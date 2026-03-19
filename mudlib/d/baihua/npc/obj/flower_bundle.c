// flower_bundle.c

inherit ITEM;

void create()
{
	set_name("鮮花", ({"flower_bundle", "flower", "flowers"}));
	set_weight(200);
	if( !clonep() ) {
		set("unit", "束");
		set("value", 10);
		set("long", "一束色彩繽紛的鮮花﹐散發著淡淡的清香﹐令人心情愉悅。\n");
	}
	setup();
}
