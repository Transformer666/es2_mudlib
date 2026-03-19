#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("步玄服", ({"buxuan_cloth", "cloth"}));
    set_weight(1500);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 3500);
        set("long",
            "一件月白色的書生長衫﹐質地上佳﹐穿上之後頗有文雅之風。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 2,
        ]));
    }
    setup();
}
