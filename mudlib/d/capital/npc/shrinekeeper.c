// shrinekeeper.c -- 守木老者，京畿神社中看守聖木舊址的老者，
//                   主線任務三「聖木探封」的送達對象
//
// 故事背景（承接主線二「殘卷尋蹤」）：
//   封山派師叔陸抱朴集齊《封鬼遺錄》﹐稟過掌門柳東蘆後﹐方知三百年前皇城
//   那株鎮著天地的聖木被斷、放出侮天鬼之物的舊案確有其事。掌門遂命少俠持
//   「封山派文書」往京畿神社﹐尋訪當年聖木被斷後便世代留守此地的老者﹐問
//   清那道封印如今的虛實。這守木老者外人只當他是神社裡掃灑的雜役﹐其實是
//   守著聖木舊址的後人。
//
// 任務流程（旗標存在玩家身上：quest/main_omen3，由 d/fonxan/npc/elder.c 開啟）：
//   進行中 (1)  : 玩家持封山派掌門的「封山派文書」到京畿神社
//                 交(give)給守木老者 -> 老者驗書後收下﹐道出封印將潰之實﹐
//                 回給「聖木殘片」﹐並把旗標推進為 2（推進在本檔）
//   已取得 (2)  : 玩家把聖木殘片帶回封山派藏劍堂交(give)給陸師叔領賞
//
// 注意：本 NPC 不開啟任務（開啟在 elder.c）﹐只負責驗書、收書、回殘片、
//       推進旗標 1 -> 2。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("守木老者", ({ "shrine keeper", "shrinekeeper", "shouqi" }) );
	set("nickname", "守木老者");
	set_attr("int", 22);
	set_attr("wis", 24);
	set_race("human");
	set_class("commoner");
	set_level(15);
	set_skill("unarmed", 20);
	set_skill("dodge", 20);
	set_skill("force", 30);
	set_skill("literate", 40);

	set("gender", "male");
	set("age", 71);
	set("long",
		"一位在京畿神社裡掃灑添油的老者﹐布衣芒鞋﹐背脊微駝﹐尋常\n"
		"香客只當他是廟裡打雜的僕役。可他那雙眼睛卻深得很﹐每每出神\n"
		"地望著神龕後一處不起眼的角落——那裡有一截焦黑的老樹樁﹐相傳\n"
		"便是三百年前那株被斷的聖木舊址。聽聞他這一脈世代留守此地﹐\n"
		"看的不是這香火鼎盛的神社﹐而是那截早已枯死的樹樁。\n"
		"你或許可以問問他﹕ask keeper about 聖木。\n");
	setup();
	carry_object("/obj/area/obj/cloth")->wear();
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player()) ) {
		int q = this_player()->query("quest/main_omen3");
		if( q == 1 )
			do_chat((: command,
				"say 這位少俠面生﹐到這神龕後頭來﹐可是有甚麼要緊事﹖" :));
	}
}

// 把一片聖木殘片交到玩家手上（先複製到自己身上，再 give 出去）
private void give_shard(object who)
{
	object shard;

	if( !who || environment(who) != environment() ) {
		command("say 咦 ... 人呢﹖");
		return;
	}
	shard = new(__DIR__"obj/saintwood_shard");
	shard->move(this_object());
	command("give saintwood shard to " + who->query("id"));
}

int do_ask(string arg)
{
	object me = this_player();
	int q;

	if( !arg || (arg != "keeper about 聖木"
		&&   arg != "keeper about 封印"
		&&   arg != "keeper about 主線"
		&&   arg != "keeper about 任務"
		&&   arg != "shrine keeper about 聖木"
		&&   arg != "shrine keeper about 封印"
		&&   arg != "keeper about quest"
		&&   arg != "keeper about task") )
		return notify_fail("你想問這位老者甚麼﹖（試試 ask keeper about 聖木）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("守木老者正出神地望著那截老樹樁﹐沒空理你。\n");

	q = me->query("quest/main_omen3");

	// 沒接過封山派掌門的差事
	if( q < 1 ) {
		do_chat((: command,
			"say 神龕後頭沒甚麼好看的﹐少俠還是到前頭上香去罷。聖木舊事﹐不是逢人便說的。" :));
		return 1;
	}

	// 任務進行中（旗標 1）：理應用 give 交付封山派文書
	if( q == 1 ) {
		if( present("sect dispatch", me) )
			do_chat((: command,
				"say 封山派的文書帶來了罷﹖少俠且把那紙文書交(give)給老朽驗過﹐老朽自有舊事相告。" :));
		else
			do_chat((: command,
				"say 空口無憑﹐這聖木的舊事老朽豈能輕信於人﹖少俠且回封山派﹐取了掌門的文書再來。" :));
		return 1;
	}

	// 已取得（旗標 2 或更後）
	if( present("saintwood shard", me) )
		do_chat((: command,
			"say 那片殘木老朽已交給少俠了﹐快拿回封山派﹐交還那位陸師叔罷。" :));
	else
		// 萬一玩家把聖木殘片弄丟了，補取一片給他
		do_chat(({
			"守木老者搖頭嘆息﹐又佝僂著身子﹐到那老樹樁邊小心翼翼取下一片殘木。\n",
			(: command, "say 怎麼那片殘木弄丟了﹖罷了﹐念在封山派的份上﹐老朽再替少俠取一片。" :),
			(: give_shard, me :),
		}));
	return 1;
}

// 收下封山派文書：確認是任務信物且玩家正在送件(旗標 1)﹐推進旗標 1 -> 2 並回給聖木殘片
int accept_object(object who, object ob)
{
	if( !ob->id("sect dispatch") ) {
		do_chat((: command, "say 神社清淨地﹐不收這個﹐少俠還是自個兒收著罷。" :));
		return 0;
	}

	// 不是正在送件的任務玩家（或已交過）﹐仍收下避免卡物﹐但不重複推進
	if( who->query("quest/main_omen3") != 1 ) {
		do_chat((: command, "say 多謝少俠﹗" :));
		return 1;
	}

	who->set("quest/main_omen3", 2);
	do_chat(({
		(: command, "say 封山派掌門柳東蘆的文書 ... 不錯﹐連那兩方印都對得上。少俠請隨老朽到這神龕後頭來。" :),
		(: command, "say 少俠瞧見了麼﹖那截焦黑的老樹樁﹐便是三百年前那株聖木被斷後留下的舊址。老朽這一脈﹐世代守的便是它。" :),
		(: command, "say 不瞞少俠﹐這些年那封印一日弱似一日。雪亭鎮那株卯木夜半啼哭﹐便是封印鬆動之兆——當年斷木放出的那物﹐只怕快要復出了。" :),
		(: command, "say 老朽從樹樁上取下這片殘木﹐其上尚存一絲當年的封印之力。少俠帶回去﹐請那位陸師叔自個兒參詳罷——遲了﹐怕是來不及了。" :),
		(: give_shard, who :),
	}));
	return 1;
}

int accept_fight(object ob)
{
	do_chat((: command, "say 少俠息怒﹗老朽一個守墓掃灑的老頭子﹐當不起少俠這般動怒。" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
