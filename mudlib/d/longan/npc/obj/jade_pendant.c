// vim: syntax=lpc
// jade_pendant.c - 玉佩 (quest item for storyteller_pendant quest)

inherit ITEM;

void create()
{
	set_name("舊玉佩", ({"jade pendant", "pendant", "jade_pendant"}));
	set_weight(200);
	if( !clonep() ) {
		set("unit", "枚");
		set("value", 500);
		set("long",
			"一枚古舊的玉佩﹐雕工精緻﹐正面刻著一個「韓」字﹐背面\n"
			"則是一柄小劍的圖案。玉質溫潤﹐但表面有不少磨損的痕跡﹐\n"
			"看得出年代久遠。\n");
	}
	setup();
}
