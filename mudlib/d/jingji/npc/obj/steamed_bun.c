// steamed_bun.c

inherit ITEM;

void create()
{
	set_name("灌湯包", ({"steamed_bun", "bun", "food"}));
	set_weight(100);
	if( !clonep() ) {
		set("unit", "籠");
		set("value", 25);
		set("long", "一籠精緻的灌湯包﹐麵皮薄如紙﹐湯汁鮮美﹐是京畿驛館的名點。\n");
	}
	setup();
}
