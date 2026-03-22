// local_wine.c

inherit ITEM;

void create()
{
	set_name("土釀", ({"local_wine", "wine", "drink"}));
	set_weight(500);
	if( !clonep() ) {
		set("unit", "壺");
		set("value", 20);
		set("long", "一壺龍安本地釀造的濁酒﹐味道醇厚﹐後勁十足。\n");
	}
	setup();
}
