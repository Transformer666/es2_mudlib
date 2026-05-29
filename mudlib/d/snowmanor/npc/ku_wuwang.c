// ku_wuwang.c -- 哭笑門左使 哭無望，寄寓雪吟莊東廂房（解仇任務伏筆）
//
// 設定（依 docs/01-世界觀與劇情/05-主線任務與NPC.md、04-玩家社群與文化/02-結仇與PvP.md）：
//   哭無望(Ku wu wang)﹐哭笑門左使﹐如今卻寄居在雪吟莊東廂房。他與本門門主
//   劉乙忘玄（哭笑判官﹐坐鎮青邪宮﹐修青邪杖法／大邪心法）之間生了嫌隙﹐
//   形同半個棄徒﹐借住魚鐵山莊上﹐落拓而鬱結。
//   他日後是「哭笑門解仇」任務的關鍵人物（解青邪宮之仇）﹐但結仇/解仇的完整
//   機制尚未實作——此處僅以隱晦、悲憤的對話埋下伏筆﹐不開任何任務。
//
// 與 d/qingxie/npc/master.c（劉乙忘玄）保持一致：青邪宮、青邪杖法、大邪心法、
//   哭笑判官、「入門容易出門難」等名物與口吻。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

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
		"日借酒澆愁。你或許可以問問他﹕ask ku about 哭笑門。\n");
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
			(: command, "say 後生﹐這筆帳遲早是要算的。只是時候未到 ... 你問這麼多作甚﹖" :),
		}));
		return 1;
	}

	// 問解仇 / 仇怨：點出日後「解青邪宮之仇」的方向，但此刻甚麼也開不了
	if( arg == "ku about 解仇"
	||  arg == "ku wu wang about 解仇"
	||  arg == "ku about 仇"
	||  arg == "ku about 恩怨"
	||  arg == "ku about grudge" ) {
		do_chat(({
			(: command, "say 解仇﹖你也惹上了青邪宮的人﹖嘿﹐那幫邪魔﹐記仇記得很。" :),
			(: command, "say 哭笑門的仇怨﹐終究要哭笑門的人來了。待有朝一日我與劉乙忘玄那筆舊帳算清了﹐這當口的恩怨﹐或許也有個了結的法子。" :),
			(: command, "say 只是眼下 ... 我自身尚且難保﹐幫不了你。你且記著我這句話便是。" :),
		}));
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
