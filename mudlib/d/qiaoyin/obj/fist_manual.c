// /d/qiaoyin/obj/fist_manual.c

inherit ITEM;
inherit F_STUDY;

void create()
{
	set_name("【太祖長拳譜】", "fist", "manual", "book");
	set_weight(800);
	if( !clonep() ) {
		set("unit", "本");
		set("value", 400);
		set("long",
			"這是一本市井間流傳的拳譜﹐圖文並茂地畫著一招招樸實\n"
			"剛猛的拳腳功夫﹐相傳是前朝太祖起兵時所創的長拳。雖\n"
			"非什麼上乘武學﹐拳腳的根基倒是紮實。識得些字的人靜\n"
			"心揣摩﹐拳腳功夫不無小補。可用 study 研讀。\n");
		set("required/skill", ([
			"literate" : 10,
		]));
		set("content", ([
			"unarmed" : 30,
		]));
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
