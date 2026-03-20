// mingmo_staff.c

#include <weapon.h>

inherit F_STAFF;

void create()
{
    set_name("冥魔杖", ({"mingmo staff", "mingmo_staff", "staff"}));
    set_weight(8000);
    setup_staff(3, 22, 200, 6);

    if( !clonep() ) {
        set("wield_as", "staff");
        set("unit", "根");
        set("value", 450000);
        set("long",
            "一根漆黑如墨的法杖，杖頂鑲嵌著一顆散發紫黑色光芒的寶珠，\n"
            "周圍瀰漫著不祥的冥氣，持杖者攻守兼備。\n");
    }
    setup();
}
