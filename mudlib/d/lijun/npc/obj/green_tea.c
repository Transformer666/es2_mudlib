// vim: syntax=lpc

inherit ITEM;

void create()
{
	set_name("清月綠茶", ({"green_tea", "tea"}));
	set_weight(200);
	if( !clonep() ) {
		set("unit", "杯");
		set("value", 20);
		set("long", "一杯清澈碧綠的綠茶﹐茶香淡雅﹐入口回甘。\n");
	}
	setup();
}
