// vim: syntax=lpc
// fire_herb.c - 火靈草 (quest item for herbalist_herb quest)

inherit ITEM;

void create()
{
	set_name("火靈草", ({"fire herb", "herb", "fire_herb"}));
	set_weight(100);
	if( !clonep() ) {
		set("unit", "株");
		set("value", 300);
		set("long",
			"一株罕見的火靈草﹐莖葉呈暗紅色﹐葉片邊緣隱隱泛著火\n"
			"焰般的光澤。據說這種草藥只生長在有龍息薰陶的岩洞中﹐\n"
			"是極為珍貴的藥材。\n");
	}
	setup();
}
