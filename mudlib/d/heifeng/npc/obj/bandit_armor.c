// bandit_armor.c

#include <armor.h>

inherit F_ARMOR;

void create()
{
	set_name("匪甲", ({"bandit_armor", "armor"}));
	set_weight(8000);
	setup_armor();

	if( !clonep() ) {
		set("unit", "件");
		set("value", 600);
		set("long",
			"一件粗製的皮甲﹐上面釘著幾塊鐵片﹐雖然做工粗糙﹐但多\n"
			"少能擋住一些刀劍。甲上佈滿了刀痕和血漬﹐不知經歷過多少次\n"
			"廝殺。\n");
		set("wear_as", "armor");
		set("apply_armor/armor", ([
			"armor" : 3,
		]));
	}
	setup();
}
