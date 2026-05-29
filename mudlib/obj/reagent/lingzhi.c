// lingzhi.c -- 靈芝，龍圖丹派煉製金液丹的藥材之一。
//
// 比照 obj/medication/boar_berry.c：用 COMBINED_ITEM 讓藥材有「數量」概念，
// 移入人物身上時會自動合併同類 (見 std/item/combined.c 的 move())，方便
// refine（煉丹）指令逐顆消耗 (add_amount(-1))。
//
// 這味藥材也可生食提神，但功效甚微，主要用途是入爐煉丹。

inherit COMBINED_ITEM;

void create()
{
	set_name("靈芝", ({ "lingzhi", "herb" }));
	if( !clonep() ) {
		set("unit", "些");
		set("long",
			"靈芝是一種傘蓋赤褐如漆的菌類﹐生於深山朽木之上﹐藥性溫和\n"
			"而平補﹐是龍圖丹派煉製金液丹的上好藥材。直接含服雖也能略\n"
			"提精神﹐但終究暴殄天物﹐不如入爐煉丹。\n");
		set("base_unit", "株");
		set("base_value", 200);
		set("base_weight", 30);
	}
	set_amount(1);
	setup();
}

int stuff_ob(object me)
{
	if( me->query_stat_maximum("food") - me->query_stat("food") < 5 )
		return notify_fail("你的肚子已經撐得什麼東西也吞不下去了。\n");
	message_vision("$N含了一株靈芝在口中慢慢嚼食。\n", me);
	me->supplement_stat("food", 3);
	me->supplement_stat("sen", 5);
	add_amount(-1);

	return 1;
}
// vim: set ts=4 sw=4 syntax=lpc
