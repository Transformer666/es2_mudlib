// straw_sandal.c

#include <armor.h>

inherit F_FEET_EQ;

void create()
{
	set_name("草鞋", ({"straw_sandal", "sandal", "shoes"}));
	set_weight(500);
	setup_feet_eq();

	if( !clonep() ) {
		set("unit", "雙");
		set("value", 30);
		set("long", "一雙用稻草編織的草鞋﹐雖然簡陋﹐但穿起來輕便透氣﹐適合在山野間行走。\n");
		set("wear_as", "feet_eq");
		set("apply_armor/feet_eq", ([
			"armor" : 1,
		]));
	}
	setup();
}
