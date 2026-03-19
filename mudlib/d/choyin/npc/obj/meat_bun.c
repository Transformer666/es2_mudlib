// meat_bun.c

inherit ITEM;

void create()
{
	set_name("肉包子", ({"meat_bun", "bun", "food"}));
	set_weight(100);
	if( !clonep() ) {
		set("unit", "個");
		set("value", 15);
		set("long", "一個熱騰騰的肉包子﹐皮薄餡大﹐咬一口滿嘴流油﹐香氣撲鼻。\n");
	}
	setup();
}
