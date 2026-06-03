// laodao.c -- 茅山符籙堂的守堂老道，掌管成符發放（補機點 / 符紙供給）。
//
// 在百花村／天寒村／巫山等符紙貿易村落建成之前﹐玩家(尤其茅山弟子)需要
// 一處穩定取得「符」的所在。守堂老道便是此一臨時補機點：玩家以銀錢向他
// 換取開光成符﹐供施展茅山符咒(幽冥三箭系等)之用。
//
// 機制全比照 d/snow/npc/yu.c(魚天)的 accept_object 收銀模型 + d/wenguo/npc/
// inkmaker.c 的 ask...about 互動：
//   give <N>兩 silver to laodao  /  give <N> coin to laodao
//     → accept_object(who, ob)：ob 為錢(money_id)時﹐依 ob->value()(總文錢)
//       決定發放符的等第﹐new(符)->move(who)﹐回 1(give 指令於回 1 後自行
//       destruct 有值的錢﹐故老道按「足額換符」收銀)。
//   ask laodao about 符  → do_ask：報出三等符的潤格與取法。
//
// 換符潤格(以物件 base_value 為準：正陽符200/少陰符500/先天符1500 文)﹐
// 老道取個吉利的整兩價﹐略高於成本﹐合「香火錢」之意：
//   >=  100 文(1 兩銀) → 正陽符
//   >=  500 文(5 兩銀) → 少陰符
//   >= 1500 文(15兩銀) → 先天符
// 銀貨兩訖﹐多給不找零(老道只發一張更高等的符)﹐不足一兩則婉拒退還。

#include <npc.h>

inherit F_VILLAGER;

#define ZHENGYANG "/obj/talisman/zhengyang_fu"
#define SHAOYIN   "/obj/talisman/shaoyin_fu"
#define XIANTIAN  "/obj/talisman/xiantian_fu"

int do_ask(string arg);
private void hand_fu(object who, string file, string cn);

void create()
{
	set_name("茅山老道", ({ "maoshan laodao", "laodao", "old taoist", "taoist" }));
	set("nickname", "守堂老道");
	set_attr("str", 18);
	set_attr("dex", 20);
	set_attr("int", 24);
	set_attr("wis", 24);
	set_attr("spi", 22);
	set_attr("con", 20);
	set_attr("cor", 20);
	set_race("human");
	set_level(15);
	set_class("taoist");
	set("sect", "茅山派");
	set("rank", "守堂道人");

	set_skill("unarmed", 40);
	set_skill("dodge", 60);
	set_skill("parry", 50);
	set_skill("force", 80);
	set_skill("dao force", 80);
	map_skill("force", "dao force");
	set_skill("magic", 90);
	set_skill("make_scroll", 90);

	set("age", 63);
	set("gender", "male");
	set("long",
		"這是一位守著符籙堂的老道﹐鬚眉皆白﹐一身半舊的青布道袍上沾\n"
		"著點點硃砂紅。他終日伏在長案前一筆一畫地畫符、開光﹐案頭與牆\n"
		"邊木架上插滿了畫成的成符﹐紅黃相間。茅山弟子施展符咒須得焚符\n"
		"引氣﹐符紙耗得極快﹐老道便在此堂中以香火錢與人結個善緣、發放\n"
		"成符。你或許可以問問他﹕ask laodao about 符。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"茅山老道執一管狼毫﹐蘸飽了硃砂﹐在黃紙上凝神運筆﹐一道符文一氣呵成。\n",
		"茅山老道拈起一張畫成的符﹐對著光看了看符膽走勢﹐微微頷首﹐擱到一旁晾著。\n",
		"茅山老道捻著長鬚自語道﹕符到咒成﹐這符紙耗得快﹐弟子們可得備足了纔好。\n",
	}));
	setup();
	carry_object("/obj/area/obj/robe")->wear();
	// 老道身上常備幾張符﹐免得空堂(亦供 swap/查看)。
	carry_object(ZHENGYANG)->set_amount(5);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player()) && userp(this_player()) ) {
		if( !is_fighting() )
			do_chat((: command,
				"say 這位道友﹐可是來換符的﹖香火錢隨喜﹐符卻是實打實開過光的。" :));
	}
}

