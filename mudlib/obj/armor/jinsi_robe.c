// jinsi_robe.c

#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("金絲長袍", ({"jinsi robe", "jinsi_robe", "cloth"}));
    set_weight(1800);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 200000);
        set("long",
            "一件以金絲織就的華麗長袍，袍身金光閃閃，顯得尊貴非凡，\n"
            "是富貴人家的象徵。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 8,
        ]));
    }
    setup();
}
