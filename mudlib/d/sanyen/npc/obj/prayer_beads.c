// prayer_beads.c

#include <armor.h>

inherit F_WRIST_EQ;

void create()
{
	set_name("念珠", ({"prayer_beads", "beads"}));
	set_weight(200);
	setup_wrist_eq();

	if( !clonep() ) {
		set("unit", "串");
		set("value", 80);
		set("long", "一串用菩提子穿成的念珠﹐共有一百零八顆﹐每顆珠子都被磨得圓潤光亮。佩戴在手腕上隱隱有一股安寧祥和之氣。\n");
		set("wear_as", "wrist_eq");
		set("apply_armor/wrist_eq", ([
			"armor" : 1,
		]));
	}
	setup();
}
