// silk_fishing_rod.c

#include <weapon.h>

inherit F_WHIP;

void create()
{
    set_name("青絲釣竿", ({"silk fishing rod", "silk_fishing_rod", "rod"}));
    set_weight(2000);
    setup_whip(3, 10, 60, 7);

    if( !clonep() ) {
        set("wield_as", "whip");
        set("unit", "根");
        set("value", 150000);
        set("long",
            "一根以青絲編織的特殊釣竿，既可垂釣又可作為武器使用，柔\n"
            "韌的竿身揮舞起來猶如軟鞭，乃煙波釣叟的隨身之物。\n");
    }
    setup();
}
