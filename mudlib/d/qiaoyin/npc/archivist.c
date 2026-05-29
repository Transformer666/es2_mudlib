// archivist.c -- 韓書吏，喬陰縣衙掌卷的老書吏，主線任務二「殘卷尋蹤」的送達對象
//
// 任務流程（旗標存在玩家身上：quest/main_omen2，由 d/fonxan/npc/elder.c 開啟）：
//   進行中 (1)  : 玩家持封山派師叔的「引薦帖」到縣衙
//                 交(give)給書吏 -> 書吏驗帖收下﹐回給「殘卷」﹐旗標設為 2
//   已取得 (2)  : 玩家把殘卷帶回封山派藏劍堂交(give)給師叔領賞
//
// 注意：本 NPC 不開啟任務（開啟在 elder.c）﹐只負責驗帖、收帖、回殘卷、
//       推進旗標 1 -> 2。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("韓書吏", ({ "yamen archivist", "archivist", "han clerk" }) );
	set_race("human");
	set_class("commoner");
	set_level(8);
	set_skill("unarmed", 12);
	set_skill("dodge", 12);
	set_skill("literate", 50);

	set("gender", "male");
	set("age", 58);
	set("long",
		"一位在縣衙卷庫裡掌管文牘的老書吏﹐穿一件洗得發灰的青布直\n"
		"裰﹐袖口磨出了毛邊﹐指節上盡是常年握筆磨出的薄繭。他在卷架\n"
		"間佝僂著背﹐一卷一卷地清點封存的舊檔﹐神情木然﹐唯有提到那\n"
		"些塵封的卷宗時﹐渾濁的眼裡才透出一絲光亮。\n"
		"你或許可以問問他﹕ask archivist about 殘卷。\n");
	setup();
	carry_object("/obj/area/obj/cloth")->wear();
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player()) ) {
		int q = this_player()->query("quest/main_omen2");
		if( q == 1 )
			do_chat((: command,
				"say 這位少俠面生得很﹐可是為著哪一宗卷宗來的﹖" :));
	}
}

// 把那卷殘卷交到玩家手上（先複製到自己身上，再 give 出去）
private void give_fragment(object who)
{
	object frag;

	if( !who || environment(who) != environment() ) {
		command("say 咦 ... 人呢﹖");
		return;
	}
	frag = new(__DIR__"obj/ancient_fragment");
	frag->move(this_object());
	command("give ancient fragment to " + who->query("id"));
}

int do_ask(string arg)
{
	object me = this_player();
	int q;

	if( !arg || (arg != "archivist about 殘卷"
		&&   arg != "archivist about 主線"
		&&   arg != "archivist about 任務"
		&&   arg != "yamen archivist about 殘卷"
		&&   arg != "archivist about quest"
		&&   arg != "archivist about task") )
		return notify_fail("你想問這位書吏甚麼﹖（試試 ask archivist about 殘卷）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("韓書吏正忙著清點卷宗﹐沒空理你。\n");

	q = me->query("quest/main_omen2");

	// 沒接過封山派師叔的差事
	if( q < 1 ) {
		do_chat((: command,
			"say 卷庫重地﹐閒人莫入。你若是奉誰之命來調卷的﹐先取了憑帖再來。" :));
		return 1;
	}

	// 任務進行中（旗標 1）：理應用 give 交付引薦帖
	if( q == 1 ) {
		if( present("intro letter", me) )
			do_chat((: command,
				"say 封山派的引薦帖帶來了罷﹖快把那帖子交(give)給老朽驗過﹐老朽自會替你調出那卷殘卷。" :));
		else
			do_chat((: command,
				"say 憑帖呢﹖無帖空口﹐這卷庫的東西可調不得﹐快回封山派找那位師叔取了引薦帖再來。" :));
		return 1;
	}

	// 已取得（旗標 2 或更後）
	if( present("ancient fragment", me) )
		do_chat((: command,
			"say 那卷殘卷老朽已調給少俠了﹐快拿回封山派交還那位師叔罷。" :));
	else
		// 萬一玩家把殘卷弄丟了，補調一卷給他
		do_chat(({
			"韓書吏佝僂著背﹐又從卷架深處摸出那卷封存的殘卷副本。\n",
			(: command, "say 怎麼那殘卷弄丟了﹖罷了﹐念在封山派的帖子份上﹐老朽再替你調一卷。" :),
			(: give_fragment, me :),
		}));
	return 1;
}

// 收下引薦帖：確認是任務信物且玩家正在送件(旗標 1)﹐推進旗標 1 -> 2 並回給殘卷
int accept_object(object who, object ob)
{
	if( !ob->id("intro letter") ) {
		do_chat((: command, "say 卷庫不收這個﹐少俠還是自個兒收著罷。" :));
		return 0;
	}

	// 不是正在送件的任務玩家（或已交過）﹐仍收下避免卡物﹐但不重複推進
	if( who->query("quest/main_omen2") != 1 ) {
		do_chat((: command, "say 多謝少俠﹗" :));
		return 1;
	}

	who->set("quest/main_omen2", 2);
	do_chat(({
		(: command, "say 封山派陸師叔的帖子 ... 不錯﹐是他的筆跡。少俠稍候。" :),
		(: command, "say 這卷殘卷封在卷庫底下幾十年了﹐前些日子縣太爺要審老松寨那案子﹐才教老朽翻了出來——說來也巧。" :),
		(: command, "say 卷子年深日久﹐字跡多有殘缺﹐少俠拿回去﹐請陸師叔自個兒參詳罷。" :),
		(: give_fragment, who :),
	}));
	return 1;
}

int accept_fight(object ob)
{
	do_chat((: command, "say 反了你了﹗縣衙重地也敢撒野﹐差役何在﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
