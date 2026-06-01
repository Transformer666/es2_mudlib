// kangping_token.c -- 康平村非戰鬥支線「康平新米飯糰」的酬謝信物：
//                     康平小店店家謝玩家替他蒸成新米飯糰、相贈的一面「康平」竹牌。
//                     持此牌的是小店記著的嘉賓﹐圖個彩頭與情分。純風味物件﹐
//                     不堪戰﹐亦不開啟任何折扣或功能（避免動到店家既有買賣邏輯﹐
//                     純作彩頭氣氛）。

inherit ITEM;

void create()
{
	set_name("康平竹牌", ({ "kangping token", "bamboo token", "kangpingpai" }) );
	set_weight(30);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "面");
		set("value", 20);
		set("long",
			"一面青竹劈削、打磨光滑的小牌﹐繫著一根細麻繩﹐正面拿\n"
			"墨筆寫著「康平」二字﹐筆意與村口那塊舊木牌一般無二﹔背面\n"
			"淺刻著一束飽滿的稻穗。牌子是拿村頭老竹的料削的﹐繫在身\n"
			"上﹐隱隱透著一縷青竹的清香。這是康平小店記給嘉賓的彩頭信\n"
			"物﹐店家說﹐持牌的都是小店記著的貴客﹐來日打康平村經過﹐\n"
			"儘管進店歇腳吃飯﹐圖個身康家平的好意頭。\n");
		set("no_sell", 1);
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