// 發符：直接 new + move(who) 同步交付（give/ask 皆由玩家觸發﹐玩家此刻必在場）。
// move 回 1 落玩家身上、自動與同類符合併﹔move 失敗(極罕)才退落到地上。
private void hand_fu(object who, string file, string cn)
{
	object fu = new(file);
	message_vision("茅山老道自木架上取下一張" + cn
		+ "﹐口中念念有詞﹐指尖一彈﹐將符遞到$N手中。\n", who);
	if( !fu->move(who) ) fu->move(environment());
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這位老道甚麼﹖（試試 ask laodao about 符）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("茅山老道正伏案畫符﹐凝神運筆﹐一時沒理會你。\n");

	// 問符 / 符紙 / 換符：報出三等符的潤格與取法
	if( arg == "laodao about 符"
	||  arg == "maoshan laodao about 符"
	||  arg == "laodao about 符紙"
	||  arg == "laodao about 換符"
	||  arg == "laodao about 正陽符"
	||  arg == "laodao about 少陰符"
	||  arg == "laodao about 先天符"
	||  arg == "laodao about fu"
	||  arg == "laodao about talisman" ) {
		do_chat(({
			(: command, "say 道友要符﹖我茅山符籙﹐有正陽、少陰、先天三等。正陽符取陽剛之氣以驅邪﹐最是尋常﹐入門咒術焚它引氣便足。" :),
			(: command, "say 少陰符取陰柔之氣﹐較費心血﹔先天符蘊先天罡氣﹐須擇時以血調砂﹐凝神一筆而成﹐半點差池便廢了﹐故而至貴。" :),
			(: command, "say 換符的規矩簡單﹕將銀錢交與老道便是（give 1 兩 silver to laodao﹐或 give 100 coin to laodao）。一兩銀換一張正陽符﹐五兩換少陰符﹐十五兩換先天符﹔多給的算是添的香火﹐老道只發那更高一等的符。" :),
		}));
		return 1;
	}

	// 問茅山符咒 / 幽冥三箭：點明符之用途（純氣氛指路）
	if( arg == "laodao about 符咒"
	||  arg == "laodao about 咒術"
	||  arg == "laodao about 幽冥三箭"
	||  arg == "laodao about youmin" ) {
		do_chat(({
			(: command, "say 茅山符咒﹐符到方能咒成。便如那靈雲觀的幽冥三箭﹐每施一式﹐袖中正陽符便要燃去一張——無符在身﹐縱有一身道法也施展不出。" :),
			(: command, "say 道友若是本派弟子﹐演法、行走江湖﹐身上總得備足了符纔好。符盡了﹐只管來符籙堂尋老道換便是。" :),
		}));
		return 1;
	}

	return notify_fail("茅山老道頭也不抬﹐淡淡道﹕道友問這個作甚﹖（試試 ask laodao about 符）\n");
}

// 收銀換符：
//   ob 為錢(money_id)時﹐依 ob->value()(總文錢)決定發放符的等第﹐發符後回 1
//   ——give 指令於本函回 1 後會自行 destruct 有值的錢(銀貨兩訖﹐足額換符)。
//   不足一兩(<100 文)則婉拒、不收(回 0﹐錢退還玩家)。
//   非錢之物一律婉拒﹐不吞玩家物品。
int accept_object(object who, object ob)
{
	if( ob->query("money_id") ) {
		int worth = (int)ob->value();   // 總值(文錢)

		if( worth < 100 ) {
			do_chat((: command,
				"say 道友這點錢﹐還不夠換一張符的﹐且自個兒收著罷——換符至少也得一兩銀。" :));
			return 0;       // 退還﹐不收
		}

		if( worth >= 1500 ) {
			do_chat((: command, "say 道友好大的手筆﹗這先天符開光不易﹐合該配與有道之士。" :));
			hand_fu(who, XIANTIAN, "先天符");
			return 1;
		}
		if( worth >= 500 ) {
			do_chat((: command, "say 道友爽快。這少陰符取陰柔之氣﹐道友收好了。" :));
			hand_fu(who, SHAOYIN, "少陰符");
			return 1;
		}

		// 100..499 文：發一張正陽符
		do_chat((: command, "say 好說好說﹐一張正陽符﹐道友拿去焚符引氣便是。" :));
		hand_fu(who, ZHENGYANG, "正陽符");
		return 1;
	}

	// 其餘物事：婉拒，不收下（避免吞掉玩家的尋常物品）
	do_chat((: command, "say 這個老道用不上﹐道友還是自個兒留著罷。" :));
	return 0;
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎呀﹗道友這是作甚﹗老道不過是個畫符的﹐動的哪門子手﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
