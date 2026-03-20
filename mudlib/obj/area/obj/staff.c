// staff.c

#include <weapon.h>

inherit F_STAFF;

void create()
{
	set_name("木棍", ({ "staff", "wooden staff" }));
	set_weight(5000);
	setup_staff(1, 12, 3, 4);

	if( !clonep() ) {
		set("wield_as", ({ "staff" }));
		set("unit", "根");
		set("value", 800);
		set("rigidity", 20);
		set("long", "一根普通的木棍，雖然樸實無華，卻也結實耐用。\n");
	}
	setup();
}

void varify_template(object owner)
{
	int i = owner->query_level();

	ENHANCE_D->enhance_weapon(this_object(), i*i + 10, "棍");
}
