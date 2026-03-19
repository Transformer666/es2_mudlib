#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("玄天劍", ({"xuantian_sword", "sword"}));
    set_weight(6000);
    setup_sword(2, 13, 42, 3);

    if( !clonep() ) {
        set("wield_as", ({"sword"}));
        set("unit", "把");
        set("value", 9000);
        set("rigidity", 32);
        set("long",
            "一把黑色的長劍﹐劍身上刻著北斗七星的圖案﹐劍氣森森。\n");
    }
    setup();
}
