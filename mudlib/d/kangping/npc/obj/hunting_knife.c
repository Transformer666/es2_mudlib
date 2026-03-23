// hunting_knife.c

#include <weapon.h>

inherit F_DAGGER;

void create()
{
	set_name("獵刀", ({"hunting_knife", "knife"}));
	set_weight(3000);
	setup_dagger(1, 6, 40, 0);

	if( !clonep() ) {
		set("wield_as", "dagger");
		set("unit", "把");
		set("value", 800);
		set("rigidity", 20);
		set("long", "一把村裡鐵匠打造的獵刀﹐刀身短而厚實﹐適合劈砍柴木和防身。\n");
	}
	setup();
}
