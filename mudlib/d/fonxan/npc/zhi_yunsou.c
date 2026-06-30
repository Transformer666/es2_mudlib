// zhi_yunsou.c -- 雲叟 支雲叟（Zhi Yunsou），結廬青嶂峰下的山中隱者（封山派解仇）
//
// 設定（依 docs/04-玩家社群與文化/02-結仇與PvP.md L208「結仇五大派 → 各有解仇
//   路徑」﹐封山派持久 vendetta/fonxan 此前無清除路徑）：
//   支雲叟是個避居青嶂峰下、與封山派淵源極深的山中老者——他年輕時曾與封山
//   派掌門柳東蘆同門論劍﹐後看破刀劍恩怨﹐結廬山門外、不問門派之爭﹐唯以調
//   停山中是非為念。封山派守正不阿、講「以靜制動」﹐獨不擅化解血仇﹔江湖人
//   與封山一脈結了死仇、不敢踏進前殿尋掌門賠罪者﹐多半繞到這山門外尋這位中
//   立的雲叟說和。他與柳東蘆有舊﹐遞句話、講個情面﹐封山派人多半也就罷手了。
//
// 解仇 service（嚴格鏡 d/snowmanor/npc/ku_wuwang.c 已驗範式）：
//   - 封山派 faction 判定：本派 NPC 之共同硬標記為 query("vendetta_mark")=="fonxan"
//     （見 d/fonxan/npc/master.c:51 掌門 set("vendetta_mark","fonxan")）。注意封山
//     派員工(如 elder)class=="fighter"、sect=="封山派" 卻【未】掛 vendetta_mark﹐
//     殺之不結仇﹔故判定以 vendetta_mark 為準（比 class+sect 更精確、只認真正會
//     結此仇的 NPC）﹐避免錯解無辜或漏解。
//   - 觸發：玩家 `ask yunsou about 解仇`（中文 topic 解仇/仇/化解/封山派之仇 …）。
//     gate：玩家須當真與封山一脈結了仇（場上有仍記恨此玩家之封山派 NPC﹐或身上
//     有持久 vendetta/fonxan）方有可解﹔雲叟念在與柳東蘆的舊情面免費說和一次。
//   - 化解：掃 livings() 中 clonep && !userp && query("vendetta_mark")=="fonxan"
//     && is_killing(who) 之 NPC﹐逐一【雙向】解仇 foe->remove_killer(who);
//     who->remove_killer(foe);﹐並清玩家身上持久 vendetta/fonxan﹐set
//     quest/zhiyunsou_done=1。
//   - double-grant 防呆：已 done 者改述「早為你了結」之言﹐不重複說和。
//   - 同步交付：解仇／設旗標／tell 全在 do_ask handler 內直接完成（純氣氛對白才
//     走 do_chat）。is_fighting()/is_chatting() 守衛於 do_ask 開頭。
//
// 機制來源（先 grep 既有檔模仿﹐未臆造 efun）：
//   仇恨儲存於各 NPC 自身 killer mapping（玩家 id 為鍵）﹐is_killing/remove_killer
//   為 include/attack.h 公開介面（feature/char/attack.c）。雙向解仇範式見
//   /d/snow/npc/girl.c﹔livings()+屬性過濾掃載入中 NPC 見 /cmds/arch/overview.c﹔
//   service/雙向解仇/旗標/防呆整鏈見 /d/snowmanor/npc/ku_wuwang.c、
//   /d/fengcheng/npc/rongfu_laoda.c。持久 vendetta 累積見 adm/daemons/chard.c、
//   進房 init() 查值自動圍攻見 feature/char/attack.c。
//
// 鐵則遵循：
//   #10：本檔無 ::die()/destruct()——旗標／訊息逕在 handler 內順序寫就。
//   #11：本檔為 NPC（非房間），不涉 replace_program。
//   #14：init() 招呼有 interactive(this_player()) 護衛（只招呼真人）。

#include <npc.h>

inherit F_VILLAGER;

#define FONXAN_MARK     "fonxan"     // 封山派陣營持久結仇 mark（query("vendetta/fonxan")）

int do_ask(string arg);

