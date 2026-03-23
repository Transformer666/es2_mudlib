// phoenix_feather.c — 鸂鷘彩羽（鸂鷘任務獎勵）

inherit ITEM;

void create()
{
	set_name("鸂鷘彩羽", ({"phoenix_feather", "feather", "phoenix feather"}));
	set_weight(30);
	if( !clonep() ) {
		set("unit", "根");
		set("value", 1200);
		set("long",
			"一根絢麗奪目的羽毛﹐在光線下折射出七彩虹光﹐散發著淡淡\n"
			"的靈氣。傳說鸂鷘是上古風鳥的後裔﹐牠的羽毛能驅邪辟穢。\n");
	}
	setup();
}
