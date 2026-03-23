// golden_scale.c — 金鯉鱗片（金鯉任務獎勵）

inherit ITEM;

void create()
{
	set_name("金鯉鱗片", ({"golden_scale", "scale", "golden scale"}));
	set_weight(50);
	if( !clonep() ) {
		set("unit", "片");
		set("value", 800);
		set("long",
			"一片金光閃閃的魚鱗﹐比尋常魚鱗大了數倍﹐泛著溫潤的光\n"
			"澤。據說鯉君渡的金鯉是上古靈物﹐牠的鱗片能帶來好運。\n");
	}
	setup();
}
