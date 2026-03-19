#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("玄衣", ({"xuan_cloth", "cloth"}));
    set_weight(2000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 3500);
        set("long",
            "一件黑色的道袍﹐袍上繡著北斗七星和玄天上帝的符文。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 2,
        ]));
    }
    setup();
}
