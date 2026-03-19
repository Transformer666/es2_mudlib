#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("丹士袍", ({"alchemy_robe", "robe"}));
    set_weight(2000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 3000);
        set("long",
            "一件淡灰色的長袍﹐袍上繡著幾朵藥草的圖案﹐是龍圖丹\n"
            "派弟子常穿的服飾。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 2,
        ]));
    }
    setup();
}
