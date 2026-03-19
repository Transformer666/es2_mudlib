// blessed_jade.c

#include <armor.h>

inherit F_WAIST_EQ;

void create()
{
    set_name("萬福寶玉", ({"blessed_jade", "jade"}));
    set_weight(1000);
    setup_waist_eq();

    if( !clonep() ) {
        set("unit", "塊");
        set("value", 300000);
        set("long",
            "一塊散發著柔和光輝的寶玉，佩戴於腰間，據說能為持有者\n"
            "帶來無盡的福氣與庇佑，驅邪避災。\n");
        set("wear_as", "waist_eq");
        set("apply_armor/waist_eq", ([
            "armor": 15,
        ]));
    }
    setup();
}
