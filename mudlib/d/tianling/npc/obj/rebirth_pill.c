// rebirth_pill.c -- 正史主線第十章「技能重置」的存 exp 信物：轉生丹。
//
// 來歷（承接 docs 主線樹 docs/01-世界觀與劇情/05 L187-188「找 人靈之樸 換取 轉生丹／先
//   吞轉生丹存取 exp（reset 後技能 exp 歸零）」）：
//   人靈魂泉畔的人靈之樸，自魂泉清光中凝出這一枚轉生丹相授。武者重凝大成（技能重置）
//   之際，那一身武學的學習進度將盡數洗去歸零；故須先服下此丹，將自身此刻的一身實戰
//   閱歷（combat exp / score）封存於丹中——重置之後，這封存的閱歷不致白白蝕去。
//
// 用法（背包內的服食信物——本檔 init()+do_eat() 落實，承 lesson #11「自訂函式之物不可
//   replace_program」、starlight_ring/chaos_seal 之背包 add_action 範式）：
//   * 本丹在玩家背包中，其 init() 必隨丹入背包(get)而觸發——故於 init() 註冊服食動作
//     (add_action "do_eat","服"/"eat")。動作掛在【背包內的轉生丹物件】上(reliable)。
//   * 玩家於身上『服 轉生丹』(亦容 eat rebirth pill)：將自身此刻的實戰閱歷快照
//     （score/combat 實戰經驗、score/survive 江湖歷練）存入旗標 quest/reset_stored_exp_*
//     並記 quest/reset_stored_exp=1，message，末了 destruct 本丹（destruct-LAST，承
//     lesson #10：destruct 後同函式其後碼不保證續行）。
//   設 no_sell：重置信物干係主線，玩家須帶在身邊、依序服食，斷不可變賣。
//
// 注意：本丹為人靈之樸逐玩家 clone 交付的任務信物，不 inherit F_UNIQUE（鏡 chaos_seal/
//   starlight_ring 之做法：僅以 set("unique",1) 作風味標記）。⚠ 既定義自訂 init()/
//   do_eat()，依 lesson #11 斷「不」replace_program。

#include <ansi.h>

inherit ITEM;

int do_eat(string arg);

void create()
{
	set_name(HIY "轉生丹" NOR,
		({ "rebirth pill", "rebirth", "轉生丹" }) );
	set_weight(50);

	if( !clonep() ) {
		set("unit", "枚");
		set("value", 1);
		set("unique", 1);
		set("no_sell", 1);
		set("long",
			"一枚溫潤如玉、彷彿凝著一縷澄澈清光的奇異丹丸。丹身既非\n"
			"草木金石所煉，而似那人靈魂泉之水所凝——通體流轉著一層淡淡\n"
			"的清光，明滅之間，竟隱隱有日月星三光的微芒在丹心深處交映迴\n"
			"盪。這是人靈魂泉畔的人靈之樸，自那一泓映著日月星三光的魂泉\n"
			"清光中凝出的轉生丹。傳聞武者重凝大成、行那技能重置之際，那\n"
			"一身武學的學習進度將盡數洗去歸零；唯有先服下此丹，將自身此\n"
			"刻的一身實戰閱歷封存於丹中，那畢生闖蕩江湖、刀頭舔血換來的\n"
			"閱歷，方不致隨重置而白白蝕去。握之在手，但覺一縷溫煦清涼的\n"
			"靈氣自掌心緩緩漫開，周身百骸俱為之一靜。\n");
	}
	setup();
}

// 本丹在玩家背包中，其 init() 必隨丹入背包(get)而觸發——於此註冊服食動作。
void init()
{
	add_action("do_eat", ({ "服", "eat" }) );
}

// 服食：服 轉生丹 / eat rebirth pill。將玩家此刻的實戰閱歷快照存入旗標，再 destruct 本
//   丹（destruct-LAST，承 lesson #10）。me=this_player()。arg 須指本轉生丹（在玩家身上）。
int do_eat(string arg)
{
	object me = this_player();
	object pill;
	int combat, survive;

	if( !me ) return 0;
	if( !arg || arg == "" )
		return notify_fail("你要服甚麼？（試試：服 轉生丹／eat rebirth pill）\n");

	// arg 須指本轉生丹（在玩家身上）。
	pill = present(arg, me);
	if( !objectp(pill) || pill != this_object() )
		return notify_fail("你身上並無這樣一枚可服的丹丸。\n");

	// 防重複服食（已存過 exp）——不重複覆寫快照、亦不重複 destruct。
	if( me->query("quest/reset_stored_exp") == 1 )
		return notify_fail(
			"你方才已服下一枚轉生丹、將一身實戰閱歷封存妥當了，此刻並無別的"
			"轉生丹可服。\n");

	// —— 合格服食：先做完所有快照/旗標更新與 message，最末才 destruct 本丹 ——
	// 將玩家此刻的實戰閱歷快照（實戰經驗 score/combat、江湖歷練 score/survive）存入旗標。
	combat  = me->query("score/combat");
	survive = me->query("score/survive");
	me->set("quest/reset_stored_exp_combat", combat);
	me->set("quest/reset_stored_exp_survive", survive);
	me->set("quest/reset_stored_exp", 1);   // 記：已服轉生丹存取 exp。

	message_vision(
		HIY "$N將那枚轉生丹和入口中——丹丸入腹即化作一縷溫煦的清光，自丹田緩緩"
		"漫向周身百骸。$N但覺畢生闖蕩江湖、刀頭舔血換來的那一身實戰閱歷，竟如倒"
		"映入水的星河一般，一點一滴地自心神深處被那清光輕輕拓下、封存了起來——縱"
		"是日後洗去舊習、重凝大成，這一身的閱歷，也再不致白白蝕去了。\n" NOR,
		me);

	tell_object(me,
		HIG "（你此刻的實戰閱歷已封存於轉生丹中：實戰經驗 " + combat + "、江湖歷練 "
		+ survive + "。如今便可去尋人靈之樸行那技能重置了——ask renling about 重置。）\n"
		NOR);

	// 轉生丹既已服下、閱歷既已封存，destruct（必置於上方快照/旗標/message「之後」——
	// destruct-LAST，承 lesson #10：destruct 後同函式其後碼不保證續行）。
	destruct(this_object());

	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
