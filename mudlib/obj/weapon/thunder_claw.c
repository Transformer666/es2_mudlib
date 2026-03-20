// thunder_claw.c

#include <weapon.h>

inherit F_BLUNT;

void create()
{
    set_name("雷熊爪", ({"thunder claw", "thunder_claw", "blunt"}));
    set_weight(2500);
    setup_blunt(4, 14, 70, 2);

    if( !clonep() ) {
        set("wield_as", "blunt");
        set("unit", "副");
        set("value", 280000);
        set("long",
            "以雷熊利爪打造的兵器，三根鋒利的爪刃閃爍著電光，揮擊時雷聲轟鳴，\n"
            "威力驚人。\n");
    }
    setup();
}
