// zuixia.c -- 無腸酒店的醉蝦（本地下酒菜﹐F_FOOD 可食﹐鏡 d/feixian/obj/braise.c）。

inherit COMBINED_ITEM;
inherit F_FOOD;

void create()
{
	set_name("醉蝦", ({ "drunken shrimp", "zuixia" }) );
	if( !clonep() ) {
		set("unit", "缽");
		set("base_unit", "碟");
		set("base_value", 90);
		set("base_weight", 280);
		set("heal_kee", 6);
		set("food_stuff", 90);
		set("long",
			"無腸酒店的招牌醉蝦——一缽活蹦的河蝦﹐用上好的龍安米\n"
			"酒生生醃醉了﹐揭蓋時蝦子還在酒裡微微抽動﹐酒香裹著蝦的\n"
			"鮮甜﹐入口冰涼鮮活﹐是老饕們最饞的一味下酒物。\n");
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
