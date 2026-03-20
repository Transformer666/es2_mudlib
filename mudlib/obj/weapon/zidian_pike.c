// zidian_pike.c

#include <weapon.h>

inherit F_PIKE;

void create()
{
    set_name("紫電紅纓槍", ({"zidian pike", "zidian_pike", "pike"}));
    set_weight(9000);
    setup_pike(4, 18, 70, 7);

    if( !clonep() ) {
        set("wield_as", "pike");
        set("unit", "把");
        set("value", 420000);
        set("long",
            "一桿閃爍著紫色電光的紅纓長槍，槍纓鮮紅如血，槍身纏繞\n"
            "著雷電之力，刺出時電光四射，攻守兼備。\n");
    }
    setup();
}
