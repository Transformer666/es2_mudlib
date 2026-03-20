// fish_belly_pearl.c

inherit ITEM;

void create()
{
    set_name("河魚腹珠", ({"fish belly pearl", "fish_belly_pearl", "pearl"}));
    set_weight(100);

    if( !clonep() ) {
        set("unit", "顆");
        set("value", 80000);
        set("long",
            "一顆在河魚腹中歷經多年孕育而成的珍珠，圓潤剔透，散發著\n"
            "柔和的銀白色光芒，乃珍寶商人極為珍視的交易之物。\n");
    }
    setup();
}
