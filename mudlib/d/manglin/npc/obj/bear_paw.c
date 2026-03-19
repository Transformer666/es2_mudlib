// bear_paw.c

inherit ITEM;

void create()
{
	set_name("熊掌", ({"bear_paw", "paw"}));
	set_weight(2000);
	if( !clonep() ) {
		set("unit", "隻");
		set("value", 200);
		set("long", "一隻碩大的熊掌﹐掌心的肉墊又厚又軟﹐爪子尖銳無比。據說熊掌燉湯是滋補上品﹐在市面上價值不菲。\n");
	}
	setup();
}
