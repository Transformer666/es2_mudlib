// 長生心法 longevity force -- 寶蓮寺「長生上人」進階(二轉)的最高階內功心法
//
// 寶蓮寺善想一脈長生上人所修的無量壽內功(設計(docs未明定):承 docs 明列之「長生
// 禪法 longevity magic / link;link2 長生」一脈﹐見 docs/03-門派與武功/03-和尚-
// 寶蓮天月白象.md §寶蓮寺)。docs 明載寶蓮主力玩法為「link/link2 長生：維持隊友
// 狀態」、長生禪法 longevity magic 為其最高絕學﹐然 docs 未明列長生上人之內功
// 心法名﹔故長生心法 longevity force 為設計值﹐定位為以無量壽願力續命延壽、培
// 元固本、滋養神識(sen)的最高階吐納之術﹐由大悲心經(almsdeed force)精進而成。
//
// 修煉與 valid_enable 等共用機制由 FORCE(/std/force.c)基底提供﹔本檔註冊心法名、
// 登錄中文名「長生心法」、override cultivate_msg() 提供長生上人一脈打坐氣象﹐並
// override exert_function 實作 docs 載明之三式自足內功功能(不需元素引擎)。中文
// 字典(data/chinese.o)查無此 key﹐以 CHINESE_D->add_translate() 自行登錄。
//
// === docs 載明之自足功能(docs/03-和尚-寶蓮天月白象.md L42-54,76-80) ===
//   exert link      -> 長生(一)：對房內隊友(同房隊友 + 自身)施加持續性狀態 buff﹐
//                      提升精氣神三維的「資質」(apply/dex/con/spi)﹐使隊友狀態
//                      回復(gin/kee/sen regen)加快——即 docs「link/link2 長生：
//                      維持隊友狀態」。鏡 daemon/skill/strategy.c::do_wis 之
//                      add_temp + call_out("end_*", N) 以 add_temp(-N) 復原模型。
//   exert link2     -> 長生(二)：第二層續命 buff﹐提升隊友護甲(apply/armor﹐
//                      feature/char/combat.c::resist_damage 讀此鍵減傷)與神識
//                      資質(apply/spi)﹐與 link 疊用維持隊友(docs L79「link & link2」)。
//   exert zazengo   -> 坐禪：打坐回精氣神(gin/kee/sen)。docs L79「zazengo(坐禪)」。
//                      鏡 cmds/std/sunpray.c 之 heal_stat(回可癒上限)+supplement_stat
//                      (回當前值封頂)﹐惟無種族門檻、回補自身三維。
//
// 觸發方式：以本內功(長生心法)之具名 exert 功能實作﹐玩家鍵入 `exert link`、
// `exert link2`、`exert zazengo`。cmds/std/exert.c::main 取 me->skill_mapped("force")
// (此處 "longevity force")﹐呼 SKILL_D("longevity force")->exert_function(me, func,
// target)。本檔接 func ∈ {link,link2,zazengo} 即自行處理﹔其餘 func(含 "longevity
// force" 本身打坐修煉)落回 ::exert_function 由 FORCE 基底處理。此乃龍圖
// daemon/skill/dragon_force.c::exert_function、zushang.c(regenerate)之同型結構。
//
// 機制對齊(已驗範式)：
//   * buff：add_temp("apply/<attr>", N) 累加(query_attr 讀 apply/<attr>﹐feature/
//     attribute.c:29)﹔health_regenerator(feature/statistic.c:354)讀 query_attr
//     ("dex"/"con"/"spi") 決定 gin/kee/sen 之回復速率﹐故提升三維資質即「維持隊友
//     狀態」。到期以 add_temp(-N) 復原(**不可 delete_temp**﹐免抹掉他源同鍵加成)﹐
//     完全鏡 strategy.c::do_wis / cmds/std/wardance.c 之 buff/復原模型。
//   * 坐禪回補：heal_stat(回可癒上限封頂 max)+supplement_stat(回當前值封頂 heal/max)
//     (feature/statistic.c:264/293)﹐鏡 cmds/std/sunpray.c::do_sunpray。
//
// runtime 鐵則：本式不涉 ::die()/destruct()(#10)﹐亦不 replace_program(#11)﹔
// 為內功 daemon(inherit FORCE)﹐非 F_VILLAGER NPC﹐不 include <weapon.h>。

#include <ansi.h>

inherit FORCE;

