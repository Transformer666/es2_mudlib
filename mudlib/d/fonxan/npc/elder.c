// elder.c -- 陸抱朴，封山派藏劍堂的師叔，主線任務二「殘卷尋蹤」的委託人
//
// 故事背景（承接主線一「卯木之兆」）：
//   雪亭鎮廟祝那封密報經師爺呈縣後﹐輾轉傳到了素來留意此事的封山派耳中。
//   封山派這位掌理劍譜典籍的師叔陸抱朴﹐多年來私下追查三百年前皇城聖木被斷、
//   侮天鬼破土的舊案﹐手裡有半部《封鬼遺錄》﹐獨缺記著「斷木放出何物」的那
//   一卷殘卷——那卷殘卷早年被一名訪客攜往喬陰縣衙存查﹐至今封存在卷庫裡。
//   陸抱朴年邁不便下山﹐又因封山派與縣衙素有嫌隙不便出面﹐遂託剛從雪亭鎮一
//   路追著卯木異兆而來的少俠﹐去喬陰縣衙把那卷殘卷討回。
//
// 任務流程（旗標存在玩家身上：quest/main_omen2）：
//   入門條件     : 須先完成主線一（quest/main_omen >= 3）﹐否則只給提示﹐不開任務
//   未開始 (0)   : 玩家 ask elder about 主線 -> 師叔交付「引薦帖」﹐旗標設為 1
//   進行中 (1)   : 玩家持引薦帖到喬陰縣衙﹐交(give)給掌卷的書吏(/d/qiaoyin/npc/archivist)
//                  書吏驗帖後收回引薦帖﹐回給「殘卷」﹐並把旗標推進為 2（推進在 archivist.c）
//   已取得 (2)   : 玩家把殘卷帶回藏劍堂交(give)給師叔 -> 領賞﹐旗標設為 3
//   已完成 (3)   : 不再重複給賞（防止重複領獎）

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("陸抱朴", ({ "fonxan elder", "elder", "lu baopu" }) );
	set("nickname", "藏劍師叔");
	set_attr("str", 18);
	set_attr("int", 24);
	set_attr("wis", 23);
	set_race("human");
	set_class("fighter");
	set_level(28);
	set("sect", "封山派");
	set("rank", "師叔");

	set_skill("sword", 90);
	set_skill("parry", 70);
	set_skill("dodge", 60);
	set_skill("force", 70);
	set_skill("literate", 60);
	set_skill("fonxansword", 90);
	set_skill("fonxanforce", 70);
	map_skill("sword", "fonxansword");
	map_skill("force", "fonxanforce");

	set("gender", "male");
	set("age", 63);
	set("long",
		"一位掌理封山派藏劍堂典籍的師叔﹐須髮花白﹐一襲半舊的青布長\n"
		"衫上沾著淡淡墨痕。他不似尋常劍客那般鋒芒外露﹐反倒像個埋首故\n"
		"紙堆的老學究﹐成日在格架間翻檢那些蟲蛀的舊卷。聽聞他年輕時也\n"
		"是劍法了得的人物﹐後來卻迷上了追查一樁三百年前的舊案﹐自此深\n"
		"居劍堂﹐與群書為伴。這幾日他翻卷翻得格外勤﹐眉宇間隱隱有憂色。\n"
		"你或許可以問問他﹕ask elder about 主線。\n");
	setup();
	carry_object("/obj/area/obj/cloth")->wear();
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player()) ) {
		int q = this_player()->query("quest/main_omen2");
		if( q == 1 || q == 2 )
			do_chat((: command,
				"say 少俠﹐喬陰縣衙那卷殘卷﹐可討回來了麼﹖" :));
		else if( !q && this_player()->query("quest/main_omen") >= 3 )
			do_chat((: command,
				"say 卯木夜啼 ... 嘶﹐這事老朽追了大半輩子了 ..." :));
	}
}

// 把一張引薦帖交到玩家手上（先複製到自己身上，再 give 出去）
private void give_letter(object who)
{
	object letter;

	if( !who || environment(who) != environment() ) {
		command("say 咦 ... 人呢﹖");
		return;
	}
	letter = new(__DIR__"obj/intro_letter");
	letter->move(this_object());
	command("give intro letter to " + who->query("id"));
}

