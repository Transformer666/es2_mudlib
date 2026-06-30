// qiao_polang.c -- 喬破浪（Qiao Polang），棲身雪吟莊外木橋畔的雪吟莊棄徒（雪吟莊解仇）
//
// 設定（依 docs/04-玩家社群與文化/02-結仇與PvP.md L208「結仇五大派 → 各有解仇
//   路徑」﹐雪吟莊持久 vendetta/snow 此前無清除路徑）：
//   喬破浪是個被逐出雪吟莊的棄徒——他原是莊主魚鐵山帳下一名得力的家丁頭目﹐
//   後來看不慣魚鐵山日張的野心與莊上見血的家法﹐犯言頂撞﹐被逐出莊去。如今他
//   無處可歸﹐只在莊外這條通鎮的木橋畔搭了個窩棚苟且度日﹐成日望著莊門出神。
//   他熟知雪吟莊上下的脾性與規矩﹐莊中家丁、教頭多半還賣他三分舊情面﹔江湖人
//   與雪吟一脈結了死仇、不敢踏進莊門賠罪者（一進莊門便要被守門家丁圍攻）﹐多
//   半繞到這橋畔尋他說和。
//
//   ※ 立此檔（鏡哭無望寄寓雪吟莊之範式）並安置於【莊外木橋】之故：雪吟莊
//     vendetta/snow 結仇之 NPC（家丁/婢女/園丁/教頭/莊主）遍佈莊門、廂廊、後園、
//     演武場、正廳——【自莊門起】便有掛 snow mark 的守門家丁。snow-marked 玩家一
//     踏進莊門即遭 attack.c init() 自動圍攻﹐根本無法深入莊內尋人解仇。故雪吟莊
//     解仇者必須安置在【玩家進得去的莊外】﹐方屬可達。莊門西出即 /d/snow/ebridge
//     （木橋﹐橋上原有的青衣漢子是雪亭鎮 commoner、非 snow 陣營﹐不圍攻）﹐正是
//     marked 玩家逼近雪吟莊前最後一個安全落腳處——以「莊棄徒棲身橋畔」立人﹐既
//     合理可達﹐又呼應哭無望「半個棄徒、落拓寄寓」的範式。
//
// 解仇 service（嚴格鏡 d/snowmanor/npc/ku_wuwang.c 已驗範式）：
//   - 雪吟莊 faction 判定：本派 NPC 之共同硬標記為 query("vendetta_mark")=="snow"
//     （見 d/snowmanor/npc/retainer.c、maid.c、gardener.c、instructor.c、
//     yu_tieshan.c 皆 set("vendetta_mark","snow")）。注意雪吟莊 NPC class 不一
//     （家丁/教頭 fighter﹐婢女/園丁 commoner）、且家丁/婢女/園丁【未】set("sect")﹐
//     故判定不可沿用 class+sect（會漏解婢女園丁、且非本派之 fighter 亦不該誤解）﹐
//     一律以 vendetta_mark 為準——只認真正會結此仇的 NPC。
//   - 觸發：玩家 `ask polang about 解仇`（中文 topic 解仇/仇/化解/雪吟莊之仇 …）。
//     gate：玩家須當真與雪吟一脈結了仇（場上有仍記恨此玩家之雪吟莊 NPC﹐或身上
//     有持久 vendetta/snow）方有可解﹔破浪念在莊上舊情面免費說和一次。
//   - 化解：掃 livings() 中 clonep && !userp && query("vendetta_mark")=="snow"
//     && is_killing(who) 之 NPC﹐逐一【雙向】解仇 foe->remove_killer(who);
//     who->remove_killer(foe);﹐並清玩家身上持久 vendetta/snow﹐set
//     quest/qiaopolang_done=1。
//   - double-grant 防呆：已 done 者改述「早替你了結」之言﹐不重複說和。
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

#define SNOW_MARK       "snow"      // 雪吟莊陣營持久結仇 mark（query("vendetta/snow")）

int do_ask(string arg);

