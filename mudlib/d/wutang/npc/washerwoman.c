// washerwoman.c
//
// 五堂鎮支線任務（quest/wutang_cargo，由 biaotou.c 開啟）的取貨對象：
//   進行中 (1)  : 玩家從鏢頭處接下任務後﹐到小巷 ask washerwoman about 鏢物
//                 浣衣婦交出拾得的「鏢物」﹐並把玩家旗標推進為 2
//   已取貨 (2)  : 玩家把鏢物帶回鏢局交(give)給鏢頭領賞
//
// 注意：本 NPC 不開啟任務（開啟在 biaotou.c），只負責交出鏢物、推進旗標 1 -> 2。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("浣衣婦", ({ "washerwoman", "woman" }) );
	set_race("human");
	set_class("commoner");
	set_level(2);

	set("age", 32);
	set("gender", "female");
	set("long",
		"一個衣著樸素的婦人﹐挽著袖子蹲在井邊浣洗衣裳﹐木杵起落﹐手\n"
		"腳十分俐落。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		"浣衣婦用木杵捶打著衣物﹐發出一陣陣悶響。\n",
		"浣衣婦頭也不抬地說道﹕這位客官﹐打水請等我洗完這桶。\n",
		"浣衣婦絞著衣裳說道﹕這口老井的水又清又甜﹐全鎮就數它最好。\n",
	}));
	setup();
	carry_object("/obj/area/obj/cloth")->wear();
	carry_money("coin", 8);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player()) ) {
		int q = this_player()->query("quest/wutang_cargo");
		if( q == 1 )
			do_chat((: command,
				"say 這位客官面生﹐莫不是鏢局差來尋那漆盒的﹖" :));
	}
}

// 把拾得的鏢物交到玩家手上（先複製到自己身上，再 give 出去）
private void give_cargo(object who)
{
	object cargo;

	if( !who || environment(who) != environment() ) {
		command("say 咦 ... 人呢﹖");
		return;
	}
	cargo = new(__DIR__"obj/escort_cargo");
	cargo->move(this_object());
	command("give escort cargo to " + who->query("id"));
}

int do_ask(string arg)
{
	object me = this_player();
	int q;

	if( !arg || (arg != "washerwoman about 鏢物"
		&&   arg != "woman about 鏢物"
		&&   arg != "washerwoman about cargo"
		&&   arg != "washerwoman about quest") )
		return notify_fail("你想問浣衣婦甚麼﹖（試試 ask washerwoman about 鏢物）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("浣衣婦正忙著﹐沒空理你。\n");

	q = me->query("quest/wutang_cargo");

	// 沒接過鏢局的差事
	if( q < 1 ) {
		do_chat((: command,
			"say 客官說的甚麼漆盒﹖我一個浣衣的婦人﹐可不曉得鏢局的事。" :));
		return 1;
	}

	// 任務進行中（旗標 1）：交出鏢物並推進旗標
	if( q == 1 ) {
		if( present("escort cargo", me) ) {
			do_chat((: command,
				"say 那漆盒不是給你了麼﹖快拿回鏢局交(give)給鏢頭罷。" :));
			return 1;
		}
		me->set("quest/wutang_cargo", 2);
		do_chat(({
			(: command, "say 哦﹗原來是鏢局的物事﹐難怪這般精緻﹐我正愁不知該還給誰呢。" :),
			(: command, "say 喏﹐就是這只漆盒﹐封條我可一點沒動。客官快拿回去交(give)給鏢頭罷。" :),
			(: give_cargo, me :),
		}));
		return 1;
	}

	// 已取貨（旗標 2 或更後）
	if( present("escort cargo", me) )
		do_chat((: command,
			"say 漆盒在你手上了﹐快拿回鏢局交(give)給鏢頭罷。" :));
	else
		// 萬一玩家把鏢物弄丟了，補一只給他
		do_chat(({
			"浣衣婦從井邊的籃子裡又取出那只漆盒。\n",
			(: command, "say 怎麼漆盒又不見了﹖罷了﹐還在我這兒擱著呢﹐再拿去罷。" :),
			(: give_cargo, me :),
		}));
	return 1;
}

int accept_fight()
{
	do_chat("浣衣婦嚇得花容失色﹐連聲道﹕別﹗別﹗我一個婦道人家 ...\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
