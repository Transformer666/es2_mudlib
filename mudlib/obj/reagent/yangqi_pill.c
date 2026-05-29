// yangqi_pill.c -- 養氣丹，龍圖丹派以 refine（煉丹）指令煉成的療傷丹藥。
//
// 比照 obj/medication/alchemist/aquapill.c（金液丹）的 stuff_ob：吞服後
// 恢復精氣神並補回少許形體 (HP)。本丹刻意做得簡單、安全──不掛
// produce_param / requirement / mixture_value 那套完整生產系統，只是
// refine.c 消耗藥材後 new() 出來的成品。
//
// 服用機制全比照現有丹藥：eat.c 會呼叫 stuff_ob(me)，其中以
// supplement_stat / heal_stat / consume_stat 調整屬性（見
// feature/statistic.c 確認）。

inherit COMBINED_ITEM;

void create()
{
	set_name("養氣丹", ({ "yangqi pill", "yangqi", "pill" }));
	if( !clonep() ) {
		set("unit", "些");
		set("long",
			"養氣丹是龍圖丹派入門的療傷丹藥﹐以靈芝、當歸入丹爐文火慢\n"
			"煉而成。藥丸呈深褐色﹐入口先苦後甘﹐服之可調養氣血、補益\n"
			"精神﹐並癒合些許外傷﹐是丹派弟子初窺丹道時最先學會煉製的\n"
			"丹藥。\n");
		set("base_unit", "粒");
		set("base_value", 300);
		set("base_weight", 5);
	}
	set_amount(1);
	setup();
}

int stuff_ob(object me)
{
	if( me->query_stat_maximum("food") - me->query_stat("food") < 8 )
		return notify_fail("你的肚子已經撐得連這粒藥丸也吞不下去了。\n");
	message_vision("$N吞下一粒養氣丹﹐只覺一股暖流自丹田緩緩散開。\n", me);
	me->consume_stat("water", 10);
	me->supplement_stat("food", 5);
	me->heal_stat("kee", 20);
	me->supplement_stat("kee", 25);
	me->supplement_stat("gin", 15);
	me->supplement_stat("sen", 10);
	add_amount(-1);

	return 1;
}
// vim: set ts=4 sw=4 syntax=lpc
