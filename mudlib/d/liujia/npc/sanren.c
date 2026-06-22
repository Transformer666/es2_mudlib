// sanren.c -- 六甲散仙，隱居六甲山頂、潛修數十載的修煉散人，六甲山獵場巔峰之對手。
//
// 結構沿用 /d/heifeng/npc/tiger.c（承 /d/hudao/wild/npc/madwolf.c → rabbit.c）的
// 戰鬥範式：可 kill、會還手、不主動攻擊路人(無 attitude，由玩家 kill 起釁)，殺後
// 只給 score(無錢)。戰力定在 level 45 一線——六甲山獵場巔峰之對手，內外兼修、踏罡
// 步斗，較巖魈(44)更勝一籌，須武藝精純、火候十足方好挑戰。此為「六甲山修煉散人」
// 一路的人形勁敵(對應任務「山精野獸／六甲山修煉散人」)。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("六甲散仙", ({ "liujia sanren", "sanren", "immortal" }) );
	set("nickname", "六甲散仙");
	set("title", "六甲山修煉散人");
	// 根骨 56 → 形體上限約 280 點；數十載吐納，以 advance_stat 厚其氣血，內力深湛。
	set_attr("con", 56);
	set_attr("str", 44);
	set_attr("dex", 46);
	set_attr("int", 40);
	set_race("human");
	set_class("fighter");
	set_level(45);

	// 內外兼修、踏罡步斗：徒手、拳掌、閃躲、拆招俱臻化境，內力尤為深湛。
	set_skill("unarmed", 116);
	set_skill("dodge", 80);
	set_skill("parry", 72);
	set_skill("force", 100);

	// 厚其氣血，使之耐打、有來有往（量介於巖魈 lvl44 的 230 與摩雲 lvl50 的 400 之間）。
	advance_stat("kee", 250);

	set("age", 64);
	set("gender", "male");
	set("long",
		"一位青袍的散人﹐鬚眉俱已花白﹐卻是面色紅潤、精神矍鑠﹐一\n"
		"望便知是內功有成的高手。他隱居六甲山頂﹐潛修數十載﹐按著\n"
		"六甲的方位踏罡步斗﹐借這滿山的草木地氣與峰頂的罡風養其真\n"
		"元﹐一身內家功夫已臻化境。他雖不問世事﹐卻最重一個「武」\n"
		"字——凡有上得峰頂、肯與他印證武學的後生﹐他向來奉陪到底﹐\n"
		"絕不藏私。此刻他負手立於六甲石陣之中﹐衣袂在罡風裡獵獵翻\n"
		"飛﹐目光湛然如電﹐隱隱透出一股不怒而威的宗師氣度。\n");
	// 純 score：江湖歷練(升級)、拳腳精熟、武術造詣、武學之道、實戰經驗。無錢幣。
	set("bounty", ([
		"survive"         : 1300,
		"unarmed mastery" : 280,
		"martial art"     : 190,
		"martial mastery" : 120,
		"combat"          : 100,
	]));
	setup();
}

// 奉陪到底、堂堂正正切磋（他並不主動尋釁﹐由玩家 kill 起釁；以武會友、點到為止之外，
// 對方既動了真格，他亦傾力相搏）。
int accept_fight(object ob)
{
	do_chat((: command, "say 六甲散仙朗笑一聲﹕後生既要印證武學﹐老朽便奉陪到底﹐手底下見真章罷﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
