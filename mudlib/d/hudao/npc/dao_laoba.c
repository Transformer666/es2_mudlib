// dao_laoba.c -- 刀疤老把 巴老把（Ba Laoba），盤踞老松林口的退隱刀客（虎刀門解仇）
//
// 設定（依 docs/04-玩家社群與文化/02-結仇與PvP.md L208「結仇五大派 → 各有解仇
//   路徑」﹐虎刀門持久 vendetta/tiger 此前無清除路徑）：
//   巴老把是個一身刀疤的退隱老刀客——當年也是老松林裡與虎刀門門主高慎一道
//   出生入死、亮刀見血的老兄弟﹐後來年歲大了、刀也快不動了﹐便在這林口搭了
//   個草棚﹐替過往的行旅看看刀、說說江湖。虎刀門收徒不問出身、只重一個「膽」
//   字﹐結起仇來也是快狠決絕、見人就砍﹔江湖人與虎刀一脈結了死仇、不敢踏進
//   刀堂尋高慎賠罪者﹐多半在這林口尋這位老把說合。他與高慎是過命的交情﹐喝
//   碗酒、撂句話﹐虎刀門人多半也就收刀作罷了。
//
// 解仇 service（嚴格鏡 d/snowmanor/npc/ku_wuwang.c 已驗範式）：
//   - 虎刀門 faction 判定：本派 NPC 之共同硬標記為 query("vendetta_mark")=="tiger"
//     （見 d/hudao/npc/master.c:51 門主 set("vendetta_mark","tiger")）。注意虎刀門
//     林中的 woodsman/hunter 是 commoner、【未】掛 vendetta_mark﹐殺之不結仇﹔故
//     判定以 vendetta_mark 為準（比 class+sect 更精確、只認真正會結此仇的 NPC）﹐
//     避免錯解無辜或漏解。
//   - 觸發：玩家 `ask laoba about 解仇`（中文 topic 解仇/仇/化解/虎刀門之仇 …）。
//     gate：玩家須當真與虎刀一脈結了仇（場上有仍記恨此玩家之虎刀門 NPC﹐或身上
//     有持久 vendetta/tiger）方有可解﹔老把念在與高慎的交情免費說合一次。
//   - 化解：掃 livings() 中 clonep && !userp && query("vendetta_mark")=="tiger"
//     && is_killing(who) 之 NPC﹐逐一【雙向】解仇 foe->remove_killer(who);
//     who->remove_killer(foe);﹐並清玩家身上持久 vendetta/tiger﹐set
//     quest/daolaoba_done=1。
//   - double-grant 防呆：已 done 者改述「早替你了結」之言﹐不重複說合。
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

#define TIGER_MARK      "tiger"     // 虎刀門陣營持久結仇 mark（query("vendetta/tiger")）

int do_ask(string arg);

// 化解虎刀門仇恨：掃出當前載入、仍記恨 who、且屬虎刀一脈
//（query("vendetta_mark")=="tiger"）的 NPC，逐一雙向解仇；並清玩家身上持久
// vendetta/tiger。回傳實際化解的虎刀門 NPC 數目（供回報訊息參考）。
private int mediate_tiger_enmity(object who)
{
	object *foes;
	int n;

	if( !who ) return 0;

	// livings() 取所有載入中的生物；過濾出 clone 的、非玩家的、仍記恨此玩家、
	// 且屬虎刀一脈（掛 vendetta_mark=="tiger"）者。（鏡 /cmds/arch/overview.c
	// 的 livings()+屬性過濾、/d/snowmanor/npc/ku_wuwang.c 的 mediate handler。）
	foes = filter_array(livings(), (:
		objectp($1)
		&& clonep($1)
		&& !userp($1)
		&& $1->is_killing($(who))
		&& $1->query("vendetta_mark") == TIGER_MARK
	:));

	n = sizeof(foes);
	foreach(object foe in foes) {
		// 雙向解仇（鏡 /d/snow/npc/girl.c）：虎刀門人收刀作罷、玩家亦不再與之為敵。
		foe->remove_killer(who);
		who->remove_killer(foe);
	}

	// 持久結仇歸零（additive）：清玩家身上 query("vendetta/tiger")。
	// vendetta 累積／圍攻機制見 adm/daemons/chard.c（殺帶 mark 之 NPC +1）、
	// feature/char/attack.c（進房 init() 查此值非零即自動開打）。
	// delete("vendetta/tiger") 經 feature/dbase.c 對 slash-path 做巢狀 map_delete
	// ——只刪 vendetta 下的 tiger 鍵，不動其他派別之 mark。
	if( who->query("vendetta/" + TIGER_MARK) )
		who->delete("vendetta/" + TIGER_MARK);

	return n;
}

