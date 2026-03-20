// bawang_pike.c

#include <weapon.h>

inherit F_PIKE;

void create()
{
    set_name("霸王槍", ({"bawang pike", "bawang_pike", "pike"}));
    set_weight(11000);
    setup_pike(4, 18, 80, 6);

    if( !clonep() ) {
        set("wield_as", "pike");
        set("unit", "把");
        set("value", 350000);
        set("long",
            "一桿霸氣十足的長槍，槍身粗如兒臂，鑄以精鋼，槍頭寒光\n"
            "閃閃，乃是軍中大將專用的重型兵器。\n");
    }
    setup();
}
