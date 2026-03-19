#include <weapon.h>

inherit F_DAGGER;

void create()
{
    set_name("銀針", ({"silver_needle", "needle"}));
    set_weight(500);
    setup_dagger(1, 4, 20, 5);

    if( !clonep() ) {
        set("wield_as", "dagger");
        set("unit", "根");
        set("value", 3000);
        set("rigidity", 10);
        set("long",
            "一根精鋼打造的銀針﹐針身細長﹐閃閃發亮﹐既是醫療器\n"
            "具﹐也可作為武器使用。\n");
    }
    setup();
}
