// tailor_needle.c

#include <weapon.h>

inherit F_NEEDLE;

void create()
{
    set_name("繡花銀針", ({"tailor needle", "tailor_needle", "needle"}));
    set_weight(200);
    setup_needle(5, 14, 80, 3);

    if( !clonep() ) {
        set("wield_as", "needle");
        set("unit", "枚");
        set("value", 350000);
        set("long",
            "一枚精緻的銀針，表面刻有細密的花紋，看似繡花用的工具，\n"
            "實則是殺人於無形的暗器，出手迅捷令人防不勝防。\n");
    }
    setup();
}
