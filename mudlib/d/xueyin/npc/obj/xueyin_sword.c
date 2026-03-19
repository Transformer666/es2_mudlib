#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("雪吟劍", ({"xueyin_sword", "sword"}));
    set_weight(7000);
    setup_sword(2, 14, 48, 3);

    if( !clonep() ) {
        set("wield_as", ({"sword"}));
        set("unit", "把");
        set("value", 10000);
        set("rigidity", 35);
        set("long",
            "一把闊劍﹐劍身寬厚﹐刃口鋒利﹐揮動時發出呼呼的風聲\n"
            "﹐是雪吟莊的制式兵器。\n");
    }
    setup();
}
