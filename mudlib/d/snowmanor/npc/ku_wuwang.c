// ku_wuwang.c -- 哭笑門左使 哭無望，寄寓雪吟莊東廂房（解仇任務）
//
// 設定（依 docs/01-世界觀與劇情/05-主線任務與NPC.md L111「哭無望 雪吟莊東廂房
//   解仇任務（哭笑門左使）」、04-玩家社群與文化/02-結仇與PvP.md）：
//   哭無望(Ku wu wang)﹐哭笑門左使﹐如今卻寄居在雪吟莊東廂房。他與本門門主
//   劉乙忘玄（哭笑判官﹐坐鎮青邪宮﹐修青邪杖法／大邪心法）之間生了嫌隙﹐
//   形同半個棄徒﹐借住魚鐵山莊上﹐落拓而鬱結。
//   他是「哭笑門解仇」任務的關鍵人物（解青邪宮之仇）——以左使身份出面斡旋﹐
//   化解玩家與哭笑門一派的仇恨。
//
// 與 d/qingxie/npc/master.c（劉乙忘玄）保持一致：青邪宮、青邪杖法、大邪心法、
//   哭笑判官、「入門容易出門難」等名物與口吻。
//
// 解仇 service（鏡既有已驗範式）：
//   - 哭笑門 faction 判定：該派 NPC 為 class=="fighter" 且 query("sect")=="哭笑門"
//     （門主 d/qingxie/npc/master.c 入門時 me->set("sect","哭笑門")；判定鍵亦
//     沿用全 mudlib 通用之 query("sect")，見各派 master.c 進階驗證）。
//   - 觸發：玩家 `ask kuwuwang about 解仇`（中文 topic 解仇/仇/化解/哭笑門之仇 …
//     沿用既有 ids 與對白風格）。gate：玩家須當真與哭笑門一派結了仇（場上有
//     仍記恨此玩家之哭笑門 NPC）方有可解；左使念在同門情面免費出面斡旋一次。
//   - 化解：掃 livings() 中 clonep && !userp && class=="fighter" &&
//     query("sect")=="哭笑門" && is_killing(who) 之 NPC﹐逐一【雙向】解仇
//     foe->remove_killer(who); who->remove_killer(foe);﹐set quest/kuwuwang_done=1。
//   - double-grant 防呆：已 done 者改述「早為你了結」之言﹐不重複斡旋。
//   - 同步交付：解仇／設旗標／tell 全在 do_ask handler 內直接完成﹐不丟進延遲
//     do_chat closure（純氣氛對白才走 do_chat）。is_fighting()/is_chatting() 守衛
//     於 do_ask 開頭（既有）。
//
// 「實際化解仇恨」機制（先 grep 既有檔模仿，未臆造 efun）：
//   ES2 仇恨儲存在「每個 NPC 自身」的 killer mapping（以玩家 id 字串為鍵）
//   ——見 /feature/char/attack.c：is_killing(who) 查玩家是否在某 NPC killer 名單﹐
//   remove_killer(ob) 刪鍵並移出 enemy（玩家以 id 鍵、NPC 以物件本身鍵）。
//   is_killing/remove_killer 為 include/attack.h 公開介面。雙向解仇範式見
//   /d/snow/npc/girl.c；以 livings()+屬性過濾掃載入中 NPC 範式見
//   /cmds/arch/overview.c；service/雙向解仇/旗標/防呆整鏈範式見
//   /d/fengcheng/npc/rongfu_laoda.c（mediate_soldier_enmity）。
//
// 鐵則遵循：
//   #10：本檔無 ::die()/destruct()——旗標／訊息逕在 handler 內順序寫就。
//   #11：本檔為 NPC（非房間），不涉 replace_program。

#include <npc.h>

inherit F_VILLAGER;

#define KUXIAO_SECT     "哭笑門"     // 哭笑門 faction 判定值（query("sect")）

int do_ask(string arg);

