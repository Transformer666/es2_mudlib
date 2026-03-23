// jade_pendant.c - 古井玉佩任務物品

inherit ITEM;

void create()
{
	set_name("玉佩", ({"jade pendant", "jade", "pendant"}));
	set_weight(100);
	if( !clonep() ) {
		set("unit", "塊");
		set("value", 500);
		set("long",
			"一塊溫潤的翠綠色玉佩﹐雕工精緻﹐上面刻著一對鴛鴦戲水的\n"
			"圖案。雖然在井水中浸泡了些時日﹐玉佩依然瑩潤如新﹐看起來\n"
			"是一件頗有年頭的物事。\n");
	}
	setup();
}
