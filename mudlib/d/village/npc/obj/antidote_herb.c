// vim: syntax=lpc

inherit ITEM;

void create()
{
	set_name("解毒草藥", ({"antidote_herb", "antidote herb", "antidote"}));
	set_weight(200);
	if( !clonep() ) {
		set("unit", "包");
		set("value", 40);
		set("long",
			"一包翠綠色的草藥﹐主要由半邊蓮和車前草製成﹐帶著一股\n"
			"微苦的清香。村裡人被蛇蟲咬傷時﹐都會用這種藥草來解毒。\n");
	}
	setup();
}
