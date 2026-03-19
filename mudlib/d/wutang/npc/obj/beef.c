// vim: syntax=lpc

inherit ITEM;

void create()
{
    set_name("水煮牛肉", ({"beef", "food"}));
    set_weight(300);
    if( !clonep() ) {
	set("unit", "份");
	set("value", 400);
	set("long", "一大盤熱騰騰的水煮牛肉﹐香氣撲鼻。\n");
    }
    setup();
}
