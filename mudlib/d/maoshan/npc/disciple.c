#include <npc.h>

inherit F_SCHOLAR;

void create()
{
	set_name("茅山弟子", ({"disciple", "maoshan_disciple"}));
	set_attr("str", 10);
	set_attr("con", 12);
	set_attr("dex", 12);
	set_attr("int", 16);
	set_attr("wis", 15);
	set_attr("spi", 14);
	set_race("human");
	set_class("taoist");
	set_level(15);

	set_skill("staff", 25);
	set_skill("dodge", 20);

	set("age", 24);
	set("attitude", "peaceful");
	set("long",
		"一名身穿道袍的茅山弟子﹐正在風中盤坐修煉﹐道袍被山風\n"
		"吹得獵獵作響﹐他卻神態自若﹐紋絲不動。\n");
	setup();
	carry_object( STOCK_ARMOR("cloth") )->wear();
	carry_object( STOCK_WEAPON("staff") )->wield();
	carry_money("coin", 30);
	set_temp("apply/vision_of_ghost", 1);
}
