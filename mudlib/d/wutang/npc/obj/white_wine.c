// vim: syntax=lpc

inherit ITEM;

void create()
{
    set_name("白干酒", ({"wine", "white_wine", "liquor"}));
    set_weight(400);
    if( !clonep() ) {
	set("unit", "壺");
	set("value", 400);
	set("long", "一壺清澈的白干酒﹐聞起來十分醇厚。\n");
    }
    setup();
}
