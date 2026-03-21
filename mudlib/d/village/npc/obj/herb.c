// herb.c

inherit ITEM;

void create()
{
	set_name("草藥", ({"herb", "herbs"}));
	set_weight(200);
	if( !clonep() ) {
		set("unit", "包");
		set("value", 25);
		set("long", "一包曬乾的草藥﹐散發著淡淡的苦香﹐據說有止血療傷的功效。\n");
	}
	setup();
}