// 領賞：給一串銅錢、一柄好劍、一帖傷藥﹐並授俠義之舉、聲望與旅行見聞
private void give_reward(object who)
{
	object coin, sword, berry;

	if( !who || environment(who) != environment() ) return;

	coin = new("/obj/money/coin");
	coin->set_amount(300);
	if( coin->move(who) ) coin->move(environment());

	sword = new("/d/snow/npc/obj/silversword");
	if( sword->move(who) ) sword->move(environment());

	berry = new("/obj/medication/boar_berry");
	if( berry->move(who) ) berry->move(environment());

	who->gain_score("survive", 300);
	who->gain_score("emprise", 100);
	who->gain_score("reputation", 50);
	who->gain_score("explorer fame", 50);

	message_vision(
		"陸抱朴自案頭取了一串銅錢與一帖傷藥﹐又從架上請下一柄封山派的"
		"佩劍﹐鄭重地交到$N手裡。\n",
		who);
}

int do_ask(string arg)
{
	object me = this_player();
	int q;

	if( !arg || (arg != "elder about 主線"
		&&   arg != "elder about 任務"
		&&   arg != "elder about 殘卷"
		&&   arg != "fonxan elder about 主線"
		&&   arg != "fonxan elder about 任務"
		&&   arg != "elder about quest"
		&&   arg != "elder about task") )
		return notify_fail("你想問這位師叔甚麼﹖（試試 ask elder about 主線）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("陸抱朴正凝神翻卷﹐沒空理你。\n");

	// 入門條件：須先完成主線一「卯木之兆」
	if( me->query("quest/main_omen") < 3 ) {
		do_chat(({
			(: command, "say 少俠面生﹐這藏劍堂的舊案﹐豈是逢人便說的﹖" :),
			(: command, "say 老朽聽聞雪亭鎮那株卯木近來夜半啼哭﹐土地神像落淚——少俠若也覺出蹊蹺﹐何不先去土地公廟見見那位廟祝？待你弄清了原委﹐老朽自有話與你說。" :),
		}));
		return 1;
	}

	q = me->query("quest/main_omen2");

	// 已全部完成
	if( q >= 3 ) {
		do_chat(({
			(: command, "say 那卷殘卷多虧少俠討了回來﹐老朽這半部《封鬼遺錄》﹐總算補齊了。" :),
			(: command, "say 只是 ... 卷上所記﹐比老朽想的還要兇險。三百年前斷木放出的那物﹐只怕從未真正被鎮住。" :),
			(: command, "say 此事老朽還得稟過掌門﹐再從長計議。少俠且先歇著﹐來日方長。" :),
		}));
		return 1;
	}

	// 已取得殘卷，回來交卷（理應用 give 交付，這裡只作提示）
	if( q == 2 ) {
		if( present("ancient fragment", me) )
			do_chat((: command,
				"say 殘卷討回來啦﹖快把那卷殘卷交(give)給老朽過目﹗" :));
		else
			do_chat((: command,
				"say 咦﹐那卷殘卷呢﹖少俠莫不是弄丟了﹖快回喬陰縣衙找那書吏補討一卷。" :));
		return 1;
	}

	// 任務進行中（還沒取回）
	if( q == 1 ) {
		if( present("intro letter", me) )
			do_chat((: command,
				"say 那引薦帖少俠帶在身上了。下山往西到喬陰市集﹐穿過縣前廣場往北﹐"
				"便是縣衙﹐把帖子交(give)給掌卷的書吏﹐討了那卷殘卷回來。" :));
		else
			// 萬一玩家把引薦帖弄丟了，補一張給他
			do_chat(({
				"陸抱朴搖頭嘆了口氣﹐又自案頭取了素箋﹐重新寫了一帖。\n",
				(: command, "say 怎麼帖子不見了﹖罷了﹐老朽再寫一張﹐少俠這回可收好了。" :),
				(: give_letter, me :),
			}));
		return 1;
	}

	// 尚未接任務：交付引薦帖，旗標設為 1
	me->set("quest/main_omen2", 1);
	do_chat(({
		(: command, "say 少俠既已查過卯木之事﹐老朽便不瞞你。我封山派這些年﹐一直在追那樁三百年前的舊案。" :),
		(: command, "say 三百年前﹐皇城那株鎮著天地的聖木被人攔腰斷了﹐自此放出個不該放的東西——卯木夜啼﹐怕正是那物又在蠢動的兆頭。" :),
		(: command, "say 老朽手裡有半部《封鬼遺錄》﹐獨缺記著『斷木放出何物』的那一卷殘卷。那殘卷早年被人帶去喬陰縣衙存了查﹐至今封在卷庫裡。" :),
		(: command, "say 怎奈封山派與縣衙素來不睦﹐老朽又年邁難行。少俠可願持老朽這封引薦帖﹐替我去縣衙把那卷殘卷討(give)回來﹖事成必有重謝﹗" :),
		(: give_letter, me :),
	}));
	return 1;
}

int accept_fight(object ob)
{
	do_chat((: command, "say 少俠何必動怒﹖老朽一介書蠹﹐與你無冤無仇。" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
