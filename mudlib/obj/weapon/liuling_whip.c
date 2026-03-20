// liuling_whip.c

#include <weapon.h>

inherit F_WHIP;

void create()
{
    set_name("六靈妖姬鞭", ({"liuling whip", "whip"}));
    set_weight(2000);
    setup_whip(6, 15, 90, 7);

    if( !clonep() ) {
        set("wield_as", "whip");
        set("unit", "條");
        set("value", 250000);
        set("long",
            "一條華麗的軟鞭，鞭身以六種靈獸的筋腱編織而成，揮動時發出如妖姬般魅惑的聲響。\n");
    }
    setup();
}
