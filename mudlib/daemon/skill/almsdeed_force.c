// 大悲心經 almsdeed force -- 寶蓮寺「大悲行者」進階(二轉)的內功心法
//
// 寶蓮寺善想一脈大悲行者所修的願力內功(設計(docs未明定):承 docs 明列之「大悲咒
// almsdeed magic / 善想禪要 almsdeed」一脈﹐見 docs/03-門派與武功/03-和尚-寶蓮
// 天月白象.md §寶蓮寺)。docs 明載寶蓮為「治療輔助」之寺院、大悲咒(almsdeed)為
// 其看家禪要﹐然 docs 未明列大悲行者之內功心法名﹔故大悲心經 almsdeed force 為
// 設計值﹐定位為承載大悲願力、滋養神識(sen)以續法力的願力吐納之術﹐由入門寶蓮
// 心法(baolian force)精進而成。
//
// 修煉與 valid_enable 等共用機制由 FORCE(/std/force.c)基底提供﹔本檔註冊心法
// 名、登錄中文名「大悲心經」、override cultivate_msg() 提供寶蓮寺大悲行者一脈
// 的打坐氣象﹐並 override exert_function 實作 docs 載明之大悲咒「自足治療」。
// 中文字典(data/chinese.o)查無此 key﹐以 CHINESE_D->add_translate() 自行登錄。
//
// === 大悲咒 heal(docs/03-門派與武功/03-和尚-寶蓮天月白象.md L42-54,76-80) ===
// 寶蓮、天月二寺以「濟世度人的多樣治療手段」為立寺之本(docs L6-7)、寶蓮為各職業
// 補機聖地(docs L139)。docs 指示之自足治療(不需元素引擎)：大悲咒 heal -- 消施術者
// 的氣(kee﹐或退而求其次取神 sen)﹐回補目標的精氣(gin/kee)。
//   exert heal              -> 回補自身的 gin/kee。
//   exert heal on <目標>    -> 回補同房目標(須玩家 userp 或自身)的 gin/kee。
// 觸發方式：以本內功(大悲心經)之具名 exert 功能實作﹐玩家鍵入 `exert heal [on x]`。
// cmds/std/exert.c::main 取 me->skill_mapped("force")(此處 "almsdeed force")﹐
// 並先解析 `on <dest>` 得 target(同房 present﹐或身上 present)﹐再呼
// SKILL_D("almsdeed force")->exert_function(me, "heal", target)。本檔接 func=="heal"
// 即自足治療﹔其餘 func(含 "almsdeed force" 本身打坐修煉)落回 ::exert_function 由
// FORCE 基底處理。此乃龍圖 daemon/skill/dragon_force.c::exert_function(override 具名
// 功能)、zushang.c(regenerate)之同型結構。
//
// 消耗/回補機制對齊(已驗範式 statistic.c)：
//   * 消耗：consume_stat("kee", N)(只削 current)﹔kee 不足則退取 sen(docs「或 sen」)。
//   * 回補：supplement_stat("gin"/"kee", N)(補 current﹐自動封頂於 heal/max)。
//     回補量隨大悲心經(force/almsdeed force)火候成長﹐並乘以慈悲願力(wis)加成。
//
// runtime 鐵則：本式不涉 ::die()/destruct()(#10)﹐亦不 replace_program(#11)﹔
// 為內功 daemon(inherit FORCE)﹐非 F_VILLAGER NPC﹐不 include <weapon.h>。

#include <ansi.h>

inherit FORCE;

// === 大悲咒 heal 的消耗/回補參數(docs 未明給細節﹐取合理且可驗值)。──
#define AH_COST_KEE     40      // 每次施術消耗施術者氣(kee)的當前值。
#define AH_COST_SEN     40      // 氣不足時退而消耗神(sen)的當前值(docs「或 sen」)。
#define AH_BASE_HEAL    30      // 回補目標 gin/kee 的基礎量(再加火候/慧根加成)。

