// gateman.c -- 門房，史部尚書府前的看門人，京畿支線任務的送達對象
//
// 任務流程（旗標存在玩家身上：quest/capital_errand，由 patrolman.c 開啟）：
//   進行中 (1)  : 玩家從巡檢處接下任務後﹐把「密函」帶到尚書府前
//                 交(give)給門房 -> 門房收下密函﹐回給「回執」﹐旗標設為 2
//   已送達 (2)  : 玩家把回執帶回後海茶館交(give)給巡檢領賞
//
// 注意：本 NPC 不開啟任務（開啟在 patrolman.c），只負責收密函、回回執、
//       推進旗標 1 -> 2。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("門房", ({ "gateman", "doorman" }) );
	set_race("human");
	set_class("commoner");
	set_level(5);
	set_skill("unarmed", 10);
	set_skill("dodge", 10);

	set("gender", "male");
	set("age", 52);
	set("long",
		"一個尚書府的老門房﹐穿著漿洗得發白的青布長衫﹐叼著一桿\n"
		"旱菸袋﹐瞇著眼斜倚在門邊的抱鼓石上。他在這府門前迎來送\n"
		"往了大半輩子﹐眼力極毒﹐尋常人的來路一望便知。\n"
		"你或許可以問問他﹕ask gateman about 任務。\n");
	setup();
	carry_object("/obj/area/obj/cloth")->wear();
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player()) ) {
		int q = this_player()->query("quest/capital_errand");
		if( q == 1 )
			do_chat((: command,
				"say 這位壯士﹐可是巡院差你來投遞文書的﹖" :));
	}
}

// 把一紙回執交到玩家手上（先複製到自己身上，再 give 出去）
private void give_receipt(object who)
{
	object receipt;

	if( !who || environment(who) != environment() ) {
		command("say 咦 ... 人呢﹖");
		return;
	}
	receipt = new(__DIR__"obj/receipt");
	receipt->move(this_object());
	command("give signed receipt to " + who->query("id"));
}

int do_ask(string arg)
{
	object me = this_player();
	int q;

	if( !arg || (arg != "gateman about 任務"
		&&   arg != "doorman about 任務"
		&&   arg != "gateman about quest"
		&&   arg != "gateman about task") )
		return notify_fail("你想問門房甚麼﹖（試試 ask gateman about 任務）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("門房正忙著﹐沒空理你。\n");

	q = me->query("quest/capital_errand");

	// 沒接過巡院的差事
	if( q < 1 ) {
		do_chat((: command,
			"say 尚書府重地﹐閒人免進。你若是替巡院送文書的﹐先去後海茶館找巡檢領了密函再來。" :));
		return 1;
	}

	// 任務進行中（旗標 1）：理應用 give 交付密函
	if( q == 1 ) {
		if( present("sealed dispatch", me) )
			do_chat((: command,
				"say 巡院的密函帶來了罷﹖快把那封密函交(give)給老朽﹐我這就收下回你一紙回執。" :));
		else
			do_chat((: command,
				"say 密函呢﹖空著手可投不了文書﹐快回後海茶館找巡檢取了密函再來。" :));
		return 1;
	}

	// 已送達（旗標 2 或更後）
	if( present("signed receipt", me) )
		do_chat((: command,
			"say 回執老朽都簽押給你了﹐快拿回後海茶館交給巡檢罷。" :));
	else
		// 萬一玩家把回執弄丟了，補一紙給他
		do_chat(({
			"門房從門房裡取出印泥﹐又重新簽了一紙回執。\n",
			(: command, "say 怎麼回執弄丟了﹖罷了﹐老朽再給你補一紙。" :),
			(: give_receipt, me :),
		}));
	return 1;
}

// 收下密函：確認是任務信物且玩家正在送件(旗標 1)，推進旗標 1 -> 2 並回給回執
int accept_object(object who, object ob)
{
	if( !ob->id("sealed dispatch") ) {
		do_chat((: command, "say 尚書府不收這個﹐壯士還是自個兒留著罷。" :));
		return 0;
	}

	// 不是正在送件的任務玩家（或已交過），仍收下避免卡物，但不重複推進
	if( who->query("quest/capital_errand") != 1 ) {
		do_chat((: command, "say 多謝壯士﹗" :));
		return 1;
	}

	who->set("quest/capital_errand", 2);
	do_chat(({
		(: command, "say 大內巡院的關防﹐錯不了。老朽這就把文書呈進去。" :),
		(: command, "say 這紙回執壯士收好﹐拿回去交(give)給巡檢﹐你那趟差事便算交差了。" :),
		(: give_receipt, who :),
	}));
	return 1;
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎喲﹗光天化日在尚書府門前撒野﹐府丁﹗還不快拿下﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
