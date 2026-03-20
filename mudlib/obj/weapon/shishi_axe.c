// shishi_axe.c

#include <weapon.h>

inherit F_AXE;

void create()
{
    set_name("十石大斧", ({"shishi axe", "shishi_axe", "axe"}));
    set_weight(15000);
    setup_axe(5, 25, 180, 4);

    if( !clonep() ) {
        set("wield_as", "axe");
        set("unit", "把");
        set("value", 400000);
        set("long",
            "一把重達十石的巨型戰斧，斧刃寬闊如扇，非力大無窮者不能\n"
            "揮舞，一斧劈下可開山裂石。\n");
    }
    setup();
}
