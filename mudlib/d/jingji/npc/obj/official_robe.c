// official_robe.c

#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("官服", ({"official_robe", "robe"}));
    set_weight(2000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 15000);
        set("long",
            "一件深藍色的官府制式服飾，胸前繡著雲紋補子，腰繫\n"
            "玉帶，雖不如高官華服精美，卻也頗具威嚴。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 3,
        ]));
    }
    setup();
}
