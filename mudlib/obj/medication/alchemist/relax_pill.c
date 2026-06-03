// relax_pill.c -- 養心丹：方家養心安神的丹藥﹐回補「精」(gin) 並解疲勞 (fatigue)。
//
// 比照 obj/medication/alchemist/aquapill.c（金液丹）：COMBINED_ITEM﹐
// set("requirement"/"mixture_value"/"produce_param") 供 refine（煉丹）
// 的火候/品質判定讀取﹐stuff_ob 以 supplement_stat/heal_stat 調整屬性。
//
// 疲勞 (fatigue) 是研讀技藝 (feature/study.c) 累積的倦怠 stat﹐以
// consume_stat 削減其 current 即「解疲勞」（fatigue 在本 mudlib 未設上限﹐
// 削減恆安全）。
//
// 配方（見 cmds/std/refine.c）：當歸×1 + 枸杞×1 + 辰砂×1﹐技能門檻
// alchemy-medication 35。

inherit COMBINED_ITEM;

void create()
{
	set_name("養心丹", ({"relax pill", "relax", "pill"}));
	if( !clonep() ) {
		set("unit", "些");
		set("long",
			"養心丹是方家養心安神、補益精元的丹藥﹐以當歸、枸杞合辰砂之\n"
			"性煉成。操勞過度、精疲力竭之時服下一粒﹐能補回耗損的精元﹐\n"
			"並紓解久勞積下的疲憊﹐使人心神安泰﹐精力復振。\n");
		set("base_unit", "粒");
		set("base_value", 480);
		set("base_weight", 5);
		set("mixture_value", 120);
		set("produce_param", ([
			"min_heat_power" : 100,
			"max_heat_power" : 200,
			"min_heat" : 300,
			"max_heat" : 360,
		]));
		set("requirement", ([
			"literate" : 12,
			"alchemy-medication" : 35,
		]));
	}
	set_amount(1);
	setup();
}

int stuff_ob(object me)
{
	if( me->query_stat_maximum("food") - me->query_stat("food") < 8 )
		return notify_fail("你的肚子已經撐得連這粒藥丸也吞不下去了。\n");
	message_vision("$N吞下一粒養心丹﹐只覺心神一鬆﹐周身的疲憊漸漸退去。\n", me);
	me->consume_stat("water", 10);
	me->supplement_stat("food", 5);
	me->heal_stat("gin", 25);
	me->supplement_stat("gin", 30);
	me->consume_stat("fatigue", 30);
	add_amount(-1);

	return 1;
}
// vim: set ts=4 sw=4 syntax=lpc
