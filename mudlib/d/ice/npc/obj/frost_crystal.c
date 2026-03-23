// vim: syntax=lpc
// Item: frost_crystal.c - 寒冰結晶 (quest reward for ice_guardian)

#include <weapon.h>

inherit F_BLUNT;

void create()
{
    set_name("寒冰結晶", ({"frost crystal", "frost_crystal", "crystal"}));
    set_weight(1500);
    setup_blunt(3, 18, 5, 2);

    if( !clonep() ) {
        set("wield_as", ({"blunt"}));
        set("unit", "塊");
        set("value", 2000);
        set("long",
            "一塊拳頭大小的深藍色結晶﹐寒氣逼人﹐握在手中有一種\n"
            "刺骨的冰冷。這是冰域守衛身上凝聚了數百年寒氣的精華。\n");
    }
    setup();
}
