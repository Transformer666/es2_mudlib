// wildboar.c -- 野豬，文國西山密林裡掘食草根的獠牙野豬，膘肥力大、性暴。
//
// 結構沿用 /d/heifeng/npc/greywolf.c：可 kill、會還手、不主動攻擊路人(無 attitude)，
// 殺後只給 score(無錢)。戰力定在 level 22 一線——較山狸(16)更硬，是文國獵場的中段對手。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("野豬", ({ "wild boar", "wildboar", "boar", "yezhu" }) );
	// 根骨 40 → 形體上限約 200 點；另以 advance_stat 加厚氣血﹐膘肥皮厚、橫衝直撞。
	set_attr("con", 40);
	set_attr("str", 36);
	set_attr("dex", 18);
	set_race("human");
	set_class("commoner");
	set_level(22);

	// 撩牙剛猛、橫衝硬撞﹐閃躲拆招平平﹐純以蠻力與皮厚取勝。
	set_skill("unarmed", 40);
	set_skill("dodge", 16);
	set_skill("parry", 22);
	set_skill("force", 16);

	// 厚其氣血﹐使之膘肥耐打、有來有往。
	advance_stat("kee", 40);

	set("age", 4);
	set("gender", "male");
	set("long",
		"一頭膘肥體壯的西山野豬﹐通體覆著粗硬的黑鬃﹐脊背高聳如鐵﹐\n"
		"一對撩牙自嘴角斜斜地翹出﹐又長又利﹐閃著森森的寒光。牠成日\n"
		"拿那硬挺的長嘴在林下拱食草根橡實﹐拱得滿地泥坑。這畜生性子\n"
		"暴烈﹐受了驚便瞪著一雙赤紅的小眼﹐呼哧呼哧地噴著粗氣﹐挺著\n"
		"撩牙橫衝直撞﹐連樵夫獵戶見了也要退避三分。\n");
	// 純 score：江湖歷練(升級)、拳腳精熟、武術造詣、武學之道、實戰經驗。無錢幣。
	set("bounty", ([
		"survive"         : 300,
		"unarmed mastery" : 76,
		"martial art"     : 48,
		"martial mastery" : 24,
		"combat"          : 28,
	]));
	setup();
}

// 不主動撲路人﹐由玩家 kill 起釁；暴烈衝撞。
int accept_fight(object ob)
{
	do_chat((: command, "say 野豬瞪著赤紅的小眼﹐呼哧呼哧噴著粗氣﹐挺起撩牙橫衝直撞而來﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
