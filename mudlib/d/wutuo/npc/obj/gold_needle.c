#include <weapon.h>

inherit F_DAGGER;

void create()
{
    set_name("金針", ({"gold_needle", "needle"}));
    set_weight(300);
    setup_dagger(1, 5, 25, 6);

    if( !clonep() ) {
        set("wield_as", "dagger");
        set("unit", "根");
        set("value", 5000);
        set("rigidity", 8);
        set("long",
            "一根精金打造的針灸針﹐針身纖細而堅韌﹐閃著金色的光\n"
            "芒﹐是武陀門下至寶。\n");
    }
    setup();
}
