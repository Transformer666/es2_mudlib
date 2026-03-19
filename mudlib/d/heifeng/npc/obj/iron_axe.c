// iron_axe.c

#include <weapon.h>

inherit F_AXE;

void create()
{
	set_name("鐵斧", ({"iron_axe", "axe"}));
	set_weight(8000);
	setup_axe(2, 10, 70, 0);

	if( !clonep() ) {
		set("wield_as", "axe");
		set("unit", "把");
		set("value", 1500);
		set("rigidity", 24);
		set("long",
			"一把沉重的鐵斧﹐斧頭鑄鐵而成﹐刃口雖然有些捲了﹐但仍\n"
			"然十分鋒利。斧柄是一根粗壯的硬木﹐被長年使用磨得十分光滑。\n");
	}
	setup();
}
