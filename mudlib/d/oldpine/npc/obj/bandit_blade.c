// bandit_blade.c

#include <weapon.h>

inherit F_BLADE;

void create()
{
	set_name("朴刀", ({"bandit_blade", "blade", "pudao"}));
	set_weight(6000);
	setup_blade(1, 8, 50, 0);

	if( !clonep() ) {
		set("wield_as", "blade");
		set("unit", "把");
		set("value", 800);
		set("rigidity", 20);
		set("long",
			"一把粗製濫造的朴刀﹐刀身佈滿鏽斑﹐刀刃也有些缺口﹐不\n"
			"過用來砍人還是綽綽有餘的。\n");
	}
	setup();
}
