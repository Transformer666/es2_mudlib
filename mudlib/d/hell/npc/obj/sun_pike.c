// sun_pike.c

#include <weapon.h>

inherit F_PIKE;

void create()
{
    set_name("太陽槍", ({"sun_pike", "sun pike", "pike"}));
    set_weight(10000);
    setup_pike(10, 70, 8, 7);

    if( !clonep() ) {
        set("wield_as", "pike");
        set("unit", "把");
        set("value", 800000);
        set("long",
            "一柄閃耀著金色光芒的長槍，槍尖處凝聚著灼熱的日炎之力，\n"
            "彷彿一輪小太陽鑲嵌其上。此槍乃地靈任務中的關鍵道具，\n"
            "傳說能引導太陽之力驅散地獄中的黑暗。\n");
    }
    setup();
}
