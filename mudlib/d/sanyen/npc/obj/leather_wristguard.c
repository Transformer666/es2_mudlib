// leather_wristguard.c - 三掩乞丐任務獎勵：皮護腕

#include <armor.h>

inherit F_WRIST_EQ;

void create()
{
	set_name("皮護腕", ({"leather wristguard", "wristguard"}));
	set_weight(400);
	setup_wrist_eq();

	if( !clonep() ) {
		set("unit", "只");
		set("value", 1500);
		set("long",
			"一只用牛皮縫製的護腕﹐雖然有些陳舊﹐但皮質依然堅韌結實。\n"
			"護腕內側刻著幾個小字﹐似乎是前任主人的名字。\n");
		set("wear_as", "wrist_eq");
		set("apply_armor/wrist_eq", ([
			"armor": 3,
		]));
	}
	setup();
}
