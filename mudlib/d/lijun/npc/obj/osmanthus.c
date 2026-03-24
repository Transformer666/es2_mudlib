// vim: syntax=lpc
// 桂花 - quest item for tea_osmanthus quest

inherit ITEM;

void create()
{
    set_name("桂花", ({"osmanthus", "osmanthus flowers", "flowers"}));
    set_weight(100);

    if( !clonep() ) {
        set("unit", "把");
        set("value", 50);
        set("long",
            "一小把金黃色的桂花﹐花瓣嬌小可愛﹐散發著沁人心脾的\n"
            "清甜香氣﹐讓人聞了精神為之一振。\n");
    }

    setup();
}
