// manto.c

inherit COMBINED_ITEM;
inherit F_FOOD;

void create()
{
	set_name("饅頭", ({ "manto" }));
	if( !clonep() ) {
		set("unit", "堆");
		set("base_unit", "個");
		set("base_value", 10);
		set("base_weight", 100);
		set("food_stuff", 80);
		set("long", "饅頭 ... 跟你想像中的一模一樣﹐感動吧。\n");
	}
	set_amount(1);   // 比照 medication COMBINED_ITEM 範式：clone 顯式設量，勿賴 setup() 條件式（見 eat 缺陷修正）
	setup();
}

