// fengshan_blade.c

#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("封山劍", ({"fengshan_blade", "sword"}));
    set_weight(4500);
    setup_sword(3, 18, 5, 3);

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 12000);
        set("long",
            "一把封山派制式長劍，劍身狹長，劍柄纏著青色絲帶，\n"
            "劍鞘上刻有封山派的山形紋章，乃是門中弟子的佩劍。\n");
    }
    setup();
}
