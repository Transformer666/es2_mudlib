// vim: syntax=lpc
// 任務物品：學童丟失的書冊

inherit ITEM;

void create()
{
	set_name("千字文", ({"student_book", "book", "qianziwen"}));
	set_weight(300);

	if( !clonep() ) {
		set("unit", "冊");
		set("value", 50);
		set("long",
			"一冊薄薄的書﹐封面上用端正的楷書寫著「千字文」三個字。\n"
			"書頁有些潮濕﹐邊角沾了些泥巴﹐但內容尚可辨認。書的扉頁\n"
			"上歪歪扭扭地寫著一個「林」字﹐大概是書的主人的姓。\n");
	}

	setup();
}
