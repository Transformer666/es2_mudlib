// wreath.c

#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
	set_name("花環", ({"wreath", "garland"}));
	set_weight(300);
	setup_head_eq();

	if( !clonep() ) {
		set("unit", "個");
		set("value", 50);
		set("long", "一個用各色鮮花編織而成的花環﹐精緻美觀﹐戴在頭上芬芳怡人。\n");
		set("wear_as", "head_eq");
		set("apply_armor/head_eq", ([
			"armor" : 1,
		]));
	}
	setup();
}
