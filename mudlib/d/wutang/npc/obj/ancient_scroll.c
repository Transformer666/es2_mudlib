// ancient_scroll.c - 巫山雕像任務獎勵：真天秘卷

#include <armor.h>

inherit F_HAND_EQ;

void create()
{
    set_name("真天秘卷", ({"ancient scroll", "scroll"}));
    set_weight(500);
    setup_hand_eq();

    if( !clonep() ) {
	set("unit", "卷");
	set("value", 5000);
	set("long",
	    "一卷泛黃的古老卷軸﹐用上好的絲綢裝裱﹐散發著淡淡的檀香。\n"
	    "卷上以古體小楷密密麻麻地記載著真天教的秘史﹐以及巫山封印\n"
	    "的來龍去脈。字跡雖已年代久遠﹐卻依然清晰可辨。\n");
	set("wear_as", "hand_eq");
	set("apply_armor/hand_eq", ([
	    "armor": 2,
	]));
    }
    setup();
}
