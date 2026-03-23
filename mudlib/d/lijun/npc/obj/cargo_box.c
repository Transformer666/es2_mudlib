// cargo_box.c — 行商貨箱（行商失貨任務道具）

inherit ITEM;

void create()
{
	set_name("貨箱", ({"cargo_box", "cargo box", "box", "cargo"}));
	set_weight(5000);
	if( !clonep() ) {
		set("unit", "只");
		set("value", 500);
		set("long",
			"一只用桐油浸過的木箱﹐雖然在水裡泡了一段時間﹐但裡面的\n"
			"貨物大致還完好。箱子上刻著一個「程」字﹐應該是行商的姓氏。\n");
	}
	setup();
}
