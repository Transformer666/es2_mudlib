// grilled_fish.c -- 羿水酒館的鹽烤河魚（本地下酒河鮮﹐F_FOOD 可食）
//   比照 /d/feixian/obj/braise.c：COMBINED_ITEM + F_FOOD 的尋常食物。
//   現從門外羿水裡撈的河魚﹐抹鹽炭烤﹐是這小魚村酒館的招牌河鮮。

inherit COMBINED_ITEM;
inherit F_FOOD;

void create()
{
	set_name("鹽烤河魚", ({ "grilled fish", "grilled", "kaoyu" }) );
	if( !clonep() ) {
		set("unit", "盤");
		set("base_unit", "尾");
		set("base_value", 40);
		set("base_weight", 300);
		set("heal_kee", 8);
		set("food_stuff", 110);
		set("long",
			"一尾現從羿水裡撈起的肥美河魚﹐剖洗乾淨﹐抹上一層粗鹽﹐\n"
			"架在炭火上烤得兩面焦黃﹐魚皮酥脆、魚肉雪白﹐還滋滋地冒著\n"
			"油星﹐騰起一陣勾人的焦香——是這羿水酒館頂出名的下酒河鮮。\n");
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
