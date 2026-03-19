// hoe.c

#include <weapon.h>

inherit F_AXE;

void create()
{
	set_name("鋤頭", ({"hoe", "tool"}));
	set_weight(5000);
	setup_axe(1, 6, 40, 0);

	if( !clonep() ) {
		set("wield_as", "axe");
		set("unit", "把");
		set("value", 40);
		set("rigidity", 18);
		set("long", "一把普通的鋤頭﹐鐵鋤頭安在一根結實的木柄上﹐本是用來種地的農具﹐緊急時也可以勉強當作武器使用。\n");
	}
	setup();
}
