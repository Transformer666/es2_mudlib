// jade_tablet.c - 李家村任務道具：傳家玉牌

#include <armor.h>

inherit F_WAIST_EQ;

void create()
{
	set_name("傳家玉牌", ({"jade tablet", "tablet", "jade"}));
	set_weight(400);
	setup_waist_eq();

	if( !clonep() ) {
		set("unit", "塊");
		set("value", 800);
		set("long",
			"一塊精緻的白玉牌﹐正面刻著「李氏傳家」四個篆字﹐背面\n"
			"刻著幾行小字﹐記載著李家先祖的訓誡。玉質溫潤細膩﹐顯然\n"
			"是一件有年頭的老物件。\n");
		set("wear_as", "waist_eq");
		set("apply_armor/waist_eq", ([
			"armor": 2,
		]));
	}
	setup();
}
