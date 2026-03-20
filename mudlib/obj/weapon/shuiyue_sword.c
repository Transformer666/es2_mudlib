// shuiyue_sword.c

#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("水月劍", ({"shuiyue sword", "sword"}));
    set_weight(3000);
    setup_sword(3, 13, 85, 3);

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 180000);
        set("long",
            "一把清靈秀雅的長劍，劍身映照出水月般的光影，揮動時如水中撈月，虛實難辨。\n");
    }
    setup();
}
