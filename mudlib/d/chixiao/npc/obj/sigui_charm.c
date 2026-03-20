// sigui_charm.c

#include <weapon.h>

inherit F_DAGGER;

void create()
{
    set_name("思歸符", ({"sigui_charm", "sigui charm", "charm", "dagger"}));
    set_weight(500);
    setup_dagger(7, 22, 4, 2);

    if( !clonep() ) {
        set("wield_as", "dagger");
        set("unit", "把");
        set("value", 350000);
        set("long",
            "一把形如符箓的奇異匕首，刃身上刻滿了密密麻麻的古老符文，\n"
            "散發著淡淡的金光。據說此符乃天靈化身前留下的遺物，持有者\n"
            "能感受到一股強烈的思鄉之情，彷彿靈魂正在被召喚回歸本源。\n");
    }
    setup();
}
