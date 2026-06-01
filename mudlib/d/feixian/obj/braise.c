// braise.c -- 錢記酒樓的招牌滷味拼盤（本地下酒菜﹐F_FOOD 可食）

inherit COMBINED_ITEM;
inherit F_FOOD;

void create()
{
	set_name("滷味拼盤", ({ "braised platter", "braise", "luwei" }) );
	if( !clonep() ) {
		set("unit", "盤");
		set("base_unit", "碟");
		set("base_value", 80);
		set("base_weight", 350);
		set("heal_kee", 8);
		set("food_stuff", 100);
		set("long",
			"錢記酒樓後堂那鍋陳年老滷裡撈出的滷味拼盤﹐醬色油亮﹐\n"
			"蹄花、豆乾、滷蛋、海帶一樣切上幾片﹐拼作一碟﹐鹹香入味﹐\n"
			"最是下酒。\n");
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
