// hudao_vest.c

#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("虎紋勁裝", ({"hudao_vest", "vest"}));
    set_weight(2500);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 10000);
        set("long",
            "一件以厚實棉布縫製的短打勁裝，前襟繡著虎頭圖案，\n"
            "衣料結實耐磨，便於格鬥，是虎刀門弟子的武服。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 4,
        ]));
    }
    setup();
}
