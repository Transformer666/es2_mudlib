// vim: syntax=lpc

inherit ITEM;

void create()
{
    set_name("小水袋", ({"waterskin", "water"}));
    set_weight(500);
    if( !clonep() ) {
	set("unit", "袋");
	set("value", 50);
	set("long", "一個裝滿清水的小水袋﹐可以解渴。\n");
    }
    setup();
}
