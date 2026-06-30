// fish.c -- 一尾小魚（釣魚 fish 指令的漁獲）
//
// 比照 obj/food/dumpling.c / manto.c：COMBINED_ITEM + F_FOOD 的尋常食物。
// 釣上來的小魚可生著充飢（food_stuff），也能賣幾文錢（base_value）。
// 數值為初版、可調；定位是低價值的雜魚，故與饅頭包子相當、略低。

inherit COMBINED_ITEM;
inherit F_FOOD;

void create()
{
	set_name("小魚", ({ "small fish", "fish" }) );
	if( !clonep() ) {
		set("unit", "簍");
		set("base_unit", "尾");
		set("base_value", 8);       // 雜魚不值錢，初版每尾 8 文（可調）
		set("base_weight", 120);
		set("food_stuff", 60);      // 生魚充飢有限，略低於饅頭（可調）
		set("long", "一尾活蹦亂跳的小魚﹐方纔自港邊的水裡釣上來﹐鱗光閃閃。\n");
	}
	set_amount(1);   // 比照 medication COMBINED_ITEM 範式：clone 顯式設量，勿賴 setup() 條件式（見 eat 缺陷修正）
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
