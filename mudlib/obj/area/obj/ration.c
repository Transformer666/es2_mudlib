// ration.c

inherit ITEM;

void create()
{
	set_name("乾糧", ({"ration", "food"}));
	set_weight(500);
	if( !clonep() ) {
		set("unit", "包");
		set("value", 20);
		set("long", "一包用油紙裹好的乾糧﹐裡頭有幾塊硬餅和一些肉乾﹐足以充飢果腹。\n");
	}
	setup();
}
