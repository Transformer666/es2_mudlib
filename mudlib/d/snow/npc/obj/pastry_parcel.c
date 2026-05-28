// pastry_parcel.c -- 雪亭鎮新手任務 1 的信物：張婆婆託人送給孫兒的點心

inherit ITEM;

void create()
{
	set_name("油紙包", ({ "pastry parcel", "parcel" }) );
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "包");
		set("value", 1);
		set("long",
			"一個用油紙仔細包好的小包裹﹐隔著紙還能聞到一股甜甜的點心\n"
			"香氣﹐上面用炭筆歪歪斜斜地寫著「給阿福」三個字。\n");
		set("no_sell", 1);
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
