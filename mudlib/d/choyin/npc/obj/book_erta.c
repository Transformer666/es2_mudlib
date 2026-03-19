// book_erta.c

inherit ITEM;

void create()
{
	set_name("爾雅", ({"book_erta", "book", "erta"}));
	set_weight(600);
	if( !clonep() ) {
		set("unit", "冊");
		set("value", 500);
		set("long",
			"一冊線裝古書﹐封面上寫著「爾雅」二字。這是一部訓詁學的\n"
			"經典著作﹐解釋了許多古代的詞語和名物﹐是讀書人案頭必備之書。\n");
	}
	setup();
}
