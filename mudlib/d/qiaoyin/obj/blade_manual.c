// /d/qiaoyin/obj/blade_manual.c

inherit ITEM;
inherit F_STUDY;

void create()
{
	set_name("【五虎斷門刀譜】", "blade", "manual", "book");
	set_weight(800);
	if( !clonep() ) {
		set("unit", "本");
		set("value", 420);
		set("long",
			"這是一本坊間鏢局慣用的刀譜﹐圖中刀客身形威猛﹐一招\n"
			"一式皆是劈、砍、撩、掛的硬橋硬馬功夫﹐講究的是大開\n"
			"大闔、剛猛沉實。識字的人對著圖譜勤加揣摩﹐刀法不難\n"
			"入門。可用 study 研讀。\n");
		set("required/skill", ([
			"literate" : 10,
		]));
		set("content", ([
			"blade" : 30,
		]));
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
