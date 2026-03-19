#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("暗影披風", ({"shadow_cloak", "cloak"}));
    set_weight(2000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 5000);
        set("long",
            "一件漆黑如墨的披風﹐質地輕薄卻異常堅韌。穿上之後﹐\n"
            "在暗處幾乎看不見人影。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 3,
        ]));
    }
    setup();
}
