// commoner.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("京城百姓", ({ "commoner", "citizen" }) );
	set_race("human");
	set_class("commoner");
	set_level(2);

	set("age", 42);
	set("gender", "male");
	set("long",
		"一個土生土長的京城百姓﹐穿著體面的綢布長衫﹐袖著手不疾\n"
		"不徐地走著﹐眉宇間自有一股久居天子腳下、見慣大場面的從\n"
		"容氣度。\n");
	set("chat_chance", 5);
	set("chat_msg", ({
		(: random_move :),
		"京城百姓朝你拱了拱手﹐算是打了個招呼。\n",
		"京城百姓得意地說道﹕在咱們天子腳下討生活﹐那可是天大的體面﹐豈是外鄉人比得的﹖\n",
		"京城百姓壓低聲音道﹕聽說後海湖底鬧過蹊蹺﹐入夜後連畫舫都不敢往湖心去哩。\n",
		"京城百姓說道﹕出了南城門往西﹐順著官道走便是喬陰縣城了。\n",
	}));
	setup();
	carry_money("coin", 50);
}

int accept_fight()
{
	do_chat("京城百姓慌忙擺手道﹕使不得﹗這可是天子腳下﹐禁軍就在眼前哪﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
