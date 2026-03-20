// hudao_blade.c

#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("虎頭刀", ({"hudao_blade", "blade"}));
    set_weight(5500);
    setup_blade(4, 25, 5, 3);

    if( !clonep() ) {
        set("wield_as", "blade");
        set("unit", "把");
        set("value", 15000);
        set("long",
            "一把沉重的虎頭刀，刀柄末端鑄有一顆銅製虎頭，刀身\n"
            "寬厚鋒利，乃是虎刀門弟子的標配兵器，舞動起來虎虎生風。\n");
    }
    setup();
}
