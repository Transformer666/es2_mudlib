// maro.c - 棉襖 (padded cotton coat)

#include <armor.h>

inherit F_CLOTH;

void create()
{
	set_name("棉襖", ({"maro", "cotton coat", "padded coat", "coat"}));
	set_weight(2000);
	setup_cloth();

	if( !clonep() ) {
		set("unit", "件");
		set("value", 800);
		set("long",
			"一件厚實的棉襖﹐用粗棉布縫製而成﹐裡面填著厚厚的棉花﹐\n"
			"雖然樣式簡樸﹐但穿起來十分暖和﹐是寒冬裡不可或缺的保暖衣物。\n");
		set("wear_as", "cloth");
		set("apply_armor/cloth", ([
			"armor": 2,
		]));
	}
	setup();
}
