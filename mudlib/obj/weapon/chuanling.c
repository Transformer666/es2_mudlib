// chuanling.c

#include <weapon.h>

inherit F_PIKE;

void create()
{
    set_name("穿靈", ({"chuanling", "chuanling pike", "pike"}));
    set_weight(12000);
    setup_pike(12, 80, 8, 7);

    if( !clonep() ) {
        set("wield_as", "pike");
        set("unit", "把");
        set("value", 900000);
        set("long",
            "一柄傳說中的神槍，槍身如白骨般慘白，槍尖處凝聚著一縷\n"
            "不散的幽魂，據說此槍能穿透一切靈體與護甲，乃是上古神話\n"
            "中令鬼神膽寒的絕世凶器。\n");
    }
    setup();
}
