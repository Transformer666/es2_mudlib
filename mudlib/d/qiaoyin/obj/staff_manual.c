// /d/qiaoyin/obj/staff_manual.c

inherit ITEM;
inherit F_STUDY;

void create()
{
	set_name("【齊眉棍法圖】", "staff", "manual", "book");
	set_weight(800);
	if( !clonep() ) {
		set("unit", "本");
		set("value", 380);
		set("long",
			"這是一卷以朱墨繪成的棍法圖﹐畫的是尋常鄉勇、腳夫所\n"
			"使的齊眉棍。圖中棍勢或掃或劈、或挑或點﹐樸實無華卻\n"
			"勝在實用。識得些字的人對圖比劃﹐棍法不難上手。可用\n"
			"study 研讀。\n");
		set("required/skill", ([
			"literate" : 10,
		]));
		set("content", ([
			"staff" : 30,
		]));
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
