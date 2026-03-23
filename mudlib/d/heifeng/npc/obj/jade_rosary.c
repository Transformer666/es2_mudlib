// jade_rosary.c — 玉念珠（石佛遺物任務獎勵）

inherit ITEM;

void create()
{
	set_name("玉念珠", ({"jade_rosary", "jade rosary", "rosary"}));
	set_weight(200);
	if( !clonep() ) {
		set("unit", "串");
		set("value", 2500);
		set("long",
			"一串溫潤的玉念珠﹐共有十八顆﹐每一顆都散發著柔和的光澤。\n"
			"珠子上隱約刻著細小的梵文﹐握在手中令人心神寧靜。似乎是某\n"
			"位高僧在此修行時留下的遺物。\n");
	}
	setup();
}
