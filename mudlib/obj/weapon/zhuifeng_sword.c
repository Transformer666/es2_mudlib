// zhuifeng_sword.c

#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("追風劍", ({"zhuifeng sword", "sword"}));
    set_weight(2800);
    setup_sword(3, 12, 90, 4);

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 200000);
        set("long",
            "一把輕若無物的長劍，出劍之速快若追風，劍身細長飄逸，專為追求極速劍法而鑄。\n");
    }
    setup();
}
