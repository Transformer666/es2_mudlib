// vim: syntax=lpc

inherit ITEM;

void create()
{
    set_name("饅頭", ({"manto", "bun", "food"}));
    set_weight(80);
    if( !clonep() ) {
	set("unit", "個");
	set("value", 10);
	set("long", "一個白胖胖的饅頭。\n");
    }
    setup();
}
