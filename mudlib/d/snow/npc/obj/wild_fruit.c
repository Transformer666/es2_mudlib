// vim: syntax=lpc
// wild_fruit.c - 靈狙任務獎勵：野果
// 靈狙送給玩家的特殊果實，食用可恢復少量精氣神

inherit COMBINED_ITEM;
inherit F_FOOD;

void create()
{
	set_name("靈果", ({"wild fruit", "fruit", "spirit fruit"}));
	if( !clonep() ) {
		set("unit", "堆");
		set("base_unit", "顆");
		set("base_value", 500);
		set("base_weight", 50);
		set("food_stuff", 200);
		set("long",
			"一顆渾圓飽滿的金色果實﹐散發著淡淡的清香﹐表面微微泛\n"
			"著光澤﹐似乎蘊含著某種靈氣。據說是靈狙在深山中採集的珍\n"
			"貴果實。\n");
	}
	setup();
}