// 前置宣告(lesson #12：自訂函式一律先前置宣告﹐免「定義前引用」靜默載入失敗)。
varargs int exert_function(object me, string func, object target);
int ah_heal(object me, object target);

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("almsdeed force");
	// 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
	CHINESE_D->add_translate("almsdeed force", "大悲心經");
	setup();
}

// 寶蓮寺大悲行者打坐運功時所現的內功氣象。
string cultivate_msg()
{
	return HIR "$N結大悲手印盤膝而坐﹐默運大悲心經﹐周身似有萬千金紅願力梵光氤氳"
	           "環繞﹐一股莊嚴慈悲之氣自丹田緩緩升騰﹐滋養神識、護法度世。\n" NOR;
}

// 大悲咒 heal：消施術者 kee(不足則 sen)﹐回補目標的精氣(gin/kee)。docs L42-54,76-80。
// target 為 0(未指定)或非活物時﹐默回補施術者自身(寶蓮自足治療之本意)。
int
ah_heal(object me, object target)
{
	int cost, gain, healed;
	string drained;

	// 目標：同房玩家或自身。未指定/非活物者﹐回補自己。
	if( !objectp(target) || !target->is_character() )
		target = me;
	if( environment(target) != environment(me) )
		return notify_fail("這裡並沒有這個人。\n");

	// 消耗：先取氣(kee)﹐氣不足則退取神(sen)(docs「消施術者 kee 或 sen」)。
	if( me->query_stat_current("kee") >= AH_COST_KEE ) {
		cost = AH_COST_KEE;
		drained = "kee";
	} else if( me->query_stat_current("sen") >= AH_COST_SEN ) {
		cost = AH_COST_SEN;
		drained = "sen";
	} else {
		return notify_fail("你體內氣息不足﹐運不起大悲咒這普度之力。\n");
	}

	// 回補量：基礎量 + 大悲心經火候 + 慈悲願力(wis)加成。
	gain = AH_BASE_HEAL + me->query_skill("force", 1) / 2
	       + me->query_attr("wis") / 2;
	if( gain < 1 ) gain = 1;

	// 先扣施術者的氣或神(consume_stat 只削 current)。
	me->consume_stat(drained, cost, me);

	// 回補目標的精(gin)與氣(kee)當前值(supplement_stat 自動封頂於 heal/max)。
	healed  = target->supplement_stat("gin", gain);
	healed += target->supplement_stat("kee", gain);

	if( target == me ) {
		message_vision(HIR
			"$N結大悲手印低誦神咒﹐周身金紅梵光內斂﹐一縷慈悲願力沉入自身百脈﹐"
			"溫養精氣。\n" NOR, me);
		tell_object(me, sprintf(HIW
			"你運轉大悲咒自療﹐精氣為之一充。(消 %s %d﹐回 gin/kee 各 %d)\n" NOR,
			drained, cost, gain));
	} else {
		message_vision(HIR
			"$N結大悲手印口誦神咒﹐一道莊嚴的金紅梵光自掌心漫出﹐溫柔地裹住$n﹐"
			"為其續氣療形。\n" NOR, me, target);
		tell_object(target, HIR
			"一股莊嚴慈悲的願力流遍你的四肢百骸﹐精氣為之一振。\n" NOR);
		tell_object(me, sprintf(HIW
			"你以大悲咒為%s續氣療形。(消 %s %d﹐回其 gin/kee 各 %d)\n" NOR,
			target->name(), drained, cost, gain));
	}

	me->start_busy(1);
	return 1;
}

// exert heal [on <目標>] -- 大悲咒自足治療(消 kee/sen﹐回目標 gin/kee)。
// 其餘 func(含 "almsdeed force" 本身)落回 FORCE 基底(打坐修煉 / notify_fail)。
varargs int exert_function(object me, string func, object target)
{
	if( !objectp(me) ) me = this_player();
	if( !objectp(me) ) return 0;

	if( func == "heal" )
		return ah_heal(me, target);

	return ::exert_function(me, func, target);
}

// vim: set ts=4 sw=4 syntax=lpc
