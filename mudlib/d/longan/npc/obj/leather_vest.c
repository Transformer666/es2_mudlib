// leather_vest.c

#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("皮甲", ({"leather_vest", "vest"}));
    set_weight(3000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 3000);
        set("long",
            "一件以牛皮硝製而成的皮甲，雖然粗糙，但結實耐用，\n"
            "能擋住一般的刀劍劈砍，是龍安鎮常見的防具。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 3,
        ]));
    }
    setup();
}
