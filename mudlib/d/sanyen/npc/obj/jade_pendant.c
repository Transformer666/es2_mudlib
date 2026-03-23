// jade_pendant.c - 三掩乞丐任務道具：玉佩

#include <armor.h>

inherit F_NECK_EQ;

void create()
{
	set_name("玉佩", ({"jade pendant", "pendant", "jade"}));
	set_weight(300);
	setup_neck_eq();

	if( !clonep() ) {
		set("unit", "塊");
		set("value", 500);
		set("long",
			"一塊沾滿泥垢的玉佩﹐拭去塵土後可以看到玉質溫潤﹐上面\n"
			"刻著一個「沈」字。這似乎是某個家族的傳家之物。\n");
		set("wear_as", "neck_eq");
		set("apply_armor/neck_eq", ([
			"armor": 1,
		]));
	}
	setup();
}
