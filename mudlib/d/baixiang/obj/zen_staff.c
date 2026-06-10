// zen_staff.c -- 禪杖，白象寺演武場供僧人練杖的演武兵刃。
// 結構沿用 /d/snow/npc/obj/cane.c（F_STAFF）；value 壓低防 farm。

#include <weapon.h>

inherit F_STAFF;

void create()
{
	set_name("禪杖", ({ "zen staff", "staff", "chanzhang" }) );
	set_weight(9000);
	setup_staff(1, 15, 80, 0);

	if( !clonep() ) {
		set("wield_as", ({ "staff", "twohanded staff" }) );
		set("unit", "根");
		set("value", 300);
		set("rigidity", 15);
		set("long",
			"一根演武用的鐵木禪杖﹐通體烏沉﹐杖頭套著數枚銅環﹐揮動\n"
			"時叮噹輕響﹐杖身被歷代武僧的手心磨得油亮。\n");
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
