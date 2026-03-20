// black_steel_dagger.c

#include <weapon.h>

inherit F_DAGGER;

void create()
{
    set_name("黑鋼短刃", ({"black steel dagger", "black_steel_dagger", "dagger"}));
    set_weight(600);
    setup_dagger(3, 10, 50, 2);

    if( !clonep() ) {
        set("wield_as", "dagger");
        set("unit", "把");
        set("value", 180000);
        set("long",
            "一把以黑鋼鑄造的短刃，刃身漆黑如墨，鋒利無比，乃八寶樓\n"
            "中的精品暗器，適合近身搏殺。\n");
    }
    setup();
}
