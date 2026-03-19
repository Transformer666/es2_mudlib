// dragon_whip.c

#include <weapon.h>

inherit F_WHIP;

void create()
{
    set_name("毒龍鞭", ({"dragon_whip", "whip"}));
    set_weight(3000);
    setup_whip(5, 10, 80, 8);

    if( !clonep() ) {
        set("wield_as", "whip");
        set("unit", "條");
        set("value", 300000);
        set("long",
            "一條漆黑的長鞭，鞭身電光閃爍，表面不斷滲出毒液，揮動\n"
            "時發出尖銳的破空聲，令人膽寒。\n");
    }
    setup();
}
