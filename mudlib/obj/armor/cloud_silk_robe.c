// cloud_silk_robe.c

#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("雲羅絲衣", ({"cloud silk robe", "cloud_silk_robe"}));
    set_weight(1500);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 250000);
        set("long",
            "一件以天蠶絲織就的輕衣，薄如雲翳，輕若無物，穿著時如身披雲霓，飄逸出塵。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 15,
        ]));
    }
    setup();
}
