// thief.c - 李家村任務：偷玉牌的小賊
// 任務觸發後才出現﹐不常駐在房間裡

#include <npc.h>

inherit F_BANDIT;

void die_give_tablet(object killer);

void create()
{
	set_name("小賊", ({"thief", "petty thief"}));
	set_attr("str", 14);
	set_attr("dex", 18);
	set_attr("con", 12);
	set_attr("int", 10);
	set_attr("spi", 8);
	set_race("human");
	set_class("commoner");
	set_level(8);

	set_skill("dagger", 30);
	set_skill("dodge", 35);
	set_skill("unarmed", 20);

	set("age", 25);
	set("gender", "male");
	set("long",
		"一個賊眉鼠眼的年輕人﹐穿著一身灰撲撲的短打﹐腰間別著一\n"
		"把短刀。他鬼鬼祟祟地東張西望﹐看起來像是個慣偷。\n");
	set("attitude", "aggressive");

	setup();
	carry_object(STOCK_WEAPON("dagger"))->wield();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	carry_object(__DIR__"obj/jade_tablet");
	carry_money("coin", 30);
}

void die(object killer)
{
	die_give_tablet(killer);
	::die(killer);
}

void die_give_tablet(object killer)
{
	object tablet;

	if( !killer || !userp(killer) ) return;

	tablet = present("jade tablet", this_object());
	if( tablet ) {
		write("小賊倒地後﹐一塊玉牌從他懷裡滾了出來。\n");
		tablet->move(environment());
	}
}
