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
//   已取得 (2)   : 玩家把殘卷帶回藏劍堂交(give)給師叔 -> 領賞(give_reward)﹐旗標設為 3
//   已完成 (3)   : 不再重複給賞（防止重複領獎）
//
// 主線任務三「聖木探封」（旗標：quest/main_omen3﹐入門條件 main_omen2 >= 3）：
//   本 NPC 同時是主線三的委託人與領賞人。do_ask 的 q>=3 分支即主線三的調度。
//   未開始 (0)   : ask elder about 主線 -> 掌門柳東蘆已閱《封鬼遺錄》﹐交付「封山派文書」
//                  (sect dispatch)﹐命少俠往京畿神社尋守木老者﹐旗標設為 1
//   進行中 (1)   : 玩家持文書到京畿神社﹐交(give)給守木老者(/d/capital/npc/shrinekeeper)
//                  老者驗書後收回文書﹐道出封印將潰之實﹐回給「聖木殘片」(saintwood
//                  shard)﹐並把旗標推進為 2（推進在 shrinekeeper.c）
//   已取得 (2)   : 玩家把聖木殘片帶回藏劍堂交(give)給師叔 -> 領賞(give_reward3)﹐旗標設為 3
//   已完成 (3)   : 不再重複給賞﹐do_ask 給出朝向動物war／侮天鬼一段的純劇情伏筆

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
	if( !coin->move(who) ) coin->move(environment());

	sword = new("/d/snow/npc/obj/silversword");
	if( !sword->move(who) ) sword->move(environment());

	berry = new("/obj/medication/boar_berry");
	if( !berry->move(who) ) berry->move(environment());

	who->gain_score("survive", 300);
	who->gain_score("emprise", 100);
	who->gain_score("reputation", 50);
	who->gain_score("explorer fame", 50);

	message_vision(
		"陸抱朴自案頭取了一串銅錢與一帖傷藥﹐又從架上請下一柄封山派的"
		"佩劍﹐鄭重地交到$N手裡。\n",
		who);
}

// 主線三「聖木探封」：把一紙封山派文書交到玩家手上（先複製到自己身上，再 give 出去）
private void give_dispatch(object who)
{
	object doc;

	if( !who || environment(who) != environment() ) {
		command("say 咦 ... 人呢﹖");
		return;
	}
	doc = new(__DIR__"obj/sect_dispatch");
	doc->move(this_object());
	command("give sect dispatch to " + who->query("id"));
}

// 主線三「聖木探封」領賞：給銅錢、一帖傷藥﹐並授俠義之舉、聲望與旅行見聞
private void give_reward3(object who)
{
	object coin, pill;

	if( !who || environment(who) != environment() ) return;

	coin = new("/obj/money/coin");
	coin->set_amount(400);
	if( !coin->move(who) ) coin->move(environment());

	pill = new("/obj/medication/alchemist/aquapill");
	if( !pill->move(who) ) pill->move(environment());

	who->gain_score("survive", 400);
	who->gain_score("emprise", 150);
	who->gain_score("reputation", 80);

	message_vision(
		"陸抱朴小心翼翼地將那片殘木供在案頭﹐凝視良久﹐才自匣中取了一串"
		"銅錢與一帖金液丹﹐鄭重地交到$N手裡。\n",
		who);
}

