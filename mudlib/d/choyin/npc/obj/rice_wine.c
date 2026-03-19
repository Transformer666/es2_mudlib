// rice_wine.c

inherit ITEM;

void create()
{
	set_name("米酒", ({"rice_wine", "wine", "drink"}));
	set_weight(500);
	if( !clonep() ) {
		set("unit", "壺");
		set("value", 25);
		set("long", "一壺清冽的米酒﹐酒香淡雅﹐入口甘甜﹐是喬陰當地的特產。\n");
	}
	setup();
}
