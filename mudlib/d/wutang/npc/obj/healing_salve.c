// vim: syntax=lpc
// healing_salve.c - 海大夫任務獎勵：金創藥

inherit COMBINED_ITEM;
inherit F_FOOD;

void create()
{
	set_name("金創藥", ({"healing salve", "salve", "medicine"}));
	if( !clonep() ) {
		set("unit", "包");
		set("base_unit", "份");
		set("base_value", 800);
		set("base_weight", 100);
		set("food_stuff", 300);
		set("long",
			"用上等草藥精心調配的金創藥﹐散發著濃郁的藥草香氣。據說\n"
			"是一位隱世名醫的祖傳秘方﹐對外傷療效極佳。\n");
	}
	setup();
}
