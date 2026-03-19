// vim: syntax=lpc

#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
	set_name("斗笠", ({"straw_hat", "hat"}));
	set_weight(800);
	setup_head_eq();

	if( !clonep() ) {
		set("unit", "頂");
		set("value", 100);
		set("long", "一頂用竹篾和棕櫚葉編織而成的斗笠﹐寬大的帽簷可以遮陽擋雨﹐是行走江湖的必備之物。\n");
		set("wear_as", "head_eq");
		set("apply_armor/head_eq", ([
			"armor" : 2,
		]));
	}
	setup();
}
