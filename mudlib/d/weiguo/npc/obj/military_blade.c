// military_blade.c

#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("軍刀", ({"military_blade", "blade"}));
    set_weight(4500);
    setup_blade(3, 20, 4, 3);

    if( !clonep() ) {
        set("wield_as", "blade");
        set("unit", "把");
        set("value", 8000);
        set("long",
            "一把衛國軍制式單刀，刀身略窄，刀背厚實，適合劈砍\n"
            "與格擋，是衛國軍中將官常佩的兵器。\n");
    }
    setup();
}
