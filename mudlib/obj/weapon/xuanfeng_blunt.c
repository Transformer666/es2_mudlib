// xuanfeng_blunt.c

#include <weapon.h>

inherit F_BLUNT;

void create()
{
    set_name("旋風流星槌", ({"xuanfeng blunt", "xuanfeng_blunt", "blunt"}));
    set_weight(12000);
    setup_blunt(5, 14, 200, 4);

    if( !clonep() ) {
        set("wield_as", "blunt");
        set("unit", "把");
        set("value", 500000);
        set("long",
            "一把以精鋼鑄成的流星槌，鎚頭圓大如斗，以鎖鏈相連，揮舞\n"
            "起來如旋風般呼嘯，勢不可擋。\n");
    }
    setup();
}
