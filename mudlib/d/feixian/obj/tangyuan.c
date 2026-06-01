// tangyuan.c -- 錢記酒樓的桂花酒釀圓子（本地甜食﹐F_FOOD 可食）

inherit COMBINED_ITEM;
inherit F_FOOD;

void create()
{
	set_name("酒釀圓子", ({ "sweet dumpling", "tangyuan", "wine dumpling" }) );
	if( !clonep() ) {
		set("unit", "鍋");
		set("base_unit", "碗");
		set("base_value", 50);
		set("base_weight", 300);
		set("heal_kee", 5);
		set("food_stuff", 90);
		set("long",
			"一碗熱騰騰的桂花酒釀圓子﹐雪白的小圓子浮在微醺的酒釀\n"
			"湯裡﹐撒著一撮金黃的乾桂花﹐甜糯暖香﹐是錢記酒樓裡最得婦\n"
			"孺歡心的一道甜食。\n");
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
