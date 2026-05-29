// axing.c -- 阿杏，順生堂藥鋪的小學徒，雪亭鎮新手任務 2 的委託人
//
// 前置條件：玩家須先完成新手任務 1（quest/snow_newbie >= 3）﹐否則阿杏
//           只會提示「先去幫張婆婆送點心」。
//
// 任務流程（旗標存在玩家身上：quest/snow_newbie2）：
//   未開始 (0)  : 玩家完成任務 1 後 ask axing about 任務 -> 接下採藥任務﹐
//                 旗標設為 1﹐並指引玩家到南門外郊野找「老藥農」取草藥
//   進行中 (1)  : 玩家到郊野 ask laoyaonong about 草藥﹐老藥農給草藥﹐
//                 並把玩家旗標推進為 2（推進在 herbfarmer.c）
//   已取貨 (2)  : 玩家把草藥帶回藥鋪交(give)給阿杏 -> 領賞﹐旗標設為 3
//   已完成 (3)  : 不再重複給賞（防止重複領獎）

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("阿杏", ({ "axing", "apprentice" }) );
	set_race("human");
	set_class("commoner");
	set_level(2);
	set_skill("unarmed", 3);
	set_skill("dodge", 3);

	set("gender", "female");
	set("age", 15);
	set("long",
		"一個十四五歲的小姑娘﹐紮著兩條烏黑的辮子﹐在順生堂裡幫著\n"
		"掌櫃抓藥跑腿。她做事麻利﹐就是人手不夠時常忙得腳不沾地。\n"
		"她看了你一眼﹐似乎有事相求。你或許可以問問她﹕\n"
		"ask axing about 任務。\n");
	setup();
	carry_object("/obj/area/obj/cloth")->wear();
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player()) ) {
		int q  = this_player()->query("quest/snow_newbie2");
		int q1 = this_player()->query("quest/snow_newbie");
		if( q == 1 || q == 2 )
			do_chat((: command,
				"say 大哥﹐郊野的老藥農那邊﹐草藥可取回來了麼﹖" :));
		else if( q < 1 && q1 >= 3 )
			do_chat((: command,
				"say 大哥﹐店裡正缺人手採藥﹐能不能幫個忙呀﹖" :));
	}
}

// 領賞：給銅錢、一把匕首（防身用）、一顆山豬果（提神），再加些經驗
private void give_reward(object who)
{
	object coin, dagger, berry;

	if( !who || environment(who) != environment() ) return;

	coin = new("/obj/money/coin");
	coin->set_amount(100);
	if( !coin->move(who) ) coin->move(environment());

	dagger = new("/obj/area/obj/dagger");
	if( !dagger->move(who) ) dagger->move(environment());

	berry = new("/obj/medication/boar_berry");
	if( !berry->move(who) ) berry->move(environment());

	who->gain_score("survive", 200);

	message_vision(
		"阿杏歡歡喜喜地接過草藥﹐取了一串銅錢﹐又從櫃上拿了把防身的"
		"匕首和一顆山豬果﹐一併塞到$N手裡。\n",
		who);
}

int do_ask(string arg)
{
	object me = this_player();
	int q, q1;

	if( !arg || (arg != "axing about 任務"
		&&   arg != "apprentice about 任務"
		&&   arg != "axing about quest"
		&&   arg != "axing about task") )
		return notify_fail("你想問阿杏甚麼﹖（試試 ask axing about 任務）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("阿杏正忙著﹐沒空理你。\n");

	q  = me->query("quest/snow_newbie2");
	q1 = me->query("quest/snow_newbie");

	// 已全部完成
	if( q >= 3 ) {
		do_chat((: command,
			"say 多虧大哥幫忙﹐掌櫃還誇我會找人手呢﹐再謝謝你啦﹗" :));
		return 1;
	}

	// 已取貨，回來交草藥（理應用 give 交付，這裡只作提示）
	if( q == 2 ) {
		if( present("herb bundle", me) )
			do_chat((: command,
				"say 草藥取回來啦﹖快把那捆草藥交(give)給我罷﹗" :));
		else
			do_chat((: command,
				"say 咦﹐草藥呢﹖你是不是把那捆草藥弄丟了﹖快回郊野找老藥農補一捆。" :));
		return 1;
	}

	// 任務進行中（還沒取到貨）
	if( q == 1 ) {
		do_chat((: command,
			"say 大哥出南門到郊野﹐找那位老藥農﹐ask laoyaonong about 草藥﹐"
			"取了草藥(give)帶回來給我就成了。" :));
		return 1;
	}

	// q == 0：尚未接任務
	// 前置條件：須先完成新手任務 1
	if( q1 < 3 ) {
		do_chat((: command,
			"say 大哥面生得很﹐這樣罷﹐你先去客棧幫張婆婆送點心﹐"
			"在鎮上混個臉熟﹐回頭我再請你幫忙。" :));
		return 1;
	}

	// 接下任務：旗標設為 1
	me->set("quest/snow_newbie2", 1);
	do_chat(({
		(: command, "say 太好啦﹗是這樣的﹐店裡的草藥快用完了。" :),
		(: command, "say 鎮南門外的郊野有位老藥農替咱們採藥﹐麻煩大哥跑一趟。" :),
		(: command, "say 到了郊野 ask laoyaonong about 草藥﹐"
			"把他採的草藥(give)帶回來給我﹐我重重有賞﹗" :),
	}));
	return 1;
}

// 收下草藥：確認是任務信物且玩家已取貨(旗標 2)，推進旗標 2 -> 3 並領賞
int accept_object(object who, object ob)
{
	if( !ob->id("herb bundle") ) {
		do_chat((: command, "say 這個藥鋪用不上﹐大哥還是自個兒留著罷。" :));
		return 0;
	}

	// 不是已取貨的任務玩家（或已交過），仍收下避免卡物，但不重複給賞
	if( who->query("quest/snow_newbie2") != 2 ) {
		do_chat((: command, "say 多謝大哥﹗" :));
		return 1;
	}

	who->set("quest/snow_newbie2", 3);
	do_chat(({
		(: command, "say 正是這味草藥﹗大哥辦事真俐落﹗" :),
		(: give_reward, who :),
		(: command, "say 這把匕首大哥拿著防身﹐山豬果累了能提提神。日後常來啊﹗" :),
	}));
	return 1;
}

int accept_fight()
{
	do_chat((: command, "say 哎呀大哥別動手﹐我這就喊掌櫃了﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