// 化解哭笑門仇恨：掃出當前載入、仍記恨 who、且屬哭笑門一派
//（class=="fighter" 且 query("sect")=="哭笑門"）的 NPC，逐一雙向解仇。
// 回傳實際化解的哭笑門 NPC 數目（供回報訊息參考）。
private int mediate_kuxiao_enmity(object who)
{
	object *foes;
	int n;

	if( !who ) return 0;

	// livings() 取所有載入中的生物；過濾出 clone 的、非玩家的、仍記恨此玩家、
	// 且屬哭笑門一派者。（鏡 /cmds/arch/overview.c 的 livings()+屬性過濾、
	// /d/fengcheng/npc/rongfu_laoda.c 的 mediate_soldier_enmity。）
	foes = filter_array(livings(), (:
		objectp($1)
		&& clonep($1)
		&& !userp($1)
		&& $1->is_killing($(who))
		&& $1->query_class() == "fighter"
		&& $1->query("sect") == KUXIAO_SECT
	:));

	n = sizeof(foes);
	foreach(object foe in foes) {
		// 雙向解仇（鏡 /d/snow/npc/girl.c）：哭笑門人忘卻此仇、玩家亦不再與之為敵。
		foe->remove_killer(who);
		who->remove_killer(foe);
	}
	return n;
}

