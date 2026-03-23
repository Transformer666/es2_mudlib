// vim: syntax=lpc
// black_iron.c - 玄鐵礦石 (quest item for smith_black_iron quest)

inherit ITEM;

void create()
{
    set_name("玄鐵礦石", ({"black iron", "iron ore", "ore"}));
    set_weight(5000);
    if( !clonep() ) {
	set("unit", "塊");
	set("value", 100);
	set("long",
	    "一塊烏黑發亮的鐵礦石﹐質地細密﹐拿在手裡沉甸甸的。這\n"
	    "種玄鐵十分稀少﹐是鑄造利器的上等材料。\n");
    }
    setup();
}