// 化解封山派仇恨：掃出當前載入、仍記恨 who、且屬封山一脈
//（query("vendetta_mark")=="fonxan"）的 NPC，逐一雙向解仇；並清玩家身上持久
// vendetta/fonxan。回傳實際化解的封山派 NPC 數目（供回報訊息參考）。
private int mediate_fonxan_enmity(object who)
{
	object *foes;
	int n;

	if( !who ) return 0;

	// livings() 取所有載入中的生物；過濾出 clone 的、非玩家的、仍記恨此玩家、
	// 且屬封山一脈（掛 vendetta_mark=="fonxan"）者。（鏡 /cmds/arch/overview.c
	// 的 livings()+屬性過濾、/d/snowmanor/npc/ku_wuwang.c 的 mediate handler。）
	foes = filter_array(livings(), (:
		objectp($1)
		&& clonep($1)
		&& !userp($1)
		&& $1->is_killing($(who))
		&& $1->query("vendetta_mark") == FONXAN_MARK
	:));

	n = sizeof(foes);
	foreach(object foe in foes) {
		// 雙向解仇（鏡 /d/snow/npc/girl.c）：封山派人忘卻此仇、玩家亦不再與之為敵。
		foe->remove_killer(who);
		who->remove_killer(foe);
	}

	// 持久結仇歸零（additive）：清玩家身上 query("vendetta/fonxan")。
	// vendetta 累積／圍攻機制見 adm/daemons/chard.c（殺帶 mark 之 NPC +1）、
	// feature/char/attack.c（進房 init() 查此值非零即自動開打）。
	// delete("vendetta/fonxan") 經 feature/dbase.c 對 slash-path 做巢狀 map_delete
	// ——只刪 vendetta 下的 fonxan 鍵，不動其他派別之 mark。
	if( who->query("vendetta/" + FONXAN_MARK) )
		who->delete("vendetta/" + FONXAN_MARK);

	return n;
}

