// zhenwu_pike.c

#include <weapon.h>

inherit F_PIKE;

void create()
{
    set_name("振武槍", ({"zhenwu_pike", "pike"}));
    set_weight(7500);
    setup_pike(5, 30, 5, 5);

    if( !clonep() ) {
        set("wield_as", "pike");
        set("unit", "把");
        set("value", 15000);
        set("long",
            "一把振武軍營制式長槍，槍頭比一般軍槍更為寬大，槍纓\n"
            "為鮮紅色，在戰場上極為醒目，是振武營精兵的佩器。\n");
    }
    setup();
}
