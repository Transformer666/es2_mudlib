// boar_tusk.c - 野豬獠牙（任務證物）

inherit ITEM;

void create()
{
	set_name("野豬獠牙", ({"boar tusk", "tusk"}));
	set_weight(300);
	if( !clonep() ) {
		set("unit", "根");
		set("value", 50);
		set("long",
			"一根粗大的野豬獠牙﹐足有一尺來長﹐尖端鋒利無比。獠牙\n"
			"上還沾著些泥土和血跡﹐可以作為除害的證據。\n");
	}
	setup();
}
