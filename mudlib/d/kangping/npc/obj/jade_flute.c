// vim: syntax=lpc
// Quest item: anlan_test (安懶道人的考驗)

inherit ITEM;

void create()
{
	set_name("玉笛", ({"jade flute", "flute", "jade_flute"}));
	set_weight(200);
	if( !clonep() ) {
		set("unit", "支");
		set("value", 500);
		set("long",
			"一支翠綠色的玉笛﹐通體瑩潤如水﹐做工極為精細。笛身上刻\n"
			"著幾朵梅花﹐線條流暢自然﹐隱隱散發著一股清幽的香氣。看起\n"
			"來是一件有些年頭的物件。\n");
	}
	setup();
}
