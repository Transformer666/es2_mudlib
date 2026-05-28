// /d/qiaoyin/obj/poetry.c

inherit ITEM;
inherit F_STUDY;

void create()
{
	set_name("【喬陰詩抄】", "poetry", "book");
	set_weight(900);
	if( !clonep() ) {
		set("unit", "本");
		set("value", 350);
		set("long",
			"這是喬陰書局自行刻印的一卷詩抄﹐輯錄了歷代過往本縣\n"
			"的文人墨客所留下的吟詠之作﹐字句清雅﹐意境悠遠。讀書\n"
			"人捧讀再三﹐於文墨一道頗有助益。可用 study 細細研讀。\n");
		set("required/skill", ([
			"literate" : 10,
		]));
		set("content", ([
			"literate" : 35,
		]));
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
