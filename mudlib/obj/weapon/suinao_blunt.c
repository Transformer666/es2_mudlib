// suinao_blunt.c

#include <weapon.h>

inherit F_BLUNT;

void create()
{
    set_name("碎腦鎚", ({"suinao hammer", "suinao_blunt", "hammer"}));
    set_weight(13000);
    setup_blunt(5, 14, 200, 3);

    if( !clonep() ) {
        set("wield_as", "blunt");
        set("unit", "把");
        set("value", 380000);
        set("long",
            "一把沉重無比的戰鎚，鎚頭以精鋼澆鑄，佈滿了凹凸不平的\n"
            "鋼刺，一鎚下去便是粉身碎骨。\n");
    }
    setup();
}
