// /d/qiaoyin/obj/force_manual.c

inherit ITEM;
inherit F_STUDY;

void create()
{
	set_name("【吐納導引圖】", "force", "manual", "book");
	set_weight(800);
	if( !clonep() ) {
		set("unit", "本");
		set("value", 500);
		set("long",
			"這是一卷講述吐納導引的圖譜﹐畫著一個個盤膝靜坐、引\n"
			"氣調息的人形﹐旁註著行氣運功的淺近法門。雖只是基礎\n"
			"的養氣功夫﹐於初習內功者卻是築基的良方。練之日久﹐\n"
			"自覺氣息綿長、內力漸增。可用 study 研讀。\n");
		set("required/skill", ([
			"literate" : 10,
		]));
		set("content", ([
			"force" : 25,
		]));
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
