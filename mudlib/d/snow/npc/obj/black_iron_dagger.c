// vim: syntax=lpc
// black_iron_dagger.c - 玄鐵短刀 (reward for smith_black_iron quest)

#include <weapon.h>

inherit F_DAGGER;

void create()
{
    set_name("玄鐵短刀", ({"black iron dagger", "dagger", "iron dagger"}));
    set_weight(3000);
    setup_dagger(3, 18, 3, 2);

    if( !clonep() ) {
	set("wield_as", ({"dagger"}));
	set("unit", "把");
	set("value", 8000);
	set("long",
	    "這把短刀由上好的玄鐵打造而成﹐刀身呈暗銀色﹐鋒利異常﹐\n"
	    "是鐵匠精心鍛造的得意之作。\n");
    }
    setup();
}