void create()
{
	set_name("支雲叟", ({ "zhi yunsou", "yunsou", "zhi", "hermit" }));
	set("nickname", "青嶂雲叟");
	set_attr("str", 20);
	set_attr("dex", 21);
	set_attr("int", 24);
	set_attr("wis", 25);
	set_attr("spi", 23);
	set_attr("con", 21);
	set_attr("cor", 18);
	set_race("human");
	set_level(28);
	set_class("commoner");      // 看破恩怨的山中隱者，不結封山之仇，故設 commoner

	set_skill("unarmed", 50);
	set_skill("dodge", 70);
	set_skill("parry", 50);
	set_skill("force", 80);

	set("gender", "male");
	set("age", 61);
	set("long",
		"這是一位鶴髮童顏的山中老者﹐一襲半舊的灰布道袍﹐鬚眉皆白卻\n"
		"梳理得一絲不苟。他結廬在這封山派的山門之外﹐青嶂峰下﹐既不入封\n"
		"山的門牆﹐也不沾江湖的恩怨﹐終日只在松下煮茶看雲﹐神情沖和恬淡。\n"
		"聽聞他年輕時曾與封山掌門柳東蘆同門論劍﹐後來看破了刀劍裡的血仇\n"
		"宿怨﹐這才避居山外做個閒雲野鶴﹐唯以調停山中是非為念。江湖人若\n"
		"與封山一脈結了死仇、不敢踏進前殿賠罪﹐多半繞來尋他說和。你或許\n"
		"可以問問他﹕ask yunsou about 封山派﹐或 ask yunsou about 解仇。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"支雲叟拈起一片松針﹐就著爐上的茶煙出神﹐神情說不出的恬淡。\n",
		"支雲叟撫著長鬚﹐悠悠道﹕劍勢如山易﹐心境如水難哪。\n",
		"支雲叟望著前殿的方向﹐微微一笑﹕東蘆那老倔頭﹐守了一輩子的劍﹐倒不曾守住自己的執念。\n",
	}));
	setup();
	carry_money("coin", 80);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	// #14：招呼只對真人，加 interactive(this_player()) 護衛，免 NPC 互觸洗版。
	if( this_player() && interactive(this_player()) ) {
		if( !is_fighting() )
			do_chat((: command,
				"say 山客遠來﹐且坐下吃杯粗茶。有甚麼放不下的﹐不妨說來聽聽。" :));
	}
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這位山中老者甚麼﹖（試試 ask yunsou about 封山派）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("支雲叟正自煮茶看雲﹐且待他閒了再問。\n");

	// 問封山派 / 柳東蘆：道出他與封山一脈的淵源 —— 解仇任務伏筆
	if( arg == "yunsou about 封山派"
	||  arg == "zhi yunsou about 封山派"
	||  arg == "yunsou about 柳東蘆"
	||  arg == "yunsou about 封山"
	||  arg == "yunsou about fonxan"
	||  arg == "yunsou about liu" ) {
		do_chat(({
			(: command, "say 封山派麼 ... 當年我與東蘆同在一處學劍﹐他守正不阿﹐一柄劍守了一座山、一條心。" :),
			(: command, "say 只是這守山的劍守得住山門﹐守不住人心裡的恨。封山派的人記仇極深﹐結了仇便是死纏到底。" :),
			(: command, "say 我看破了這刀劍裡的恩怨﹐這才避到山外來煮茶看雲。後生﹐你若與封山一脈結了甚麼死仇﹐莫往前殿硬闖——ask yunsou about 解仇 便是。" :),
		}));
		return 1;
	}

	// 問解仇 / 仇怨：封山派解仇 service —— 雲叟念在與柳東蘆的舊情面，出面說和。
	//   同步交付，旗標／訊息逕在本 handler 內寫就。
	if( arg == "yunsou about 解仇"
	||  arg == "zhi yunsou about 解仇"
	||  arg == "yunsou about 仇"
	||  arg == "yunsou about 化解"
	||  arg == "yunsou about 封山派之仇"
	||  arg == "yunsou about 恩怨"
	||  arg == "yunsou about grudge" ) {
		object me;
		int cleared;
		int had_mark;

		me = this_player();
		if( !me || !interactive(me) )
			return notify_fail("這裡沒人問你的話。\n");

		// double-grant 防呆：已說和過者，不重複出面，改述早為了結之言。
		if( me->query("quest/zhiyunsou_done") >= 1 ) {
			command("say 你與封山那段仇怨﹐老朽早替你說和了結了﹐安心便是。");
			tell_object(me,
				"支雲叟撫鬚淡淡一笑﹕同樣的人情﹐老朽可不便厚著臉皮去討第二回。\n");
			return 1;
		}

		// gate：玩家須當真與封山一脈結了仇方有可解。仇怨有二態——
		//   (1) 場上有仍記恨此玩家之封山派 NPC（transient killer）；
		//   (2) 玩家身上有持久 vendetta/fonxan（即便此刻無此派 NPC 在場）。
		// 兩者任一成立即可說和。先記下持久 mark 之有無（mediate 內會清掉），
		//   再 mediate（同時做 transient 雙向解仇＋清持久 vendetta/fonxan）。
		had_mark = me->query("vendetta/" + FONXAN_MARK) ? 1 : 0;
		cleared = mediate_fonxan_enmity(me);
		if( cleared <= 0 && !had_mark ) {
			command("say 解仇﹖你眼下並未惹上封山的人﹐何來仇怨可解﹖");
			command("say 哪日真與封山一脈結了死仇﹐再繞來尋老朽這把老骨頭罷。");
			return 1;
		}

		// ── 同步交付（全在 handler 內直接完成，不走延遲 do_chat）──
		// 1. 設永久旗標（鐵則 #10 精神：關鍵狀態先落地）
		me->set("quest/zhiyunsou_done", 1);
		// 2. mediate_fonxan_enmity 已完成 transient 雙向解仇＋清持久 vendetta/fonxan，
		//    此處只述其事。
		command("say 唉 ... 你也與封山的人結下了死仇﹖也罷﹐看在老朽與東蘆同門一場的份上﹐這個情面老朽替你討了。");
		command("say 封山的劍守的是個「正」字﹐冤有頭債有主﹐這場仇怨﹐就此一筆勾銷罷。");
		if( cleared > 0 )
			tell_object(me,
				"支雲叟擱下茶盞﹐自袖中取出一方刻著舊劍紋的木牌﹐託人帶句話往前殿去。不過片刻\n"
				"工夫﹐你只覺方才還對你橫眉立目、必欲除之而後快的封山派人﹐眼前 " + cleared +
				" 名與你\n結仇者﹐竟似一夕之間忘了你這號人物﹐恩怨盡釋。\n");
		else
			tell_object(me,
				"支雲叟擱下茶盞﹐自袖中取出一方刻著舊劍紋的木牌﹐託人帶句話往前殿去。你心頭一鬆\n"
				"——你與封山一脈那段宿怨﹐自此一筆勾銷﹐日後與封山派人打照面﹐再不必擔心他們\n"
				"認出舊仇、拔劍相向了。\n");
		return 1;
	}

	// 問青嶂峰 / 看雲煮茶：閒談氣氛
	if( arg == "yunsou about 青嶂峰"
	||  arg == "yunsou about 青嶂"
	||  arg == "yunsou about 茶"
	||  arg == "yunsou about peak" ) {
		do_chat(({
			(: command, "say 這青嶂峰呵﹐雲來雲去﹐看了幾十年﹐倒比那滿山的劍痕耐看。" :),
			(: command, "say 山中無甲子﹐煮一壺茶、看一回雲﹐恩怨是非便都淡了。後生﹐你眉宇間戾氣太重﹐該歇歇了。" :),
		}));
		return 1;
	}

	return notify_fail("支雲叟只是含笑望著你﹐並不答話。（試試 ask yunsou about 封山派）\n");
}

// 山中隱者亦有護身之能，受襲自會閃避反擊。結仇機制未涉，此處僅作自衛。
int accept_fight(object ob)
{
	do_chat((: command, "say 後生﹐老朽一片好心與你說和﹐你卻要動粗﹖且看你拿不拿得住老朽。" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
