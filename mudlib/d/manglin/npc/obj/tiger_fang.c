// vim: syntax=lpc
// Item: tiger_fang.c - 狻猊虎牙 (quest item for hunter_beast)

#include <weapon.h>

inherit F_DAGGER;

void create()
{
    set_name("狻猊虎牙", ({"tiger fang", "tiger_fang", "fang"}));
    set_weight(500);
    setup_dagger(2, 12, 3, 1);

    if( !clonep() ) {
        set("wield_as", ({"dagger"}));
        set("unit", "顆");
        set("value", 500);
        set("long",
            "一顆從狻猊口中拔下的巨大虎牙﹐足有半尺來長﹐\n"
            "牙尖鋒利無比﹐隱隱散發著一股陰寒之氣。\n");
    }
    setup();
}
