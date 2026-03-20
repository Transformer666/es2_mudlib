// xuanyao.c

#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("旋耀", ({"xuanyao", "xuanyao blade", "blade"}));
    set_weight(8000);
    setup_blade(10, 90, 11, 4);

    if( !clonep() ) {
        set("wield_as", "blade");
        set("unit", "把");
        set("value", 950000);
        set("long",
            "一把散發著耀眼金光的寬刃大刀，刀身不斷旋轉著細微的光芒\n"
            "，傳說此刀乃是日月精華所鑄，揮動時光芒萬丈，敵人未近身\n"
            "便已被其光華所灼傷。\n");
    }
    setup();
}
