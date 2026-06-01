// peachcake.c -- 醉月茶寮的桃花糕（武陵桃林落英入饌﹐本地甜點﹐F_FOOD 可食）

inherit COMBINED_ITEM;
inherit F_FOOD;

void create()
{
	set_name("桃花糕", ({ "peach blossom cake", "peach cake", "taohuagao" }) );
	if( !clonep() ) {
		set("unit", "屜");
		set("base_unit", "塊");
		set("base_value", 40);
		set("base_weight", 200);
		set("heal_kee", 4);
		set("food_stuff", 85);
		set("long",
			"一塊粉嫩的桃花糕﹐是武陵人家拿三月桃林裡新落的花瓣﹐\n"
			"和著糯米、白糖蒸成的時令甜點﹐糕面上還嵌著一兩片淺紅的\n"
			"花瓣﹐入口清甜軟糯﹐隱隱透著一縷桃花的香氣。\n");
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