void create()
{
	set_name("哭無望", ({ "ku wu wang", "ku", "wuwang", "ku zuoshi" }));
	set("nickname", "哭笑左使");
	set_attr("str", 22);
	set_attr("dex", 24);
	set_attr("int", 22);
	set_attr("wis", 21);
	set_attr("spi", 20);
	set_attr("con", 22);
	set_attr("cor", 16);
	set_race("human");
	set_level(30);
	set_class("fighter");
	set("sect", "哭笑門");
	set("rank", "左使");

	set_skill("unarmed", 70);
	set_skill("staff", 110);
	set_skill("parry", 100);
	set_skill("dodge", 90);
	set_skill("force", 100);

	set("gender", "male");
	set("age", 44);
	set("long",
		"這是一位形容枯槁的中年人﹐一身洗得發灰的玄黑長袍——那原是\n"
		"哭笑門的服色。他半邊臉似笑非笑﹐另半邊卻凝著化不開的鬱色﹐恰\n"
		"是哭笑門人特有的怪異神情。他斜倚窗前﹐手裡握著一只酒盞﹐眼底\n"
		"盛著說不盡的悲憤與落寞。聽聞他本是哭笑門左使﹐一身青邪杖法練\n"
		"得極是了得﹐卻因與門主劉乙忘玄生了嫌隙﹐避居到這雪吟莊來﹐成\n"
		"日借酒澆愁。你或許可以問問他﹕ask ku about 哭笑門﹐或 ask ku about 解仇。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"哭無望舉盞一飲而盡﹐半邊臉在笑﹐半邊臉卻像在哭。\n",
		"哭無望喃喃道﹕青邪宮 ... 哼﹐那也配叫師門﹖\n",
		"哭無望望著窗外的高牆出神﹐長長嘆了口氣。\n",
	}));
	setup();
	carry_object("/obj/area/obj/robe")->wear();
	carry_money("coin", 120);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player()) ) {
		if( !is_fighting() )
			do_chat((: command,
				"say 又是個面生的後生 ... 也罷﹐你要問甚麼﹖" :));
	}
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這位落拓的左使甚麼﹖（試試 ask ku about 哭笑門）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("哭無望正自借酒澆愁﹐懶得理你。\n");

	// 問哭笑門 / 劉乙忘玄：悲憤隱晦﹐道破與門主的嫌隙 —— 解仇任務伏筆
	if( arg == "ku about 哭笑門"
	||  arg == "ku wu wang about 哭笑門"
	||  arg == "ku about 劉乙忘玄"
	||  arg == "ku wu wang about 劉乙忘玄"
	||  arg == "ku about 忘玄"
	||  arg == "ku about 青邪宮"
	||  arg == "ku about 青邪"
	||  arg == "ku about kuxiao"
	||  arg == "ku about liu" ) {
		do_chat(({
			(: command, "say 哭笑門 ... 哈﹐哭笑判官劉乙忘玄那一套青邪杖法、大邪心法﹐我哭無望當年練得不比任何人差。" :),
			(: command, "say 可你道那青邪宮是甚麼好去處﹖入門容易出門難——這話我如今才嚼出味來。" :),
			(: command, "say 我與那姓劉的早已恩斷義絕。他做的那些見不得光的勾當﹐我不願再沾﹐這才避到魚莊主這兒來苟且偷生。" :),
			(: command, "say 後生﹐這筆帳遲早是要算的。你若也與青邪宮那幫人結了仇﹐看在同門份上﹐我或可替你斡旋——ask ku about 解仇 便是。" :),
		}));
		return 1;
	}

	// 問解仇 / 仇怨：哭笑門解仇 service —— 左使念在同門情面，出面化解玩家
	//   與哭笑門一派（青邪宮）的仇恨。同步交付，旗標／訊息逕在本 handler 內寫就。
	if( arg == "ku about 解仇"
	||  arg == "ku wu wang about 解仇"
	||  arg == "ku about 仇"
	||  arg == "ku about 化解"
	||  arg == "ku about 哭笑門之仇"
	||  arg == "ku about 恩怨"
	||  arg == "ku about grudge" ) {
		object me;
		int cleared;

		me = this_player();
		if( !me || !interactive(me) )
			return notify_fail("這裡沒人問你的話。\n");

		// double-grant 防呆：已斡旋過者，不重複出面，改述早為了結之言。
		if( me->query("quest/kuwuwang_done") >= 1 ) {
			command("say 你與我哭笑門那段仇怨﹐我早為你了結了﹐安心便是。");
			tell_object(me,
				"哭無望半邊臉笑著﹐半邊臉哭著﹐淡淡道﹕同樣的人情﹐我可不做第二回。\n");
			return 1;
		}

		// gate：玩家須當真與哭笑門一派結了仇（場上有仍記恨此玩家之哭笑門 NPC）
		//   方有可解。先化解、後依結果說辭；化解＝0 則表此刻並無此派之仇。
		cleared = mediate_kuxiao_enmity(me);
		if( cleared <= 0 ) {
			command("say 解仇﹖你眼下並未惹上我哭笑門的人﹐何來仇怨可解﹖");
			command("say 哪日真與青邪宮那幫人結了死仇﹐再來尋我這落魄左使罷。");
			return 1;
		}

		// ── 同步交付（全在 handler 內直接完成，不走延遲 do_chat）──
		// 1. 設永久旗標（鐵則 #10 精神：關鍵狀態先落地）
		me->set("quest/kuwuwang_done", 1);
		// 2. cleared 已由 mediate_kuxiao_enmity 完成雙向解仇，此處只述其事。
		command("say 嘿 ... 你也惹上了青邪宮的人﹖也罷﹐看在同門一場的份上﹐這人情我替你了了。");
		command("say 哭笑門的仇怨﹐終究要哭笑門的人來了。劉乙忘玄那筆舊帳是我的﹐你這當口的恩怨﹐就此一筆勾銷。");
		tell_object(me,
			"哭無望擱下酒盞﹐半邊臉似笑非笑﹐取出一方褪色的舊門牌在掌心摩挲﹐口中念念\n"
			"有詞。你只覺方才還對你橫眉立目、必欲除之而後快的哭笑門人﹐眼前 " + cleared +
			" 名與你\n結仇者﹐竟似一夕之間忘了你這號人物﹐恩怨盡釋。\n");
		return 1;
	}

	// 問雪吟莊 / 魚鐵山：左使的旁觀視角﹐隱隱透出兩人之間的詭異關係（伏筆）
	if( arg == "ku about 雪吟莊"
	||  arg == "ku about 魚鐵山"
	||  arg == "ku wu wang about 魚鐵山"
	||  arg == "ku about yu"
	||  arg == "ku about manor" ) {
		do_chat(({
			(: command, "say 魚莊主麼 ... 他肯收留我這麼個落魄人﹐自有他的盤算。" :),
			(: command, "say 他與我那位前門主﹐私下裡來往得可不清不楚。至於圖謀些甚麼——後生﹐有些事﹐知道得越少﹐活得越長。" :),
		}));
		return 1;
	}

	return notify_fail("哭無望半邊臉笑著﹐半邊臉哭著﹐並不答你。（試試 ask ku about 哭笑門）\n");
}

// 左使究竟是練家子﹐受襲自會還手。結仇機制未實作﹐此處僅作自衛反擊。
int accept_fight(object ob)
{
	do_chat((: command, "say 落魄歸落魄﹐我哭笑門左使的功夫﹐也不是你能放肆的﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
