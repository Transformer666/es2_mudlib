// incense.c

inherit ITEM;

void create()
{
	set_name("香", ({"incense", "joss_stick"}));
	set_weight(50);
	if( !clonep() ) {
		set("unit", "柱");
		set("value", 5);
		set("long", "一柱細細的線香﹐點燃後會散發出淡淡的檀香味﹐用來供佛拜神。\n");
	}
	setup();
}
