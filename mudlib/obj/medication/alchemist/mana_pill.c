// mana_pill.c -- 醒神丹：方家提神醒腦的丹藥﹐服之回補「神」(sen)。
//
// 比照 obj/medication/alchemist/aquapill.c（金液丹）：COMBINED_ITEM﹐
// set("requirement"/"mixture_value"/"produce_param") 供 refine（煉丹）
// 的火候/品質判定讀取﹐stuff_ob 以 supplement_stat/heal_stat 調整屬性。
//
// 配方（見 cmds/std/refine.c）：靈芝×1 + 枸杞×1﹐技能門檻 alchemy-medication 20。

inherit COMBINED_ITEM;

void create()
{
	set_name("醒神丹", ({"mana pill", "mana", "pill"}));
	if( !clonep() ) {
		set("unit", "些");
		set("long",
			"醒神丹是方家用以提神醒腦的丹藥﹐以靈芝佐枸杞文火煉成﹐藥丸\n"
			"清香沁鼻。久讀傷神、苦思耗氣之後含服一粒﹐但覺神清氣朗、倦\n"
			"意盡消﹐是讀書修煉之人案頭常備的解乏靈丹。\n");
		set("base_unit", "粒");
		set("base_value", 260);
		set("base_weight", 5);
		set("mixture_value", 80);
		set("produce_param", ([
			"min_heat_power" : 80,
			"max_heat_power" : 200,
			"min_heat" : 200,
			"max_heat" : 240,
		]));
		set("requirement", ([
			"literate" : 8,
			"alchemy-medication" : 20,
		]));
	}
	set_amount(1);
	setup();
}

int stuff_ob(object me)
{
	if( me->query_stat_maximum("food") - me->query_stat("food") < 8 )
		return notify_fail("你的肚子已經撐得連這粒藥丸也吞不下去了。\n");
	message_vision("$N吞下一粒醒神丹﹐只覺一股清涼直透腦門﹐精神為之一振。\n", me);
	me->consume_stat("water", 8);
	me->supplement_stat("food", 5);
	me->heal_stat("sen", 20);
	me->supplement_stat("sen", 30);
	add_amount(-1);

	return 1;
}
// vim: set ts=4 sw=4 syntax=lpc
