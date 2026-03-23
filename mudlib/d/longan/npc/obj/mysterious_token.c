// vim: syntax=lpc
// Quest item: beggar_clue (龍安乞丐的消息)

inherit ITEM;

void create()
{
	set_name("神秘玉牌", ({"mysterious token", "token", "jade token", "mysterious_token"}));
	set_weight(100);
	if( !clonep() ) {
		set("unit", "塊");
		set("value", 300);
		set("long",
			"一塊拇指大小的玉牌﹐質地溫潤﹐正面刻著一個古樸的「安」\n"
			"字﹐背面是一朵蓮花圖案。玉牌邊緣略有磨損﹐看起來頗有些\n"
			"年代了。\n");
	}
	setup();
}
