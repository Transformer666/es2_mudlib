// /d/qiaoyin/obj/sword_manual.c

inherit ITEM;
inherit F_STUDY;

void create()
{
	set_name("【基礎劍訣】", "sword", "manual", "book");
	set_weight(800);
	if( !clonep() ) {
		set("unit", "本");
		set("value", 450);
		set("long",
			"這是一卷入門的劍訣﹐工筆細細勾畫著持劍、運劍的姿勢\n"
			"與步法﹐旁註著刺、削、撩、格的要訣。雖只是粗淺的劍\n"
			"道入門﹐於初習劍術者而言﹐連使劍帶招架﹐都頗有助益。\n"
			"可用 study 研讀。\n");
		set("required/skill", ([
			"literate" : 10,
		]));
		set("content", ([
			"sword" : 30,
			"parry" : 20,
		]));
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
