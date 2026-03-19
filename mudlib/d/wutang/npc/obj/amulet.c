// vim: syntax=lpc

#include <armor.h>

inherit F_NECK_EQ;

void create()
{
    set_name("護身符", ({"amulet", "charm"}));
    set_weight(200);
    if( !clonep() ) {
	set("unit", "個");
	set("value", 50000);
	set("long", "一塊刻著神秘符文的護身符﹐據說能增強佩戴者的能力。\n");
	set("wear_as", "neck_eq");
	set("apply_armor/neck_eq", ([
	    "armor": 2,
	]));
    }
    setup();
}
