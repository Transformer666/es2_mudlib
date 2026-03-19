// rapid_sword.c

#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("疾風劍", ({"rapid_sword", "sword"}));
    set_weight(4000);
    setup_sword(4, 12, 100, 5);

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 250000);
        set("long",
            "一把輕巧的寶劍，劍身薄如蟬翼，揮動時彷彿能斬斷風本身，\n"
            "出劍速度快如疾風，令人防不勝防。\n");
    }
    setup();
}
