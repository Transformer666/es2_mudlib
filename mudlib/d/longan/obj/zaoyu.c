// zaoyu.c -- 無腸酒店的糟魚（本地下酒菜﹐F_FOOD 可食﹐鏡 d/feixian/obj/braise.c）。

inherit COMBINED_ITEM;
inherit F_FOOD;

void create()
{
	set_name("糟魚", ({ "braised fish", "zaoyu" }) );
	if( !clonep() ) {
		set("unit", "盤");
		set("base_unit", "塊");
		set("base_value", 70);
		set("base_weight", 320);
		set("heal_kee", 7);
		set("food_stuff", 100);
		set("long",
			"無腸酒店用本地新撈的青魚、配著自釀的酒糟醃燉出來的糟\n"
			"魚﹐魚肉酥透入味﹐帶著一股醇厚的酒糟香﹐鹹鮮裡透著回甘﹐\n"
			"是這水鄉佐酒的一道妙物。\n");
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
