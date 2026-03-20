// white_robe.c - 老乞婆任務獎勵：白長袍

#include <armor.h>

inherit F_CLOTH;

void create()
{
	set_name("白長袍", ({"white robe", "white long robe", "robe"}));
	set_weight(1200);
	setup_cloth();

	if( !clonep() ) {
		set("unit", "件");
		set("value", 3000);
		set("long",
			"一件潔白如雪的長袍﹐布料柔軟細膩﹐穿在身上輕盈舒適。袍子\n"
			"的衣領和袖口繡著淡淡的雲紋﹐在陽光下隱隱泛著銀色的光澤﹐\n"
			"顯然不是凡品。\n");
		set("wear_as", "cloth");
		set("apply_armor/cloth", ([
			"armor": 4,
		]));
	}
	setup();
}
