// commoner.c -- 京城百姓，京畿街頭、後海湖邊走動的尋常市井之人。
//               亦兼京畿支線任務「後海茶香」的中繼人——後海湖邊這位百姓
//               順手拾得了茶博士散落的那包雨前龍井。
//
// 任務流程（旗標存在玩家身上：quest/houhai_tea，由 d/capital/npc/teamaster.c 開啟）：
//   進行中 (1)  : 玩家 ask commoner about 茶葉 -> 百姓把拾得的「龍井茶葉」交還﹐
//                 並把旗標推進為 2（推進在本檔）
//   其餘狀態    : 只作尋常閒談﹐不交付茶葉（未接任務則裝糊塗﹐已尋回則道已給過）
//
// 注意：本 NPC 不開啟任務、不領賞﹔開啟與領賞皆在 teamaster.c。
//       以 ask（而非 give）交付信物﹐並於旗標處作防重複推進。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("京城百姓", ({ "commoner", "citizen" }) );
	set_race("human");
	set_class("commoner");
	set_level(2);

	set("age", 42);
	set("gender", "male");
	set("long",
		"一個土生土長的京城百姓﹐穿著體面的綢布長衫﹐袖著手不疾\n"
		"不徐地走著﹐眉宇間自有一股久居天子腳下、見慣大場面的從\n"
		"容氣度。\n");
	set("chat_chance", 5);
	set("chat_msg", ({
		(: random_move :),
		"京城百姓朝你拱了拱手﹐算是打了個招呼。\n",
		"京城百姓得意地說道﹕在咱們天子腳下討生活﹐那可是天大的體面﹐豈是外鄉人比得的﹖\n",
		"京城百姓壓低聲音道﹕聽說後海湖底鬧過蹊蹺﹐入夜後連畫舫都不敢往湖心去哩。\n",
		"京城百姓說道﹕出了南城門往西﹐順著官道走便是喬陰縣城了。\n",
	}));
	setup();
	carry_money("coin", 50);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player())
		&& this_player()->query("quest/houhai_tea") == 1 )
		do_chat((: command,
			"say 這位客官眼生 ... 是後海茶館那位茶博士遣來尋茶葉的罷﹖" :));
}

// 把拾得的龍井茶葉直接交到玩家手中（leaf->move(who) 比 command give 可靠﹐
// 不依賴玩家 id 字串解析﹐也不會因聊天延遲而落空）。
private void give_leaf(object who)
{
	object leaf;

	if( !who || environment(who) != environment() ) {
		command("say 咦 ... 人呢﹖客官且站定了﹐我這就把茶葉交還。");
		return;
	}
	if( present("longjing leaf", who) ) return;	// 已在玩家身上﹐不重複給

	leaf = new("/d/capital/npc/obj/longjing_leaf");
	if( leaf->move(who) ) {
		message_vision(
			"$N從懷裡摸出一包油紙裹著的龍井茶葉﹐鄭重遞到$n手中。\n",
			this_object(), who);
		// 旗標只在茶葉確實到手後才推進 1->2﹐避免「旗標走了茶葉沒拿到」卡關。
		who->set("quest/houhai_tea", 2);
	} else {
		leaf->remove();
		command("say 客官且空出隻手來接這包茶葉罷。");
	}
}

int do_ask(string arg)
{
	object me = this_player();
	int q;

	if( !arg || (arg != "commoner about 茶葉"
		&&   arg != "commoner about 茶"
		&&   arg != "commoner about 龍井"
		&&   arg != "citizen about 茶葉"
		&&   arg != "commoner about tea"
		&&   arg != "commoner about leaf") )
		return notify_fail("你想問這位百姓甚麼﹖（試試 ask commoner about 茶葉）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("京城百姓正自顧自地走著﹐沒空理你。\n");

	q = me->query("quest/houhai_tea");

	// 任務進行中（旗標 1）：交還拾得的龍井茶葉，推進旗標 1 -> 2
	if( q == 1 ) {
		if( present("longjing leaf", me) )
			do_chat((: command,
				"say 那包龍井不是早給了客官麼﹖快帶回去交(give)還茶博士罷﹗" :));
		else
			// 旗標改在 give_leaf 內、茶葉確實交到手後才推進﹐這裡不先設。
			do_chat(({
				(: command, "say 客官說的可是今早湖風捲到岸邊那包茶葉﹖嘿﹐叫我順手拾著了——瞧這油紙裹的﹐定是上好的龍井﹐我正尋思著該還誰哩。" :),
				(: command, "say 既是後海茶館茶博士的東西﹐客官替他帶回去便是。物歸原主﹐我一個本分人﹐可不貪這份。" :),
				(: give_leaf, me :),
			}));
		return 1;
	}

	// 已尋回（旗標 >=2）
	if( q >= 2 ) {
		// 救援：旗標已推進但茶葉遺失（且尚未交差 q==2）→ 再補一包﹐免得卡關。
		if( q == 2 && !present("longjing leaf", me) )
			do_chat(({
				(: command, "say 客官怎把那包龍井又弄丟了﹖也罷﹐我這兒還剩些﹐再與你補一包。" :),
				(: give_leaf, me :),
			}));
		else
			do_chat((: command,
				"say 那包龍井我早交與客官了﹐還沒給茶博士送去麼﹖" :));
		return 1;
	}

	// 未接任務（旗標 0）：裝糊塗，順道把人引向茶博士
	do_chat((: command,
		"say 茶葉﹖客官要嚐茶﹐後海茶館那位茶博士的手藝才叫一絕﹐去問他便是。" :));
	return 1;
}

int accept_fight()
{
	do_chat("京城百姓慌忙擺手道﹕使不得﹗這可是天子腳下﹐禁軍就在眼前哪﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
