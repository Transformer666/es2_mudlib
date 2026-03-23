// vim: syntax=lpc
// 封山劍法殘譜 - fengshan_lost_manual quest item

inherit ITEM;

void create()
{
	set_name("封山劍法殘譜", ({"sword scroll", "scroll", "sword_scroll"}));
	set_weight(200);

	if( !clonep() ) {
		set("unit", "卷");
		set("value", 500);
		set("long",
			"一卷泛黃的竹簡﹐上面以蠅頭小字記載著精妙的劍招圖解﹐\n"
			"字跡雖然因為風雨侵蝕而略有模糊﹐但仍然可以辨認。竹簡\n"
			"的邊角有些破損﹐看來已經在崖壁上經歷了不少風吹雨打。\n");
	}
	setup();
}
