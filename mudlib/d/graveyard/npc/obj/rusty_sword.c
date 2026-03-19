// rusty_sword.c

#include <weapon.h>

inherit F_SWORD;

void create()
{
	set_name("鏽劍", ({"rusty_sword", "sword"}));
	set_weight(5000);
	setup_sword(1, 6, 40, 1);

	if( !clonep() ) {
		set("wield_as", "sword");
		set("unit", "把");
		set("value", 150);
		set("rigidity", 15);
		set("long",
			"一把鏽跡斑斑的長劍﹐不知在墳墓中埋了多少年。劍身佈滿了\n"
			"紅褐色的鏽斑﹐劍刃也缺了好幾處﹐但握在手中仍能感覺到一股\n"
			"隱隱的寒意。\n");
	}
	setup();
}
