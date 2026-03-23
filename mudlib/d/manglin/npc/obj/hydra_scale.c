// vim: syntax=lpc
// Armor: hydra_scale.c - 蛟鱗甲 (quest reward for manglin_hydra)

#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("蛟鱗甲", ({"hydra scale", "hydra_scale", "scale armor"}));
    set_weight(4000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 15000);
        set("long",
            "以鮫蛟鱗甲縫製的護身甲，鱗片如同精鋼般堅硬，泛著\n"
            "幽幽的深青色光澤。穿上之後感覺渾身被一層冰涼的水氣\n"
            "包裹，彷彿置身深水之中。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 12,
        ]));
    }

    setup();
}
