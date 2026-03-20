// flame_arrow.c

#include <weapon.h>

inherit F_NEEDLE;

void create()
{
    set_name("炎日箭", ({"flame_arrow", "flame arrow", "arrow"}));
    set_weight(800);
    setup_needle(8, 25, 4, 3);

    if( !clonep() ) {
        set("wield_as", "needle");
        set("unit", "支");
        set("value", 500000);
        set("long",
            "一支燃燒著永恆火焰的金色箭矢，箭身以不知名的金屬鑄成，\n"
            "箭尖處凝聚著灼熱的日炎之力，即使在地獄的幽暗之中也能\n"
            "照亮四方。此箭乃地靈任務中的關鍵道具。\n");
    }
    setup();
}
