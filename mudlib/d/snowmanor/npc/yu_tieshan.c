// yu_tieshan.c -- 雪吟莊莊主 魚鐵山
//
// 設定（依 docs/01-世界觀與劇情/05-主線任務與NPC.md、04-地圖與場景.md）：
//   雪吟莊莊主﹐不斷擴張勢力﹐欲自命武林盟主。其內功一脈相傳自外邦「天邪國」﹐
//   是主線反派之一。與哭笑門主劉乙忘玄之間似有不可告人的勾結——主線疑團之一
//   即「魚鐵山和劉乙忘玄到底在搞什麼陰謀」。
//
// 本 NPC 為 boss 級人物（戰力參照虎刀門主高慎 / 哭笑門主劉乙忘玄之規格）：
//   * 不收徒、不開任何任務；對外人冷峻寡言。
//   * ask 劉乙忘玄 / 哭笑門 -> 神色一凜、含糊岔開，純為陰謀伏筆，不透露任何實情。
//   * accept_fight 回傳 1 —— 他奉陪到底﹐且戰力極強﹐是「莫去招惹」的強敵。
//   * 結仇/解仇完整機制尚未實作﹐此處僅以「自衛反擊 + 對話伏筆」呈現。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("魚鐵山", ({ "yu tieshan", "tieshan", "yu zhuangzhu" }));
	set("nickname", "雪吟莊主");
	set_attr("str", 27);
	set_attr("dex", 24);
	set_attr("int", 23);
	set_attr("wis", 23);
	set_attr("spi", 24);
	set_attr("cps", 25);
	set_attr("con", 26);
	set_attr("cor", 24);
	set_race("human");
	set_level(40);
	set_class("fighter");
	set("sect", "雪吟莊");
	set("rank", "莊主");

	set_skill("unarmed", 130);
	set_skill("blade", 150);
	set_skill("parry", 130);
	set_skill("dodge", 110);
	set_skill("force", 130);

	advance_stat("gin", 240);
	advance_stat("kee", 250);
	advance_stat("sen", 230);

	set("gender", "male");
	set("age", 52);
	set("long",
		"這位便是雪吟莊莊主魚鐵山。他身形高大﹐一襲金絲滾邊的玄色長\n"
		"袍罩著精悍的身板﹐面容方正﹐顴骨高聳﹐一雙眼睛深陷而銳利﹐睨\n"
		"人時自有一股不怒而威的煞氣。他按著一柄金絲纏柄的長刀﹐端坐廳\n"
		"中﹐神態傲岸如臨萬軍。聽聞他這些年勢力日張﹐隱隱有問鼎武林盟\n"
		"主之心﹐莊中那一脈剛猛詭譎的掌法刀法﹐據說源出某個不為中土所\n"
		"知的外邦。此人城府極深﹐尋常江湖客在他面前﹐連大氣也不敢出。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"魚鐵山端坐椅上﹐目光冷冷地自你身上掃過﹐似在掂量你的斤兩。\n",
		"魚鐵山把玩著手中那柄金絲長刀﹐刀光一閃﹐廳中眾家丁無不屏息。\n",
		"魚鐵山淡淡道﹕這武林﹐終要有個說了算的人。\n",
	}));
	setup();
	carry_object("/obj/area/obj/blade")->wield();
	carry_object("/obj/area/obj/robe")->wear();
	carry_money("coin", 800);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這位莊主甚麼﹖\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("魚鐵山正自端坐養神﹐並不理會你。\n");

	// 問雪吟莊 / 莊主自身：傲然寡言﹐對外人不吐實情
	if( arg == "yu about 雪吟莊"
	||  arg == "tieshan about 雪吟莊"
	||  arg == "yu tieshan about 雪吟莊"
	||  arg == "yu about 魚鐵山"
	||  arg == "tieshan about 魚鐵山"
	||  arg == "yu tieshan about 魚鐵山"
	||  arg == "yu about manor"
	||  arg == "yu tieshan about manor" ) {
		do_chat(({
			(: command, "say 雪吟莊的事﹐何勞外人過問﹖" :),
			(: command, "say 你既進得這道莊門﹐便該懂莊上的規矩——少看、少問、少多事。" :),
		}));
		return 1;
	}

	// 問劉乙忘玄 / 哭笑門：神色一凜、含糊岔開 —— 陰謀伏筆（不透露任何實情）
	if( arg == "yu about 劉乙忘玄"
	||  arg == "tieshan about 劉乙忘玄"
	||  arg == "yu tieshan about 劉乙忘玄"
	||  arg == "yu about 忘玄"
	||  arg == "yu about 哭笑門"
	||  arg == "tieshan about 哭笑門"
	||  arg == "yu tieshan about 哭笑門"
	||  arg == "yu about kuxiao"
	||  arg == "yu about liu" ) {
		do_chat(({
			(: command, "say 劉乙忘玄﹖" :),
			(: command, "say 哼﹐你一個來歷不明的後生﹐打聽這名字作甚﹖" :),
			(: command, "say 我與青邪宮素無往來。莊裡的事你管不著﹐山外的事——你更不該多問。" :),
			(: command, "say 識相的﹐便莫在這雪吟莊裡多生事端。" :),
		}));
		return 1;
	}

	// 問武林盟主 / 天邪 之類：透一點野心﹐仍不及陰謀本身
	if( arg == "yu about 武林盟主"
	||  arg == "yu tieshan about 武林盟主"
	||  arg == "yu about 盟主"
	||  arg == "yu about 天邪"
	||  arg == "tieshan about 天邪" ) {
		do_chat(({
			(: command, "say 武林盟主﹖這四個字﹐豈是憑空喊出來的。" :),
			(: command, "say 待我雪吟莊的根基穩了﹐這江湖﹐自會知道誰才當得起這個名號。" :),
		}));
		return 1;
	}

	return notify_fail("魚鐵山眉頭微皺﹐並不答你這一句。\n");
}

// boss 級：奉陪到底。結仇機制未實作﹐此處僅作自衛反擊。
int accept_fight(object ob)
{
	do_chat((: command, "say 不知死活的東西﹐也敢在雪吟莊裡撒野﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
