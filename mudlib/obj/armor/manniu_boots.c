// manniu_boots.c

#include <armor.h>

inherit F_FEET_EQ;

void create()
{
    set_name("蠻牛靴", ({"manniu boots", "manniu_boots", "boots"}));
    set_weight(2000);
    setup_feet_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 100000);
        set("long",
            "一雙以蠻牛皮革縫製的厚重戰靴，靴面粗獷結實，踩踏之下\n"
            "塵土飛揚。\n");
        set("wear_as", "feet_eq");
        set("apply_armor/feet_eq", ([
            "armor": 12,
        ]));
    }
    setup();
}
