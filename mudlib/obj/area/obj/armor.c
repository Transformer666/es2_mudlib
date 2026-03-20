// armor.c

#include <armor.h>

inherit F_ARMOR;

void create()
{
	set_name("軍甲", ({ "armor" }));
	set_weight(8000);
	setup_armor();

	if( !clonep() ) {
		set("unit", "套");
		set("value", 3000);
		set("long", "一套制式軍甲，雖有些陳舊但仍堅固耐用。\n");
		set("wear_as", "armor");
		set("apply_armor/armor", ([
			"armor": 5,
		]));
	}

	setup();
}
