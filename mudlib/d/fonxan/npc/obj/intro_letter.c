// intro_letter.c -- 主線任務二「殘卷尋蹤」的信物：
//                   封山派藏劍師叔陸抱朴寫給喬陰縣衙書吏的一封引薦帖

inherit ITEM;

void create()
{
	set_name("引薦帖", ({ "intro letter", "letter" }) );
	set_weight(80);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "帖");
		set("value", 1);
		set("long",
			"一封封山派藏劍師叔陸抱朴親筆寫就的引薦帖﹐素箋上一行行小\n"
			"楷瘦硬如劍﹐落款處鈐著一方「封山藏劍」的朱印。帖中寫明持帖\n"
			"之人乃受託前來調閱卷庫中那卷《封鬼遺錄》殘卷﹐還望縣衙書吏\n"
			"行個方便。憑著這封帖子﹐合該能在喬陰縣衙討回那卷殘卷。\n");
		set("no_sell", 1);
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
