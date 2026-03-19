// snakeskin.c

inherit ITEM;

void create()
{
	set_name("蛇皮", ({"snakeskin", "skin"}));
	set_weight(500);
	if( !clonep() ) {
		set("unit", "張");
		set("value", 50);
		set("long", "一張花紋斑斕的蛇皮﹐質地柔韌﹐可以賣給皮匠做些小玩意。\n");
	}
	setup();
}
