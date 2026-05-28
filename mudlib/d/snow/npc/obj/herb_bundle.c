// herb_bundle.c -- 雪亭鎮新手任務 2 的信物：老藥農替順生堂採的一捆草藥

inherit ITEM;

void create()
{
	set_name("草藥", ({ "herb bundle", "herb", "bundle" }) );
	set_weight(300);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "捆");
		set("value", 1);
		set("long",
			"一捆新鮮採下的草藥﹐根莖上還沾著郊野的泥土﹐散發出一股\n"
			"清苦的藥草香氣。這是順生堂託老藥農採來的藥材﹐該趕緊送\n"
			"回藥鋪去。\n");
		set("no_sell", 1);
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
