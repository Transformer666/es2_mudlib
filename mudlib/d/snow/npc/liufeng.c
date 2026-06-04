// liufeng.c -- 柳風，雲遊雪亭鎮「飲風客棧」的茅山散符道人，發放「少陰符」。
//
// 來歷（呼應 docs 01-世界觀與劇情/05-主線任務與NPC.md 側線 NPC 表 L129：
//   「柳風 | 天寒村域水客棧 | 書換少陰符 (Scroll of yin)」）：
//   柳風本是茅山符籙堂出身的散人道士，因天寒村域水客棧路遠難至，遂常雲遊四方、
//   借客棧一角擺攤散符結緣。如今便在雪亭鎮「飲風客棧」歇腳，替過路的茅山弟子與
//   有緣人開光發放「少陰符」。docs 所載「書換」「天寒村域水客棧」於此作風味對白——
//   柳風口中念著天寒村域的舊話、提及以符經換符的古例，卻只當閒談；真要符時，問他
//   一聲便贈，不設硬門檻，免得遠來的少俠枯等。
//
// 機制（學自 batch-1 戒言 jieyan 的延遲 bug）：
//   * ask liufeng about 少陰符 / 符 / scroll → do_ask 內「直接同步」呼叫
//     give_shaoyin(me)（new+move(who)，失敗才落地），第一次給即時到手——
//     give 絕不放進 do_chat 陣列（do_chat 會延後約三個心跳，致玩家空等或離場漏拿）。
//     do_chat 僅用於 say 風味對白。
//   * 重複領取防呆：旗標 quest/sq_liufeng + present("shaoyin fu", me) 雙重把關。
//       未領過(無旗標)        → 開光給符、設旗標。
//       已領過(有旗標)但符已失 → 同步補一張(「散落補發」)，不重設旗標。
//       已領過且符仍在身上    → 只給對白，不重複發符。
//
// 交付的「少陰符」直接沿用正典 /obj/talisman/shaoyin_fu.c：該物為與
//   /std/magic.c::cast_spell「符閘」相接的 COMBINED_ITEM(可疊加消耗符)，
//   present id 為 "shaoyin fu"。此處不另造 d/snow/npc/obj 下的分身，以免與符閘
//   所認的正典符衝突、或造出一張機制走樣的假符。

#include <npc.h>
#include <ansi.h>

#define SHAOYIN "/obj/talisman/shaoyin_fu"

inherit F_VILLAGER;

int do_ask(string arg);
private void give_shaoyin(object who);

void create()
{
	set_name(HIC "柳風" NOR, ({ "liufeng", "liu feng", "taoist liufeng", "柳風" }) );
	set("nickname", "散符道人");
	set_attr("str", 16);
	set_attr("dex", 20);
	set_attr("int", 23);
	set_attr("wis", 24);
	set_attr("spi", 22);
	set_attr("con", 18);
	set_attr("cor", 22);
	set_race("human");
	set_class("taoist");
	set_level(12);
	set("sect", "茅山派");
	set("rank", "散符道人");

	set_skill("unarmed", 35);
	set_skill("dodge", 55);
	set_skill("parry", 45);
	set_skill("force", 70);
	set_skill("dao force", 70);
	map_skill("force", "dao force");
	set_skill("magic", 85);
	set_skill("make_scroll", 80);

	set("age", 47);
	set("gender", "male");
	set("long",
		"一個雲遊四方的茅山散人道士﹐自稱柳風。一身洗得發白的靛青道\n"
		"袍上沾著點點褪了色的硃砂﹐袖口磨得起了毛邊。他在客棧一角擺\n"
		"開半舊的符案﹐案頭壓著幾迭紅黃相間的成符﹐一管狼毫斜插在硯\n"
		"池裡。聽口音﹐他像是打那遠在天邊的天寒村域一路行腳過來的﹐\n"
		"談起水客棧裡以符經換符的舊例﹐眼裡便泛起些懷想的神色。\n"
		"你或許可以問問他﹕ask liufeng about 少陰符。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		HIC "柳風" NOR "拈起一張畫成的少陰符﹐對著光看了看符膽走勢﹐微微頷首﹐擱到一旁晾著。\n",
		HIC "柳風" NOR "捻著三縷青鬚﹐望著客棧門外出神﹐像是想起了天寒村域水客棧的舊事。\n",
		HIC "柳風" NOR "以指尖蘸了硃砂﹐在黃紙上凝神運筆﹐一道幽曲的陰符一氣呵成。\n",
	}));
	setup();
	carry_object("/obj/area/obj/robe")->wear();
	// 案頭常備幾張少陰符﹐免得空攤(亦供查看)。
	carry_object(SHAOYIN)->set_amount(3);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player()) && userp(this_player()) ) {
		if( !is_fighting() )
			do_chat((: command,
				"say 這位道友﹐一路風塵﹖貧道柳風﹐攤上這少陰符﹐有緣便結個善緣。" :));
	}
}

