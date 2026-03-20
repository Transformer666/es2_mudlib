// rainnar_cloth.c

#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("雨師妾袍", ({"rainnar cloth", "rainnar_cloth"}));
    set_weight(2000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 280000);
        set("long",
            "一件繡有五條栩栩如生毒蛇圖案的長袍，袍身輕薄如雨絲，穿著時彷彿能感受到雨師的庇佑。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 20,
        ]));
    }
    setup();
}
