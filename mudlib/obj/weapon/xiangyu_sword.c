// xiangyu_sword.c

#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("鑲玉短劍", ({"xiangyu sword", "xiangyu_sword", "sword"}));
    set_weight(2500);
    setup_sword(3, 20, 50, 3);

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 80000);
        set("long",
            "一把鑲嵌著碧玉的精緻短劍，劍柄雕工細膩，是文人佩劍的\n"
            "上品。\n");
    }
    setup();
}
