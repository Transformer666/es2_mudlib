// tianling_dagger.c

#include <weapon.h>

inherit F_DAGGER;

void create()
{
    set_name("天靈匕首", ({"tianling_dagger", "tianling dagger", "dagger"}));
    set_weight(1500);
    setup_dagger(6, 20, 3, 2);

    if( !clonep() ) {
        set("wield_as", "dagger");
        set("unit", "把");
        set("value", 300000);
        set("long",
            "一把散發著幽幽靈光的匕首，刃身薄如蟬翼卻堅不可摧，乃\n"
            "是擊敗天靈後凝聚而成的神兵，蘊含著天界的靈力。\n");
    }
    setup();
}
