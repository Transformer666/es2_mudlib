// citizen.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("縣民", ({ "citizen", "townman" }) );
	set_race("human");
	set_class("commoner");
	set_level(2);

	set("age", 39);
	set("gender", "male");
	set("long",
		"一個尋常的喬陰縣城百姓﹐穿著還算體面的細布長衫﹐袖著手\n"
		"不慌不忙地走著﹐一臉縣城人家見過些世面的從容。\n");
	set("chat_chance", 5);
	set("chat_msg", ({
		(: random_move :),
		"縣民朝你拱了拱手﹐算是打了個招呼。\n",
		"縣民得意地說道﹕咱們喬陰好歹是個縣城﹐比那雪亭、五堂的小鎮可體面多了。\n",
		"縣民壓低聲音道﹕聽說老松林裡那夥老松寨的匪人﹐連縣太爺都拿他們沒法子哩。\n",
		"縣民說道﹕往西北出城過了老松林﹐便是雪亭鎮了﹐只是那條路如今不大太平。\n",
	}));
	setup();
	carry_money("coin", 30);
}

int accept_fight()
{
	do_chat("縣民慌忙擺手道﹕使不得使不得﹗光天化日﹐縣衙就在眼前哪﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
