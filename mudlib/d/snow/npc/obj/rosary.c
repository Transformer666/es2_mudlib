// rosary.c - 老乞婆任務獎勵：念珠

#include <armor.h>

inherit F_NECK_EQ;

void create()
{
	set_name("念珠", ({"rosary", "beads", "prayer beads"}));
	set_weight(500);
	setup_neck_eq();

	if( !clonep() ) {
		set("unit", "串");
		set("value", 2000);
		set("long",
			"一串溫潤的檀木念珠﹐每一顆珠子上都隱隱散發著淡淡的檀香﹐\n"
			"握在手裡讓人心神寧靜。珠子的表面因為長年摩挲而顯得光滑圓潤﹐\n"
			"似乎蘊含著一股不凡的靈氣。\n");
		set("wear_as", "neck_eq");
		set("apply_armor/neck_eq", ([
			"armor": 2,
		]));
	}
	setup();
}
