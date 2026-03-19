// vim: syntax=lpc

inherit ITEM;

void create()
{
    set_name("牛肉包子", ({"dumpling", "beef_dumpling", "food"}));
    set_weight(100);
    if( !clonep() ) {
	set("unit", "個");
	set("value", 10);
	set("long", "一個熱騰騰的牛肉包子﹐皮薄餡多。\n");
    }
    setup();
}