// === link 長生(一)：提升三維資質的持續 buff(數值 docs 未明﹐取合理可驗值)。──
#define LINK_DEX        8       // 提升精(gin)回復所恃之 dex。
#define LINK_CON        8       // 提升氣(kee)回復所恃之 con。
#define LINK_SPI        8       // 提升神(sen)回復所恃之 spi。
#define LINK_DURATION   60      // buff 持續秒數(call_out 以秒計)。

// === link2 長生(二)：護甲 + 神識資質的持續 buff。──
#define LINK2_ARMOR     20      // 提升護甲(apply/armor﹐resist_damage 減傷)。
#define LINK2_SPI       10      // 再提升神識資質(apply/spi)。
#define LINK2_DURATION  60      // buff 持續秒數。

// === zazengo 坐禪：回補自身精氣神。──
#define ZAZEN_MEND      20      // 回填三維的可癒上限(heal)。
#define ZAZEN_RESTORE   60      // 回補三維的當前值(current﹐再加火候加成)。

// 前置宣告(lesson #12：自訂函式一律先前置宣告﹐免「定義前引用」靜默載入失敗)。
varargs int exert_function(object me, string func, object target);
int lf_link(object me);
int lf_link2(object me);
int lf_zazengo(object me);
void end_link(object ob);
void end_link2(object ob);

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("longevity force");
	// 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
	CHINESE_D->add_translate("longevity force", "長生心法");
	setup();
}

// 寶蓮寺長生上人打坐運功時所現的內功氣象。
string cultivate_msg()
{
	return HIW "$N結無量壽印盤膝入定﹐默運長生心法﹐周身似有一輪澄澈瑩白的壽光"
	           "緩緩流轉﹐一股清淨綿長之氣自丹田氤氳而生﹐培元固本、續命延壽。\n" NOR;
}

// link 長生(一)：對房內隊友(同房隊友 + 自身)施加持續性 buff﹐提升三維資質﹐
// 使隊友 gin/kee/sen 回復加快(維持隊友狀態)。docs L42/L79。
// 鏡 strategy.c::do_wis：add_temp + 旗標 + call_out("end_link", N)﹐到期 add_temp(-N)。
int
lf_link(object me)
{
	object env, ob, *team;
	int n;

	env = environment(me);
	if( !objectp(env) )
		return notify_fail("你身在虛空﹐無從施展長生願力。\n");

	team = me->query_team();

	message_vision(HIW
		"$N結無量壽印盤膝低誦﹐一輪澄澈瑩白的長生壽光自頂門綻放﹐如水般漫向"
		"周遭同袍﹐為眾人續命培元﹗\n" NOR, me);

	foreach(ob in all_inventory(env)) {
		if( !objectp(ob) || !ob->is_character() ) continue;
		// 僅及於自身與同隊隊友(docs「對房內隊友施加」)。
		if( ob != me && (!arrayp(team) || member_array(ob, team) == -1) )
			continue;
		// 已在 link buff 中者不重複疊加(避免無限延長)。
		if( ob->query_temp("longevity_link_active") ) continue;
		ob->set_temp("longevity_link_active", 1);
		ob->add_temp("apply/dex", LINK_DEX);
		ob->add_temp("apply/con", LINK_CON);
		ob->add_temp("apply/spi", LINK_SPI);
		ob->set_temp("longevity_link_callout",
			call_out("end_link", LINK_DURATION, ob));
		tell_object(ob, HIW "一股澄澈綿長的長生壽光流遍你的百脈﹐只覺精氣神綿綿不絕。\n" NOR);
		n++;
	}

	tell_object(me, sprintf(HIW
		"你以長生願力為%d人續命培元。(維持隊友狀態﹐持續%d秒)\n" NOR,
		n, LINK_DURATION));
	me->start_busy(1);
	return 1;
}

// link 到期：把先前加的量「減回去」並清旗標。用 add_temp(-N)﹐不可 delete_temp。
void
end_link(object ob)
{
	if( !objectp(ob) ) return;
	ob->add_temp("apply/dex", -LINK_DEX);
	ob->add_temp("apply/con", -LINK_CON);
	ob->add_temp("apply/spi", -LINK_SPI);
	ob->delete_temp("longevity_link_active");
	ob->delete_temp("longevity_link_callout");
	tell_object(ob, NOR "你身上那股綿長的長生壽光漸漸消退了。\n");
}

