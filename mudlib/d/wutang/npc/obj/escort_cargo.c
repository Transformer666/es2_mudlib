// escort_cargo.c -- 五堂鎮鏢局支線任務的信物：失落的鏢物（一只描金漆盒）

inherit ITEM;

void create()
{
	set_name("鏢物", ({ "escort cargo", "cargo", "lacquer box" }) );
	set_weight(300);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "只");
		set("value", 1);
		set("long",
			"一只巴掌大的描金漆盒﹐盒蓋上貼著鎮遠鏢局的紅紙封條﹐封條\n"
			"邊角已被蹭得有些起毛。掂在手裡沉甸甸的﹐想是哪位主顧託鏢\n"
			"局押運的要緊物事﹐半道上不知怎的失落了﹐該趕緊送回鏢局去。\n");
		set("no_sell", 1);
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
