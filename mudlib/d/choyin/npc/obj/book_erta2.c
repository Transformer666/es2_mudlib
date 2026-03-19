// book_erta2.c

inherit ITEM;

void create()
{
	set_name("論語", ({"book_erta2", "book", "lunyu"}));
	set_weight(600);
	if( !clonep() ) {
		set("unit", "冊");
		set("value", 500);
		set("long",
			"一冊線裝古書﹐封面上端正地寫著「論語」二字。書中記載了\n"
			"孔子及其弟子的言行﹐是儒家最重要的經典之一﹐讀書人無不熟讀。\n");
	}
	setup();
}
