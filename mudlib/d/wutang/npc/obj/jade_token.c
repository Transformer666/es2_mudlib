// jade_token.c - 鎮天神廟任務獎勵：真天玉牌

#include <armor.h>

inherit F_NECK_EQ;

void create()
{
    set_name("真天玉牌", ({"jade token", "jade", "token"}));
    set_weight(300);
    setup_neck_eq();

    if( !clonep() ) {
	set("unit", "塊");
	set("value", 3000);
	set("long",
	    "一塊溫潤的白玉牌﹐正面刻著「真天」二字﹐背面刻著一個古老\n"
	    "的八卦圖案。玉牌散發著淡淡的光澤﹐握在手中微微發暖﹐似乎\n"
	    "蘊含著某種力量。\n");
	set("wear_as", "neck_eq");
	set("apply_armor/neck_eq", ([
	    "armor": 3,
	]));
    }
    setup();
}
