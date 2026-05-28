// /d/qiaoyin/obj/primer.c

inherit ITEM;
inherit F_STUDY;

void create()
{
	set_name("【三字蒙書】", "primer", "book");
	set_weight(800);
	if( !clonep() ) {
		set("unit", "本");
		set("value", 150);
		set("long",
			"這是一本坊間最常見的蒙學讀本﹐三字一句﹐朗朗上口﹐\n"
			"專供蒙童識字啟蒙之用。內容雖淺﹐倒也是讀書識字的根\n"
			"基。可用 study 細加研讀。\n");
		set("required/skill", ([
			"literate" : 1,
		]));
		set("content", ([
			"literate" : 15,
		]));
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
