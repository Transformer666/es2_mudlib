// fury_whip.c

#include <weapon.h>

inherit F_WHIP;

void create()
{
    set_name("怒天鞭", ({"fury whip", "fury_whip", "whip"}));
    set_weight(3500);
    setup_whip(5, 12, 90, 8);

    if( !clonep() ) {
        set("wield_as", "whip");
        set("unit", "條");
        set("value", 320000);
        set("long",
            "一條通體赤紅的長鞭，鞭身以玄鐵打造，揮動時發出震耳欲聾\n"
            "的怒吼，彷彿天神之怒降臨人間，乃八寶樓中的至寶。\n");
    }
    setup();
}
