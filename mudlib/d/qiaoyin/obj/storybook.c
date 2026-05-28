// /d/qiaoyin/obj/storybook.c

inherit ITEM;

void create()
{
	set_name("【江湖奇聞錄】", "storybook", "book");
	set_weight(700);
	if( !clonep() ) {
		set("unit", "本");
		set("value", 80);
		set("long",
			"這是坊間刻印的一本話本傳奇﹐記的都是些江湖上的奇人\n"
			"異事、刀光劍影﹐文字通俗熱鬧﹐茶餘飯後翻來解悶最是合\n"
			"適。書頁邊角已被無數人翻得起了毛邊。\n");
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
