#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("夜行衣", ({"night_suit", "suit"}));
    set_weight(1500);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 4000);
        set("long",
            "一套深黑色的夜行衣﹐質地輕薄貼身﹐方便行動﹐是盜賊\n"
            "和刺客常用的裝束。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 2,
        ]));
    }
    setup();
}
