// zijin_pike.c

#include <weapon.h>

inherit F_PIKE;

void create()
{
    set_name("紫金鳳頭錐", ({"zijin_pike", "pike"}));
    set_weight(12000);
    setup_pike(4, 14, 80, 10);

    if( !clonep() ) {
        set("wield_as", "pike");
        set("unit", "把");
        set("value", 350000);
        set("long",
            "一柄以紫金鑄造的長錐，錐頭雕刻成鳳首形狀，華貴非凡，\n"
            "揮動時帶起陣陣紫金光芒，氣勢凌人。\n");
    }
    setup();
}