// 化解雪吟莊仇恨：掃出當前載入、仍記恨 who、且屬雪吟一脈
//（query("vendetta_mark")=="snow"）的 NPC，逐一雙向解仇；並清玩家身上持久
// vendetta/snow。回傳實際化解的雪吟莊 NPC 數目（供回報訊息參考）。
private int mediate_snow_enmity(object who)
{
	object *foes;
	int n;

	if( !who ) return 0;

	// livings() 取所有載入中的生物；過濾出 clone 的、非玩家的、仍記恨此玩家、
	// 且屬雪吟一脈（掛 vendetta_mark=="snow"）者。（鏡 /cmds/arch/overview.c
	// 的 livings()+屬性過濾、/d/snowmanor/npc/ku_wuwang.c 的 mediate handler。）
	foes = filter_array(livings(), (:
		objectp($1)
		&& clonep($1)
		&& !userp($1)
		&& $1->is_killing($(who))
		&& $1->query("vendetta_mark") == SNOW_MARK
	:));

	n = sizeof(foes);
	foreach(object foe in foes) {
		// 雙向解仇（鏡 /d/snow/npc/girl.c）：雪吟莊人忘卻此仇、玩家亦不再與之為敵。
		foe->remove_killer(who);
		who->remove_killer(foe);
	}

	// 持久結仇歸零（additive）：清玩家身上 query("vendetta/snow")。
	// vendetta 累積／圍攻機制見 adm/daemons/chard.c（殺帶 mark 之 NPC +1）、
	// feature/char/attack.c（進房 init() 查此值非零即自動開打）。
	// delete("vendetta/snow") 經 feature/dbase.c 對 slash-path 做巢狀 map_delete
	// ——只刪 vendetta 下的 snow 鍵，不動其他派別之 mark。
	if( who->query("vendetta/" + SNOW_MARK) )
		who->delete("vendetta/" + SNOW_MARK);

	return n;
}

