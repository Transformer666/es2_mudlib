// rice_wine.c -- 龍安米酒：水鄉小鎮自釀的溫醇米酒（LIQUID + F_DRINK﹐可 drink）。
//   鏡 /obj/water.c 的 LIQUID_ITEM + F_DRINK 範式。F_VENDOR 賣酒時自動以
//   /obj/bottle 盛裝交付（見 feature/npc/vendor.c::deliver_merchandise 的 liquid 分支）。
//   value = base_value * volume（liquid.c::render_value）；含 alcohol﹐drink 會微醺。

inherit LIQUID_ITEM;
inherit F_DRINK;

void create()
{
	set_name("龍安米酒", ({ "rice wine", "wine", "longan wine" }));
	if( !clonep() ) {
		set("long",
			"一甕龍安水鄉自釀的米酒﹐酒色微微泛著琥珀的暖黃﹐溫醇\n"
			"裡帶著一股米糧的清甜﹐後勁卻不容小覷。鎮上人說﹐這酒是\n"
			"取了溪河上游的活水、襯著新採的荷葉封甕釀成的﹐聞香下\n"
			"馬﹐是這一帶頂出名的好酒。(可用 drink 飲用)\n");
		set("density", 1);
		set("base_value", 1);	// value = base_value * volume；一瓶約得百來文。
		set("alcohol", 8);
	}
	setup();
	set_volume(100);
}

// vim: set ts=4 sw=4 syntax=lpc