// link2 長生(二)：第二層續命 buff﹐提升護甲(減傷)與神識資質。docs L79「link & link2」。
int
lf_link2(object me)
{
	object env, ob, *team;
	int n;

	env = environment(me);
	if( !objectp(env) )
		return notify_fail("你身在虛空﹐無從施展長生願力。\n");

	team = me->query_team();

	message_vision(HIC
		"$N結無量壽印再運長生心法第二重﹐一層瑩白護體壽光自掌心溢散﹐覆住"
		"周遭同袍﹐為眾人護體凝神﹗\n" NOR, me);

	foreach(ob in all_inventory(env)) {
		if( !objectp(ob) || !ob->is_character() ) continue;
		if( ob != me && (!arrayp(team) || member_array(ob, team) == -1) )
			continue;
		if( ob->query_temp("longevity_link2_active") ) continue;
		ob->set_temp("longevity_link2_active", 1);
		ob->add_temp("apply/armor", LINK2_ARMOR);
		ob->add_temp("apply/spi", LINK2_SPI);
		ob->set_temp("longevity_link2_callout",
			call_out("end_link2", LINK2_DURATION, ob));
		tell_object(ob, HIC "一層瑩白的護體壽光覆上你的周身﹐只覺神智清明、護體生輝。\n" NOR);
		n++;
	}

	tell_object(me, sprintf(HIW
		"你以長生願力為%d人護體凝神。(維持隊友狀態﹐持續%d秒)\n" NOR,
		n, LINK2_DURATION));
	me->start_busy(1);
	return 1;
}

// link2 到期：把先前加的量「減回去」並清旗標。用 add_temp(-N)﹐不可 delete_temp。
void
end_link2(object ob)
{
	if( !objectp(ob) ) return;
	ob->add_temp("apply/armor", -LINK2_ARMOR);
	ob->add_temp("apply/spi", -LINK2_SPI);
	ob->delete_temp("longevity_link2_active");
	ob->delete_temp("longevity_link2_callout");
	tell_object(ob, NOR "你身上那層瑩白的護體壽光漸漸消退了。\n");
}

// zazengo 坐禪：打坐回補自身精氣神(gin/kee/sen)。docs L79。
// 鏡 sunpray.c::do_sunpray：先 heal_stat 回填可癒上限﹐再 supplement_stat 回補當前值。
int
lf_zazengo(object me)
{
	int restore, healed;

	if( me->is_fighting() )
		return notify_fail("你正在交戰之中﹐無法靜心坐禪。\n");

	// 三維俱滿則毋須坐禪。
	if( me->query_stat_current("gin") >= me->query_stat_effective("gin")
	&&  me->query_stat_current("kee") >= me->query_stat_effective("kee")
	&&  me->query_stat_current("sen") >= me->query_stat_effective("sen")
	&&  me->query_stat_effective("gin") >= me->query_stat_maximum("gin")
	&&  me->query_stat_effective("kee") >= me->query_stat_maximum("kee")
	&&  me->query_stat_effective("sen") >= me->query_stat_maximum("sen") )
		return notify_fail("你此刻精氣神俱滿﹐坐禪並無增益。\n");

	// 回補量隨長生心法(force)火候成長。
	restore = ZAZEN_RESTORE + me->query_skill("force", 1) / 2;
	if( restore < 1 ) restore = 1;

	message_vision(HIW
		"$N結無量壽印盤膝坐禪﹐萬念俱寂﹐默運長生心法調息歸元﹐周身澄澈壽光"
		"內斂﹐精氣神綿綿溫養。\n" NOR, me);

	// 先小幅回填三維可癒上限﹐再大量回補當前的精氣神。
	me->heal_stat("gin", ZAZEN_MEND);
	me->heal_stat("kee", ZAZEN_MEND);
	me->heal_stat("sen", ZAZEN_MEND);

	healed  = me->supplement_stat("gin", restore);
	healed += me->supplement_stat("kee", restore);
	healed += me->supplement_stat("sen", restore);

	if( healed > 0 )
		tell_object(me, sprintf(HIW
			"你靜心坐禪﹐精氣神為之一振﹐大為回復。(每維回約 %d)\n" NOR, restore));
	else
		tell_object(me, "你靜心坐禪﹐然此刻精氣神俱滿﹐已無從再補。\n");

	me->start_busy(1);
	return 1;
}

// exert link/link2/zazengo -- 長生心法之自足內功功能(群補 buff / 坐禪回補)。
// 其餘 func(含 "longevity force" 本身)落回 FORCE 基底(打坐修煉 / notify_fail)。
varargs int exert_function(object me, string func, object target)
{
	if( !objectp(me) ) me = this_player();
	if( !objectp(me) ) return 0;

	switch( func ) {
	case "link":    return lf_link(me);
	case "link2":   return lf_link2(me);
	case "zazengo": return lf_zazengo(me);
	}

	return ::exert_function(me, func, target);
}

// vim: set ts=4 sw=4 syntax=lpc
