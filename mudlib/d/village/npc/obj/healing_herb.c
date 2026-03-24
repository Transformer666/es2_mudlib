// vim: syntax=lpc

inherit ITEM;

void create()
{
	set_name("療傷藥草", ({"healing_herb", "healing herb", "herb"}));
	set_weight(200);
	if( !clonep() ) {
		set("unit", "包");
		set("value", 60);
		set("long",
			"一包精心調配的療傷藥草﹐裡面混合了金銀花、當歸和白芷\n"
			"等藥材﹐散發著濃郁的藥香。據說敷在傷口上可以加速癒合。\n");
	}
	setup();
}