// 發符：直接 new + move(who) 同步交付（ask 由玩家觸發﹐玩家此刻必在場）。
// move 回真落玩家身上、自動與同類符疊加﹔move 失敗(極罕)才退落到地上。
// 切記不可放進 do_chat 陣列延後呼叫——那會害玩家空等或離場漏拿(batch-1 戒言之鑑)。
private void give_shaoyin(object who)
{
	object fu;

	if( !who || environment(who) != environment() ) return;
	fu = new(SHAOYIN);
	message_vision(HIC "柳風" NOR "自符案上取下一張少陰符﹐口中念念有詞﹐"
		"指尖一彈﹐青灰色的符紙便落入$N手中。\n", who);
	if( !fu->move(who) ) fu->move(environment());
}

int do_ask(string arg)
{
	object me = this_player();

	if( !arg )
		return notify_fail("你想問這位道人甚麼﹖（試試 ask liufeng about 少陰符）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("柳風正伏案運筆畫符﹐凝神攝氣﹐一時沒理會你。\n");

	// 問少陰符 / 符 / 換符 / scroll：贈一張少陰符（不設硬門檻，書換只作風味）
	if( arg == "liufeng about 少陰符"
	||  arg == "liu feng about 少陰符"
	||  arg == "liufeng about 符"
	||  arg == "liu feng about 符"
	||  arg == "liufeng about 換符"
	||  arg == "liufeng about scroll"
	||  arg == "liu feng about scroll"
	||  arg == "liufeng about shaoyin"
	||  arg == "liufeng about fu" ) {

		// 已領過：若符仍在身上﹐只敘舊不重發﹔若已散去﹐同步補發一張。
		if( me->query("quest/sq_liufeng") ) {
			if( present("shaoyin fu", me) ) {
				do_chat(({
					(: command, "say 道友身上那少陰符還在﹐且收好了﹐取陰柔之氣以攝幽冥﹐臨陣焚它引氣便是。" :),
					(: command, "say 這符雖只是中品﹐開光卻費心血﹐莫要輕擲了。" :),
				}));
				return 1;
			}
			// 旗標在、符已失：補發一張（同步），不重設旗標
			do_chat((: command,
				"say 咦﹐道友那張少陰符散了﹖也罷﹐貧道再與你補一張﹐這回仔細收著。" :));
			give_shaoyin(me);
			return 1;
		}

		// 首次：開光發符，設旗標（先給對白風味，再同步發符）
		do_chat(({
			(: command, "say 道友要的是少陰符﹖此符取陰柔之氣以攝幽冥﹐較那正陽符更費心血﹐乃三等符中之中品。" :),
			(: command, "say 早年在天寒村域那水客棧﹐換這符是要拿符經來換的﹔如今貧道雲遊在外﹐與道友這一面之緣﹐便不拘那古例了——拿去。" :),
		}));
		give_shaoyin(me);
		me->set("quest/sq_liufeng", 1);
		return 1;
	}

	// 問天寒村域 / 水客棧 / 茅山：純風味指路
	if( arg == "liufeng about 天寒村域"
	||  arg == "liufeng about 水客棧"
	||  arg == "liufeng about 天寒"
	||  arg == "liufeng about 茅山"
	||  arg == "liufeng about 書"
	||  arg == "liufeng about 符經" ) {
		do_chat(({
			(: command, "say 天寒村域那水客棧﹐遠在天邊﹐終年風雪。貧道便是打那兒一路行腳出來的。" :),
			(: command, "say 那村域的舊例﹕要符﹐得拿符經來換﹐謂之『書換』。貧道在外雲遊﹐倒沒這般講究——道友若要少陰符﹐問貧道一聲便是(ask liufeng about 少陰符)。" :),
		}));
		return 1;
	}

	return notify_fail("柳風捻著長鬚﹐淡淡道﹕道友問這個作甚﹖（試試 ask liufeng about 少陰符）\n");
}

int accept_fight()
{
	do_chat((: command, "say 哎呀﹗道友這是作甚﹗貧道不過是個畫符散人﹐動的哪門子手﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
