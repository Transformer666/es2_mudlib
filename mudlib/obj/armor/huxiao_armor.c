// huxiao_armor.c

#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("虎嘯旭日鎧", ({"huxiao armor", "huxiao_armor", "armor"}));
    set_weight(16000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "套");
        set("value", 450000);
        set("long",
            "一套鑲嵌著虎牙裝飾的重型鎧甲，胸甲上刻有一輪旭日，配\n"
            "合咆哮的猛虎圖紋，威武霸氣。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "armor": 40,
        ]));
    }
    setup();
}
