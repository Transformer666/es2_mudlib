// monk_kasaya.c

#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("僧袍袈裟", ({"monk_kasaya", "kasaya"}));
    set_weight(2000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 5000);
        set("long",
            "一件以粗布縫製的褐色僧袍，外披一襲金線縫邊的袈裟，\n"
            "雖然樸素卻透著莊嚴肅穆的氣息，是白象寺僧人的日常衣著。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 3,
        ]));
    }
    setup();
}
