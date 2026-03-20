// xuanmang.c

#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("旋芒", ({"xuanmang", "xuanmang blade", "blade"}));
    set_weight(8000);
    setup_blade(12, 100, 12, 4);

    if( !clonep() ) {
        set("wield_as", "blade");
        set("unit", "把");
        set("value", 900000);
        set("long",
            "一柄傳說中的神刀，刀身通體透明如水晶，卻鋒利無匹，據說\n"
            "此刀乃天神賦予寒於氏的兩把利刃之一，與穿靈齊名，曾在最後\n"
            "的聖戰中斬下侮天鬼的頭顱。刀身上隱隱流動著淡金色的光芒，\n"
            "似乎蘊藏著無窮的神力。\n");
    }
    setup();
}
