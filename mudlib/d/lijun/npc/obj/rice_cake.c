// vim: syntax=lpc

inherit ITEM;

void create()
{
	set_name("桂花糕", ({"rice_cake", "cake"}));
	set_weight(150);
	if( !clonep() ) {
		set("unit", "塊");
		set("value", 15);
		set("long", "一塊香甜的桂花糕﹐表面點綴著金黃色的桂花﹐散發著誘人的甜香。\n");
	}
	setup();
}
