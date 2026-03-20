// spirit_wine.c

inherit ITEM;

void create()
{
	set_name("靈酒", ({"spirit_wine", "wine", "drink"}));
	set_weight(400);
	if( !clonep() ) {
		set("unit", "壺");
		set("value", 20);
		set("long", "一壺用山泉和不知名草藥釀製的酒﹐酒色微紅﹐帶著淡淡的辛辣香氣﹐據說有驅邪暖身之效。\n");
	}
	setup();
}
