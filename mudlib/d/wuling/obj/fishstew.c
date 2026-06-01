// fishstew.c -- 醉月茶寮的招牌溪魚羹（取水嵐溪中鮮魚﹐本地吃食﹐F_FOOD 可食）

inherit COMBINED_ITEM;
inherit F_FOOD;

void create()
{
	set_name("溪魚羹", ({ "stream fish stew", "fish stew", "xiyu" }) );
	if( !clonep() ) {
		set("unit", "鍋");
		set("base_unit", "碗");
		set("base_value", 60);
		set("base_weight", 320);
		set("heal_kee", 6);
		set("food_stuff", 95);
		set("long",
			"一碗熱騰騰的溪魚羹﹐取的是水嵐溪裡現撈的肥魚﹐去骨切\n"
			"作細片﹐佐以嫩筍、薑絲與山菌慢火吊成﹐湯色奶白﹐鮮甜不\n"
			"腥﹐喝下去渾身都暖了﹐是武陵人待客的一道家常好湯。\n");
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
