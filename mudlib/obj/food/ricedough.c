// ricedough.c

inherit COMBINED_ITEM;
inherit F_FOOD;

void create()
{
	set_name("飯糰", ({ "rice dough", "dough", "rice" }));
	if( !clonep() ) {
		set("unit", "堆");
		set("base_unit", "個");
		set("base_value", 25);
		set("base_weight", 80);
		set("food_stuff", 60);
		set("long",
			"米飯作成的糰子，裡面包著一些肉鬆、煎蛋、油條段兒的小菜。\n");
	}
	set_amount(1);   // 比照 medication COMBINED_ITEM 範式：clone 顯式設量，勿賴 setup() 條件式（見 eat 缺陷修正）
	setup();
}

