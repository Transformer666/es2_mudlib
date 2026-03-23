// vim: syntax=lpc
// Armor: tiger_hide.c - 狻猊皮甲 (quest reward for hunter_beast)

#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("狻猊皮甲", ({"tiger hide", "tiger_hide", "hide"}));
    set_weight(3000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 8000);
        set("long",
            "一件用狻猊的漆黑獸皮縫製的皮甲﹐雖然看起來簡陋﹐\n"
            "但獸皮異常堅韌﹐穿在身上隱隱有一股野獸的威壓散發出來。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 8,
        ]));
    }

    setup();
}
