// vim: syntax=lpc

#include <weapon.h>

inherit F_STAFF;

void create()
{
	set_name("竹竿", ({"bamboo_pole", "pole"}));
	set_weight(2000);
	setup_staff(1, 15, 100, 0);

	if( !clonep() ) {
		set("wield_as", ({"staff", "twohanded staff"}));
		set("unit", "根");
		set("value", 50);
		set("rigidity", 8);
		set("long",
			"一根又長又直的青竹竿﹐既可以當釣竿用﹐也可以在危急時\n"
			"當作武器防身。竹節光滑﹐握在手裡很是順手。\n");
	}
	setup();
}
