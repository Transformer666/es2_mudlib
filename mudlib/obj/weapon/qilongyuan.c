// qilongyuan.c

#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("泣龍怨", ({"qilongyuan", "qilongyuan sword", "sword"}));
    set_weight(9000);
    setup_sword(5, 18, 140, 5);

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 550000);
        set("long",
            "一把散發著龍吟之聲的巨劍，劍身隱約浮現龍鱗紋路，每一次\n"
            "揮斬都伴隨著如泣如訴的龍嘯，氣勢懾人。\n");
    }
    setup();
}
