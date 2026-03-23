// vim: syntax=lpc
// 金剛露 - baixiang_bodhi_tree quest item

inherit ITEM;

void create()
{
	set_name("金剛露", ({"sacred dew", "dew", "sacred_dew"}));
	set_weight(100);

	if( !clonep() ) {
		set("unit", "瓶");
		set("value", 0);
		set("long",
			"一小瓶凝結在古鐘經文上的露水﹐散發著淡淡的檀香氣息。\n"
			"據說這種露水吸收了數百年來僧人誦經的靈氣﹐對草木有神\n"
			"奇的滋養之效。\n");
	}
	setup();
}
