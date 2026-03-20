// wind_god_feather.c

#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("風神之羽", ({"wind god feather", "wind_god_feather", "sword"}));
    set_weight(9000);
    setup_sword(9, 30, 200, 5);

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 800000);
        set("long",
            "一把蘊含風神之力的巨劍，劍身輕盈如羽，揮舞時卻能掀起驚\n"
            "天狂風，需要雙手方能駕馭其中蘊藏的磅礴力量。\n");
    }
    setup();
}
