// danggui.c -- 當歸，龍圖丹派煉製金液丹的藥材之一。
//
// 比照 obj/medication/boar_berry.c：COMBINED_ITEM，移入人物身上時自動
// 合併同類，refine（煉丹）逐份消耗。當歸補血活血，是金液丹療傷藥性的來源。

inherit COMBINED_ITEM;

void create()
{
	set_name("當歸", ({ "danggui", "herb" }));
	if( !clonep() ) {
		set("unit", "些");
		set("long",
			"當歸是一種常見的補血藥材﹐根莖肥碩﹐氣味芳香﹐補血活血﹐\n"
			"是龍圖丹派煉製金液丹療傷藥性的來源。生嚼略帶辛甘﹐主要還\n"
			"是用來入爐煉丹。\n");
		set("base_unit", "支");
		set("base_value", 120);
		set("base_weight", 40);
	}
	set_amount(1);
	setup();
}

int stuff_ob(object me)
{
	if( me->query_stat_maximum("food") - me->query_stat("food") < 5 )
		return notify_fail("你的肚子已經撐得什麼東西也吞不下去了。\n");
	message_vision("$N咬了一口當歸﹐辛甘的藥味在口中化開。\n", me);
	me->supplement_stat("food", 3);
	me->supplement_stat("kee", 5);
	add_amount(-1);

	return 1;
}
// vim: set ts=4 sw=4 syntax=lpc
