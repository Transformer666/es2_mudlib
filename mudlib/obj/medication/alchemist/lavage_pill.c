// lavage_pill.c -- 清腹丹：方家清食化滯的丹藥﹐回補「食」(food) 與「水」(water)。
//
// 比照 obj/medication/alchemist/aquapill.c（金液丹）：COMBINED_ITEM﹐
// set("requirement"/"mixture_value"/"produce_param") 供 refine（煉丹）
// 的火候/品質判定讀取﹐stuff_ob 以 supplement_stat 調整屬性。
//
// 此丹一反多數丹藥「消耗食水換取精氣神」之性：它本身潤腹生津、開胃化滯﹐
// 服之同時回補食與水﹐解滯脹之苦﹐故吞服前不檢查胃納。
//
// 配方（見 cmds/std/refine.c）：枸杞×1 + 當歸×1﹐技能門檻 alchemy-medication 10。

inherit COMBINED_ITEM;

void create()
{
	set_name("清腹丹", ({"lavage pill", "lavage", "pill"}));
	if( !clonep() ) {
		set("unit", "些");
		set("long",
			"清腹丹是方家清食化滯、潤腹生津的丹藥﹐以枸杞、當歸炮製而成﹐\n"
			"入口微酸回甘。行旅斷糧、腹中滯脹之時含服一粒﹐能解一時的飢渴\n"
			"滯悶﹐使腸胃通暢、津液復生﹐是行走江湖隨身應急的丹藥。\n");
		set("base_unit", "粒");
		set("base_value", 140);
		set("base_weight", 5);
		set("mixture_value", 40);
		set("produce_param", ([
			"min_heat_power" : 70,
			"max_heat_power" : 180,
			"min_heat" : 120,
			"max_heat" : 160,
		]));
		set("requirement", ([
			"literate" : 5,
			"alchemy-medication" : 10,
		]));
	}
	set_amount(1);
	setup();
}

int stuff_ob(object me)
{
	message_vision("$N吞下一粒清腹丹﹐只覺腹中一陣清涼通暢﹐飢渴滯悶為之一解。\n", me);
	me->supplement_stat("food", 30);
	me->supplement_stat("water", 30);
	add_amount(-1);

	return 1;
}
// vim: set ts=4 sw=4 syntax=lpc
