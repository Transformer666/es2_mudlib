// mountain_boar.c -- 山豕，六甲山口與山腰一帶橫衝直撞的吊睛山豬，六甲山獵場
// 最淺一級的獵物。
//
// 結構沿用 /d/heifeng/npc/leopard.c（承 /d/hudao/wild/npc/madwolf.c → rabbit.c）：
// 可 kill、會還手、不主動攻擊路人(無 attitude，由玩家 kill 起釁)，殺後只給
// score(無錢)。戰力定在 level 32 一線——略強於黑風山巖豹(31)，是備妥兵刃、稍有
// 火候的玩家堂堂正正打得過的對手(六甲山獵場的入門級)。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("山豕", ({ "mountain boar", "boar", "shanshi" }) );
	// 根骨 46 → 形體上限約 230 點；皮糙肉厚、橫衝直撞，極耐戰。
	set_attr("con", 46);
	set_attr("str", 42);
	set_attr("dex", 24);
	set_race("human");
	set_class("commoner");
	set_level(32);

	// 獠牙拱挑、橫衝剛猛：徒手剛狠、皮厚耐打，閃拆中平，內力平平。
	set_skill("unarmed", 60);
	set_skill("dodge", 30);
	set_skill("parry", 40);
	set_skill("force", 32);

	// 厚其氣血，使之耐打、有來有往（量輕於黑風山斑斕虎 lvl36 的 150）。
	advance_stat("kee", 100);

	set("age", 5);
	set("gender", "male");
	set("long",
		"一頭膘肥體壯的吊睛山豕﹐周身覆著一層粗硬如鬃的黑棕剛毛﹐\n"
		"脊背高高拱起﹐一對焦黃的獠牙自嘴角斜斜地向上挑出﹐尖端磨\n"
		"得鋥亮。牠是這六甲山口一帶橫衝直撞的霸主﹐吸納了滿山的草\n"
		"木地氣﹐較山下尋常的野豬兇悍數倍。此刻牠小眼裡泛著兇光﹐\n"
		"前蹄不住地刨著地上的腐葉﹐喉間滾出一串粗重的悶哼﹐隨時要\n"
		"低頭拱起獠牙﹐沒命地衝撞過來。\n");
	// 純 score：江湖歷練(升級)、拳腳精熟、武術造詣、武學之道、實戰經驗。無錢幣。
	set("bounty", ([
		"survive"         : 560,
		"unarmed mastery" : 120,
		"martial art"     : 82,
		"martial mastery" : 48,
		"combat"          : 46,
	]));
	setup();
}

// 奉陪到底、凶悍反擊（牠並不主動撲路人﹐由玩家 kill 起釁）。
int accept_fight(object ob)
{
	do_chat((: command, "say 山豕喉間一聲粗重的悶哼﹐脊背一拱﹐低頭挺起獠牙﹐沒命地衝撞而來﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