int do_ask(string arg)
{
	object me = this_player();
	int q, q3;

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

	// 主線二已全部完成（殘卷已交還）：此處轉為主線三「聖木探封」的調度
	if( q >= 3 ) {
		q3 = me->query("quest/main_omen3");

		// 主線三已全部完成：收尾、埋下動物war／侮天鬼一段的伏筆（純劇情，不開任何任務）
		if( q3 >= 3 ) {
			do_chat(({
				(: command, "say 那片聖木殘片老朽參詳了數日﹐其上封印之力果然將盡——守木老者所言非虛﹐那物快要復出了。" :),
				(: command, "say 老朽已飛書稟過掌門。掌門說﹐當年斷木放出的﹐乃是天靈山那頭悔天鬼的爪牙﹐如今怕是連深山裡的走獸都要受其蠱惑而生亂。" :),
				(: command, "say 聽聞那物與一顆喚作『混沌珠』的邪物相連﹐又有摩雲一脈在暗中覬覦。少俠且養精蓄銳﹐來日這場禍事﹐只怕還要仰仗你。" :),
			}));
			return 1;
		}

		// 主線三已取得聖木殘片，回來交付（理應用 give 交付，這裡只作提示）
		if( q3 == 2 ) {
			if( present("saintwood shard", me) )
				do_chat((: command,
					"say 京畿神社那一趟可有著落﹖快把那片聖木殘片交(give)給老朽過目﹗" :));
			else
				do_chat((: command,
					"say 咦﹐那片聖木殘片呢﹖少俠莫不是弄丟了﹖快回京畿神社找那守木老者補取一片。" :));
			return 1;
		}

		// 主線三進行中（已領文書，還沒回來）
		if( q3 == 1 ) {
			if( present("sect dispatch", me) )
				do_chat((: command,
					"say 那紙文書少俠帶在身上了。下山往京畿去﹐到了帝都﹐自皇城廣場往北便是京畿神社﹐"
					"尋著那位守木的老者﹐把文書交(give)給他﹐問清聖木封印的虛實。" :));
			else
				// 萬一玩家把文書弄丟了，補一紙給他
				do_chat(({
					"陸抱朴搖頭嘆了口氣﹐又自案頭取了黃綾﹐重新具了一紙文書鈐上掌門的印。\n",
					(: command, "say 怎麼文書不見了﹖罷了﹐老朽再具一紙﹐少俠這回可收好了。" :),
					(: give_dispatch, me :),
				}));
			return 1;
		}

		// 主線三尚未開啟：掌門已閱《封鬼遺錄》﹐交付封山派文書﹐旗標設為 1
		me->set("quest/main_omen3", 1);
		do_chat(({
			(: command, "say 那卷殘卷多虧少俠討了回來﹐老朽這半部《封鬼遺錄》﹐總算補齊了。卷上所記﹐比老朽想的還要兇險——三百年前斷木放出的那物﹐只怕從未真正被鎮住。" :),
			(: command, "say 老朽已將補齊的《封鬼遺錄》稟過掌門柳東蘆。掌門閱罷﹐命老朽托一個信得過的人﹐持封山派文書往京畿神社走一趟。" :),
			(: command, "say 那京畿神社的神龕後頭﹐有一截焦黑的老樹樁﹐相傳便是三百年前那株聖木被斷的舊址﹐有位老者世代留守。少俠可願持這紙文書去尋他﹐問清那道封印如今的虛實﹖" :),
			(: command, "say 切記﹕到了神社﹐須把文書交(give)給那守木老者﹐再問他舊事。事關天下安危﹐萬望少俠謹慎﹗" :),
			(: give_dispatch, me :),
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

// 收下信物：
//   殘卷(ancient fragment)   -- 主線二「殘卷尋蹤」交還﹐旗標 main_omen2 2 -> 3﹐領賞(give_reward)
//   聖木殘片(saintwood shard) -- 主線三「聖木探封」交還﹐旗標 main_omen3 2 -> 3﹐領賞(give_reward3)
// 兩者皆收下後不自行 destruct﹐由 give 指令將信物移入本 NPC（與 archivist 等一致）﹐
// 並於最終旗標處作防重複領獎。
int accept_object(object who, object ob)
{
	// 主線二：交還《封鬼遺錄》殘卷
	if( ob->id("ancient fragment") ) {
		// 已領過賞（旗標已 >=3）：道謝收下﹐不重複給賞
		if( who->query("quest/main_omen2") >= 3 ) {
			do_chat((: command, "say 這卷殘卷老朽早已收訖﹐多謝少俠了﹗" :));
			return 1;
		}
		// 尚未進行到交卷這一步（旗標不為 2）：仍收下避免卡物﹐但不推進、不給賞
		if( who->query("quest/main_omen2") != 2 ) {
			do_chat((: command, "say 多謝少俠﹗" :));
			return 1;
		}

		// 同步給賞、即記旗標（give_reward 為直接 new+move﹐玩家此刻必在場）。
		// 不把給賞放進延遲的 do_chat——免玩家於回呼前離場致賞沒領、旗標卻記完成而卡關。
		give_reward(who);
		who->set("quest/main_omen2", 3);
		do_chat(({
			(: command, "say 正是那卷殘卷﹗老朽這半部《封鬼遺錄》﹐總算補齊了﹗少俠辦事真是俐落﹗" :),
			(: command, "say 這點薄禮少俠拿著﹐銅錢防身﹐傷藥備急﹐這柄封山佩劍便贈與少俠了。" :),
		}));
		return 1;
	}

	// 主線三：交還聖木殘片
	if( ob->id("saintwood shard") ) {
		// 已領過賞（旗標已 >=3）：道謝收下﹐不重複給賞
		if( who->query("quest/main_omen3") >= 3 ) {
			do_chat((: command, "say 那片殘木老朽早已收訖﹐正日夜參詳著﹐多謝少俠了﹗" :));
			return 1;
		}
		// 尚未進行到交付這一步（旗標不為 2）：仍收下避免卡物﹐但不推進、不給賞
		if( who->query("quest/main_omen3") != 2 ) {
			do_chat((: command, "say 多謝少俠﹗" :));
			return 1;
		}

		// 同步給賞、即記旗標（give_reward3 為直接 new+move﹐玩家此刻必在場）。
		// 不把給賞放進延遲的 do_chat——免玩家於回呼前離場致賞沒領、旗標卻記完成而卡關。
		give_reward3(who);
		who->set("quest/main_omen3", 3);
		do_chat(({
			(: command, "say 這便是聖木的殘片麼 ... 嘶﹐其上封印之力果然將盡。守木老者所言﹐看來半分不假。" :),
			(: command, "say 少俠這一趟﹐功不可沒。此事老朽即刻飛書稟報掌門﹐少俠且先歇息﹐養精蓄銳——只怕來日這場禍事﹐還要仰仗你。" :),
		}));
		return 1;
	}

	// 其餘物事：婉拒﹐不收下（避免吞掉玩家的尋常物品）
	do_chat((: command, "say 這個老朽用不上﹐少俠還是自個兒留著罷。" :));
	return 0;
}

int accept_fight(object ob)
{
	do_chat((: command, "say 少俠何必動怒﹖老朽一介書蠹﹐與你無冤無仇。" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