void create()
{
	set_name("巴老把", ({ "ba laoba", "laoba", "ba", "old blade" }));
	set("nickname", "刀疤老把");
	set_attr("str", 24);
	set_attr("dex", 21);
	set_attr("int", 19);
	set_attr("wis", 20);
	set_attr("spi", 21);
	set_attr("con", 23);
	set_attr("cor", 22);
	set_race("human");
	set_level(29);
	set_class("commoner");      // 退隱不問門派之爭的老刀客，不結虎刀之仇，故設 commoner

	set_skill("unarmed", 60);
	set_skill("blade", 80);
	set_skill("parry", 60);
	set_skill("dodge", 55);
	set_skill("force", 70);

	set("gender", "male");
	set("age", 57);
	set("long",
		"這是一個一身刀疤的退隱老刀客﹐花白的頭髮胡亂束著﹐臉上、頸\n"
		"上、露在外頭的手臂上﹐橫七豎八全是當年刀頭舔血留下的舊傷疤。他\n"
		"在這老松林口搭了個草棚﹐棚下擺著塊磨刀石﹐成日替過往的行旅磨磨\n"
		"刀、嘮嘮江湖舊事。聽聞他當年也是這林子裡與虎刀門門主高慎一道亮\n"
		"刀見血的老兄弟﹐如今刀快不動了﹐才退到林口看著後生們進進出出。\n"
		"江湖人若與虎刀一脈結了死仇、不敢踏進刀堂賠罪﹐多半在這林口尋他\n"
		"說合。你或許可以問問他﹕ask laoba about 虎刀門﹐或 ask laoba about 解仇。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"巴老把就著磨刀石「霍霍」磨著一柄缺口的舊刀﹐渾濁的眼裡精光偶爾一閃。\n",
		"巴老把摸著臉上一道斜貫的刀疤﹐咧嘴一笑﹕這道﹐就是當年那小子高慎賞的。\n",
		"巴老把抬眼望了望南面刀堂的方向﹐搖搖頭﹕後生們的刀﹐是越來越快﹐火氣也越來越大嘍。\n",
	}));
	setup();
	carry_money("coin", 70);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	// #14：招呼只對真人，加 interactive(this_player()) 護衛，免 NPC 互觸洗版。
	if( this_player() && interactive(this_player()) ) {
		if( !is_fighting() )
			do_chat((: command,
				"say 後生﹐進林子是要拜山頭呢﹐還是惹了甚麼麻煩﹖在老把這兒歇歇腳罷。" :));
	}
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這個一身刀疤的老刀客甚麼﹖（試試 ask laoba about 虎刀門）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("巴老把正自低頭磨刀﹐且待他閒了再問。\n");

	// 問虎刀門 / 高慎：道出他與虎刀一脈的交情 —— 解仇任務伏筆
	if( arg == "laoba about 虎刀門"
	||  arg == "ba laoba about 虎刀門"
	||  arg == "laoba about 高慎"
	||  arg == "laoba about 虎刀"
	||  arg == "laoba about hudao"
	||  arg == "laoba about gao" ) {
		do_chat(({
			(: command, "say 虎刀門麼 ... 當年我跟高慎那小子﹐就在這林子裡跟猛虎搏命、跟仇家拼刀﹐是過命的交情。" :),
			(: command, "say 虎刀門收徒只認一個「膽」字﹐刀快、人狠、亮刀就要見血。結起仇來呵﹐那也是見人就砍、絕不收手的。" :),
			(: command, "say 你若不巧惹上了虎刀門的人﹐莫往南邊刀堂硬闖﹐尋死呢——ask laoba about 解仇 便是。" :),
		}));
		return 1;
	}

	// 問解仇 / 仇怨：虎刀門解仇 service —— 老把念在與高慎的交情，出面說合。
	//   同步交付，旗標／訊息逕在本 handler 內寫就。
	if( arg == "laoba about 解仇"
	||  arg == "ba laoba about 解仇"
	||  arg == "laoba about 仇"
	||  arg == "laoba about 化解"
	||  arg == "laoba about 虎刀門之仇"
	||  arg == "laoba about 恩怨"
	||  arg == "laoba about grudge" ) {
		object me;
		int cleared;
		int had_mark;

		me = this_player();
		if( !me || !interactive(me) )
			return notify_fail("這裡沒人問你的話。\n");

		// double-grant 防呆：已說合過者，不重複出面，改述早為了結之言。
		if( me->query("quest/daolaoba_done") >= 1 ) {
			command("say 你跟虎刀門那段樑子﹐老把早替你了結了﹐安心進出便是。");
			tell_object(me,
				"巴老把咧嘴一笑﹐露出豁了的牙﹕同一個人情﹐老把可不替你討第二回。\n");
			return 1;
		}

		// gate：玩家須當真與虎刀一脈結了仇方有可解。仇怨有二態——
		//   (1) 場上有仍記恨此玩家之虎刀門 NPC（transient killer）；
		//   (2) 玩家身上有持久 vendetta/tiger（即便此刻無此派 NPC 在場）。
		// 兩者任一成立即可說合。先記下持久 mark 之有無（mediate 內會清掉），
		//   再 mediate（同時做 transient 雙向解仇＋清持久 vendetta/tiger）。
		had_mark = me->query("vendetta/" + TIGER_MARK) ? 1 : 0;
		cleared = mediate_tiger_enmity(me);
		if( cleared <= 0 && !had_mark ) {
			command("say 解仇﹖你眼下又沒惹著虎刀門的人﹐哪來的仇怨好解﹖");
			command("say 哪天真跟虎刀一脈結了死樑子﹐再來尋老把這把老骨頭罷。");
			return 1;
		}

		// ── 同步交付（全在 handler 內直接完成，不走延遲 do_chat）──
		// 1. 設永久旗標（鐵則 #10 精神：關鍵狀態先落地）
		me->set("quest/daolaoba_done", 1);
		// 2. mediate_tiger_enmity 已完成 transient 雙向解仇＋清持久 vendetta/tiger，
		//    此處只述其事。
		command("say 嘿 ... 你也跟虎刀門的人結下死仇了﹖也罷﹐看在我跟高慎那點過命的交情上﹐這個人情老把替你討了。");
		command("say 虎刀門的刀﹐快是快﹐到底還聽老把一句話。這段樑子﹐就此一筆勾銷罷。");
		if( cleared > 0 )
			tell_object(me,
				"巴老把把舊刀往磨刀石上一擱﹐撐著膝蓋站起身﹐衝著南面刀堂的方向中氣十足地吼了\n"
				"幾嗓子。不過片刻﹐你只覺方才還對你橫眉立目、亮刀就要拼命的虎刀門人﹐眼前 " +
				cleared + " 名與\n你結仇者﹐竟似一夕之間收了刀、忘了你這號人物﹐恩怨盡釋。\n");
		else
			tell_object(me,
				"巴老把把舊刀往磨刀石上一擱﹐撐著膝蓋站起身﹐衝著南面刀堂的方向中氣十足地吼了\n"
				"幾嗓子。你心頭一鬆——你跟虎刀一脈那段死樑子﹐自此一筆勾銷﹐日後與虎刀門人\n"
				"打照面﹐再不必擔心他們認出舊仇、拔刀相向了。\n");
		return 1;
	}

	// 問老松林 / 磨刀：閒談氣氛
	if( arg == "laoba about 老松林"
	||  arg == "laoba about 松林"
	||  arg == "laoba about 刀"
	||  arg == "laoba about woods" ) {
		do_chat(({
			(: command, "say 這老松林呵﹐松幹上那些刀痕﹐一道是一條人命﹐老把都記得。" :),
			(: command, "say 刀這東西﹐越磨越快﹐人心卻是越磨越鈍。後生﹐你這股戾氣﹐該收收了。" :),
		}));
		return 1;
	}

	return notify_fail("巴老把只顧低頭磨刀﹐並不答你。（試試 ask laoba about 虎刀門）\n");
}

// 老刀客究竟是練家子，受襲自會還手。結仇機制未涉，此處僅作自衛反擊。
int accept_fight(object ob)
{
	do_chat((: command, "say 好小子﹗老把一片好意替你說合﹐你倒要動刀﹖看老把這把老骨頭還使不使得動﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
