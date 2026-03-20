// jiaogu_blade.c

#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("蛟骨刀", ({"jiaogu blade", "jiaogu_blade", "blade"}));
    set_weight(6000);
    setup_blade(4, 22, 110, 4);

    if( !clonep() ) {
        set("wield_as", "blade");
        set("unit", "把");
        set("value", 500000);
        set("long",
            "一把以蛟龍之骨鍛造而成的寶刀，刀身泛著幽綠色的光澤，隱\n"
            "隱散發出一股凌厲的殺氣，令人不寒而慄。\n");
    }
    setup();
}
