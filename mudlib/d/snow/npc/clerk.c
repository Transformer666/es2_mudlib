// clerk.c -- 師爺，雪亭鎮鄉校衙堂裡斷事的官府師爺，主線任務「卯木之兆」的送達對象
//
// 任務流程（旗標存在玩家身上：quest/main_omen，由 keeper.c 開啟）：
//   進行中 (1)  : 玩家從土地公廟接下任務後﹐把「密報」帶到鄉校
//                 交(give)給師爺 -> 師爺收下密報﹐回給「批文」﹐旗標設為 2
//   已送達 (2)  : 玩家把批文帶回土地公廟交(give)給廟祝領賞
//
// 注意：本 NPC 不開啟任務（開啟在 keeper.c）﹐只負責收密報、回批文、
//       推進旗標 1 -> 2。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("師爺", ({ "clerk", "shiye", "secretary" }) );
	set_race("human");
	set_class("commoner");
	set_level(6);
	set_skill("unarmed", 10);
	set_skill("dodge", 10);
	set_skill("literate", 30);

	set("gender", "male");
	set("age", 47);
	set("long",
		"一位縣裡派到鄉校斷事的師爺﹐戴著瓜皮小帽﹐穿一件半舊的醬\n"
		"色綢衫﹐鼻梁上架著一副玳瑁老花鏡。他在衙堂的案後坐著﹐手\n"
		"邊堆著一摞卷宗﹐執筆批著公文﹐神情透著公門中人的精明老到。\n"
		"你或許可以問問他﹕ask clerk about 任務。\n");
	setup();
	carry_object("/obj/area/obj/cloth")->wear();
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player()) ) {
		int q = this_player()->query("quest/main_omen");
		if( q == 1 )
			do_chat((: command,
				"say 這位少俠﹐可是土地公廟的廟祝差你來投遞文書的﹖" :));
	}
}

// 把一紙批文交到玩家手上（先複製到自己身上，再 give 出去）
private void give_reply(object who)
{
	object reply;

	if( !who || environment(who) != environment() ) {
		command("say 咦 ... 人呢﹖");
		return;
	}
	reply = new(__DIR__"obj/official_reply");
	reply->move(this_object());
	command("give official reply to " + who->query("id"));
}

int do_ask(string arg)
{
	object me = this_player();
	int q;

	if( !arg || (arg != "clerk about 任務"
		&&   arg != "shiye about 任務"
		&&   arg != "secretary about 任務"
		&&   arg != "clerk about quest"
		&&   arg != "clerk about task") )
		return notify_fail("你想問師爺甚麼﹖（試試 ask clerk about 任務）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("師爺正忙著﹐沒空理你。\n");

	q = me->query("quest/main_omen");

	// 沒接過廟祝的差事
	if( q < 1 ) {
		do_chat((: command,
			"say 衙堂斷事﹐閒人勿擾。你若是替誰投遞文書的﹐先取了文書再來。" :));
		return 1;
	}

	// 任務進行中（旗標 1）：理應用 give 交付密報
	if( q == 1 ) {
		if( present("sealed report", me) )
			do_chat((: command,
				"say 廟祝的密報帶來了罷﹖快把那封密報交(give)給本師爺﹐我這就過目回你一紙批文。" :));
		else
			do_chat((: command,
				"say 密報呢﹖空著手可投不了文書﹐快回土地公廟找廟祝取了密報再來。" :));
		return 1;
	}

	// 已送達（旗標 2 或更後）
	if( present("official reply", me) )
		do_chat((: command,
			"say 批文本師爺都批給你了﹐快拿回土地公廟交給廟祝罷。" :));
	else
		// 萬一玩家把批文弄丟了，補一紙給他
		do_chat(({
			"師爺自卷宗裡抽出一張公箋﹐提筆重新批了一紙。\n",
			(: command, "say 怎麼批文弄丟了﹖罷了﹐本師爺再給你補一紙。" :),
			(: give_reply, me :),
		}));
	return 1;
}

// 收下密報：確認是任務信物且玩家正在送件(旗標 1)﹐推進旗標 1 -> 2 並回給批文
int accept_object(object who, object ob)
{
	if( !ob->id("sealed report") ) {
		do_chat((: command, "say 衙堂不收這個﹐少俠還是自個兒留著罷。" :));
		return 0;
	}

	// 不是正在送件的任務玩家（或已交過）﹐仍收下避免卡物﹐但不重複推進
	if( who->query("quest/main_omen") != 1 ) {
		do_chat((: command, "say 多謝少俠﹗" :));
		return 1;
	}

	who->set("quest/main_omen", 2);
	do_chat(({
		(: command, "say 卯木夜啼 ... 嘶﹐這等怪事﹐本師爺倒也聽斐縣那邊的同僚提過一兩樁。" :),
		(: command, "say 此事本師爺記下了﹐自會具文呈報縣衙。封山派近來也在查那株老榕﹐少俠日後留意便是。" :),
		(: command, "say 這紙批文少俠收好﹐拿回去交(give)給廟祝﹐也好教那老人家安心。" :),
		(: give_reply, who :),
	}));
	return 1;
}

int accept_fight(object ob)
{
	do_chat((: command, "say 放肆﹗竟敢在衙堂之上動粗﹐皂隸何在﹐還不拿下﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
