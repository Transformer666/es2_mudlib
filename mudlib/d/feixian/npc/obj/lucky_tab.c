// lucky_tab.c -- 斐縣非戰鬥支線「悅客來的散帳」的酬謝信物：
//                 悅客來客棧掌櫃謝玩家替他核齊散帳、相贈的一面「常來」竹牌。
//                 持此牌的是客棧記down的熟客﹐圖個彩頭與情分。純風味物件﹐
//                 不堪戰﹐亦不開啟任何折扣或功能（避免動到店家既有買賣邏輯﹐
//                 純作彩頭氣氛）。

inherit ITEM;

void create()
{
	set_name("常來竹牌", ({ "lucky tab", "bamboo tab", "changlai" }) );
	set_weight(30);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "面");
		set("value", 20);
		set("long",
			"一面打磨光潤的小竹牌﹐繫著一根紅絨繩﹐正面以烙鐵燙著\n"
			"「悅客來」三字﹐背面一個圓潤的「常來」二字。這是悅客來\n"
			"客棧記給熟客的彩頭信物﹐掌櫃說﹐持牌的都是客棧記著的\n"
			"老主顧﹐來日打斐縣經過﹐儘管進店歇腳吃茶﹐圖個情分。\n"
			"牌子小巧﹐佩在身上﹐倒也添個喜氣。\n");
		set("no_sell", 1);
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
