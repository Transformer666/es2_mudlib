// jade_pendant.c - 守墓人師父的玉佩
// Quest item: gravekeeper_pendant

inherit ITEM;

void create()
{
	set_name("玉佩", ({"jade_pendant", "jade", "pendant"}));
	set_weight(100);
	if( !clonep() ) {
		set("unit", "塊");
		set("value", 500);
		set("long",
			"一塊溫潤的白玉佩﹐雕成蓮花形狀﹐背面刻著「清心」二字。\n"
			"雖然在墓中沉睡多年﹐玉質依然瑩潤透亮﹐顯然不是凡品。\n");
	}
	setup();
}