void create()
{
	set_name("喬破浪", ({ "qiao polang", "polang", "qiao", "outcast" }));
	set("nickname", "雪吟棄徒");
	set_attr("str", 23);
	set_attr("dex", 22);
	set_attr("int", 21);
	set_attr("wis", 20);
	set_attr("spi", 20);
	set_attr("con", 22);
	set_attr("cor", 21);
	set_race("human");
	set_level(27);
	set_class("commoner");      // 已被逐出雪吟莊的棄徒，不再結雪吟之仇，故設 commoner

	set_skill("unarmed", 55);
	set_skill("blade", 75);
	set_skill("parry", 55);
	set_skill("dodge", 60);
	set_skill("force", 65);

	set("gender", "male");
	set("age", 41);
	set("long",
		"這是一個落魄潦倒的中年漢子﹐一身藏青勁裝早已洗得發白、補丁\n"
		"摞補丁﹐卻仍依稀看得出是雪吟莊家丁的舊裝束。他在這通鎮的木橋畔\n"
		"搭了個破窩棚棲身﹐成日望著橋東莊門的方向出神﹐眼底滿是悵惘與不\n"
		"甘。聽聞他原是莊主魚鐵山帳下一名得力的家丁頭目﹐後來看不慣莊上\n"
		"日張的野心與見血的家法﹐犯言頂撞﹐被逐出莊去﹐成了個無處可歸的\n"
		"棄徒。他熟知莊上下的脾性規矩﹐莊中家丁、教頭多半還賣他三分舊情。\n"
		"你或許可以問問他﹕ask polang about 雪吟莊﹐或 ask polang about 解仇。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"喬破浪蹲在窩棚前﹐望著橋東莊門的方向出神﹐久久不語。\n",
		"喬破浪扯了扯身上發白的舊勁裝﹐自嘲似地冷笑了一聲。\n",
		"喬破浪低聲咕噥﹕魚鐵山 ... 那點野心﹐遲早要把整座莊子拖進血海裡去。\n",
	}));
	setup();
	carry_money("coin", 60);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	// #14：招呼只對真人，加 interactive(this_player()) 護衛，免 NPC 互觸洗版。
	if( this_player() && interactive(this_player()) ) {
		if( !is_fighting() )
			do_chat((: command,
				"say 客人這是要過橋進莊﹖ ... 哼﹐莊裡那潭水﹐可比這橋下的溪水深得多。" :));
	}
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這個落魄的雪吟莊棄徒甚麼﹖（試試 ask polang about 雪吟莊）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("喬破浪正自望著莊門出神﹐懶得理你。\n");

	// 問雪吟莊 / 魚鐵山：道出他與雪吟一脈的舊怨 —— 解仇任務伏筆
	if( arg == "polang about 雪吟莊"
	||  arg == "qiao polang about 雪吟莊"
	||  arg == "polang about 魚鐵山"
	||  arg == "polang about 雪吟"
	||  arg == "polang about manor"
	||  arg == "polang about yu" ) {
		do_chat(({
			(: command, "say 雪吟莊麼 ... 我喬破浪在莊上當了十幾年家丁頭目﹐莊裡的規矩脾性﹐沒人比我更熟。" :),
			(: command, "say 可魚鐵山那點問鼎武林的野心﹐越來越藏不住了。莊上的家法見了血﹐我看不過眼﹐頂了他兩句﹐就這麼被逐了出來。" :),
			(: command, "say 莊裡那幫家丁、教頭﹐到底還念著我幾分舊情。你若不巧惹上了雪吟莊的人﹐莫往莊門裡硬闖——一進去就是個圍毆——ask polang about 解仇 便是。" :),
		}));
		return 1;
	}

	// 問解仇 / 仇怨：雪吟莊解仇 service —— 破浪念在莊上舊情面，出面說和。
	//   同步交付，旗標／訊息逕在本 handler 內寫就。
	if( arg == "polang about 解仇"
	||  arg == "qiao polang about 解仇"
	||  arg == "polang about 仇"
	||  arg == "polang about 化解"
	||  arg == "polang about 雪吟莊之仇"
	||  arg == "polang about 恩怨"
	||  arg == "polang about grudge" ) {
		object me;
		int cleared;
		int had_mark;

		me = this_player();
		if( !me || !interactive(me) )
			return notify_fail("這裡沒人問你的話。\n");

		// double-grant 防呆：已說和過者，不重複出面，改述早為了結之言。
		if( me->query("quest/qiaopolang_done") >= 1 ) {
			command("say 你跟雪吟莊那段仇怨﹐我早替你了結了﹐安心便是。");
			tell_object(me,
				"喬破浪自嘲似地一笑﹕我這點殘存的薄面﹐替你討一回也就罷了﹐莫指望第二回。\n");
			return 1;
		}

		// gate：玩家須當真與雪吟一脈結了仇方有可解。仇怨有二態——
		//   (1) 場上有仍記恨此玩家之雪吟莊 NPC（transient killer）；
		//   (2) 玩家身上有持久 vendetta/snow（即便此刻無此派 NPC 在場）。
		// 兩者任一成立即可說和。先記下持久 mark 之有無（mediate 內會清掉），
		//   再 mediate（同時做 transient 雙向解仇＋清持久 vendetta/snow）。
		had_mark = me->query("vendetta/" + SNOW_MARK) ? 1 : 0;
		cleared = mediate_snow_enmity(me);
		if( cleared <= 0 && !had_mark ) {
			command("say 解仇﹖你眼下並未惹上雪吟莊的人﹐何來仇怨可解﹖");
			command("say 哪日真與雪吟一脈結了死仇﹐再來尋我這落魄棄徒罷。");
			return 1;
		}

		// ── 同步交付（全在 handler 內直接完成，不走延遲 do_chat）──
		// 1. 設永久旗標（鐵則 #10 精神：關鍵狀態先落地）
		me->set("quest/qiaopolang_done", 1);
		// 2. mediate_snow_enmity 已完成 transient 雙向解仇＋清持久 vendetta/snow，
		//    此處只述其事。
		command("say 唉 ... 你也惹上了雪吟莊的人﹖也罷﹐看在我這點殘存的舊情面上﹐這個人情我替你說和了。");
		command("say 雪吟莊的仇怨﹐我這被逐的棄徒倒還勸得動幾分。你這段恩怨﹐就此一筆勾銷罷。");
		if( cleared > 0 )
			tell_object(me,
				"喬破浪站起身﹐自破窩棚裡摸出一面褪了色的舊腰牌﹐託過橋的莊客捎句話進莊去。不過\n"
				"片刻﹐你只覺方才還對你橫眉立目、必欲除之而後快的雪吟莊人﹐眼前 " + cleared +
				" 名與你\n結仇者﹐竟似一夕之間忘了你這號人物﹐恩怨盡釋。\n");
		else
			tell_object(me,
				"喬破浪站起身﹐自破窩棚裡摸出一面褪了色的舊腰牌﹐託過橋的莊客捎句話進莊去。你心頭\n"
				"一鬆——你與雪吟一脈那段宿怨﹐自此一筆勾銷﹐日後與雪吟莊人打照面﹐再不必擔心\n"
				"他們認出舊仇、拔刀相向了。\n");
		return 1;
	}

	// 問木橋 / 棄徒身世：閒談氣氛
	if( arg == "polang about 木橋"
	||  arg == "polang about 橋"
	||  arg == "polang about 棄徒"
	||  arg == "polang about bridge" ) {
		do_chat(({
			(: command, "say 這橋是雪吟莊對外的咽喉﹐莊裡莊外的人﹐都得從我眼皮底下過。" :),
			(: command, "say 我守在這橋頭﹐一半是無處可去﹐一半 ... 也是想看看魚鐵山那野心﹐到底要把這座莊子帶到哪一步去。" :),
		}));
		return 1;
	}

	return notify_fail("喬破浪只望著橋東莊門出神﹐並不答你。（試試 ask polang about 雪吟莊）\n");
}

// 棄徒到底是莊上練出來的身手，受襲自會還手。結仇機制未涉，此處僅作自衛反擊。
int accept_fight(object ob)
{
	do_chat((: command, "say 落魄歸落魄﹐我喬破浪在雪吟莊操練出來的本事﹐還沒荒到任你欺負﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
