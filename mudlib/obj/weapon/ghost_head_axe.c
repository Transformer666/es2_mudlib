// ghost_head_axe.c

#include <weapon.h>

inherit F_AXE;

void create()
{
    set_name("鬼頭劈象刀", ({"ghost head axe", "axe"}));
    set_weight(9000);
    setup_axe(5, 25, 160, 3);

    if( !clonep() ) {
        set("wield_as", "axe");
        set("unit", "把");
        set("value", 350000);
        set("long",
            "一把巨型戰斧，斧頭雕刻著猙獰的鬼面，據說此斧曾劈開過巨象，威力驚天動地。\n");
    }
    setup();
}
