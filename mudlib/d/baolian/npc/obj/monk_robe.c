#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("僧袍", ({"monk_robe", "robe"}));
    set_weight(2000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 3000);
        set("long",
            "一件金色的袈裟﹐上面繡著蓮花圖案﹐穿上之後頗具佛門\n"
            "威儀。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 3,
        ]));
    }
    setup();
}
