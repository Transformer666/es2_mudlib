// black_spark.c

#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("離玄光熾", ({"black spark", "black_spark", "sword"}));
    set_weight(3500);
    setup_sword(5, 15, 110, 4);

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 280000);
        set("long",
            "一把漆黑的短劍，劍身不時閃爍著幽暗的光芒，彷彿蘊含著某種玄秘的力量，\n"
            "出劍時光影交錯。\n");
    }
    setup();
}
