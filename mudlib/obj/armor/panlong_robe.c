// panlong_robe.c

#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("蟠龍朝服", ({"panlong robe", "panlong_robe", "cloth"}));
    set_weight(3000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 250000);
        set("long",
            "一件繡有蟠龍圖案的華麗朝服，以金絲銀線織就，光彩奪目，\n"
            "是朝廷重臣才有資格穿著的禮服。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 10,
        ]));
    }
    setup();
}
