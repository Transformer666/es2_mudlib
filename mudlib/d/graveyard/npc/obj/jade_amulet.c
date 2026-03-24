// vim: syntax=lpc
// 護身玉符 - reward from stele_prayer quest

#include <armor.h>

inherit F_NECK_EQ;

void create()
{
    set_name("護身玉符", ({"jade amulet", "amulet", "jade_amulet"}));
    set_weight(200);
    setup_neck_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 5000);
        set("long",
            "一枚晶瑩剔透的玉符﹐上面刻著一個古老的「安」字﹐散發\n"
            "著淡淡的柔和光芒。佩戴在身上﹐心中莫名地感到一陣安寧。\n");
        set("wear_as", "neck_eq");
        set("apply_armor/neck_eq", ([
            "armor": 2,
        ]));
    }

    setup();
}
