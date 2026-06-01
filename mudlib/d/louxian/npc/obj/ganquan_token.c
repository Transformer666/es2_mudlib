// ganquan_token.c -- 婁縣非戰鬥支線「甘泉茶會」的酬謝信物：
//                    甘泉客棧掌櫃謝玩家替他張羅成那一席甘泉好茶、相贈的一面
//                    「甘泉」竹牌。持此牌的是客棧記著的座上嘉賓﹐圖個彩頭與情分。
//                    純風味物件﹐不堪戰﹐亦不開啟任何折扣或功能（避免動到店家既有
//                    買賣邏輯﹐純作彩頭氣氛）。

inherit ITEM;

void create()
{
	set_name("甘泉竹牌", ({ "ganquan charm", "bamboo charm", "ganquanpai" }) );
	set_weight(30);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "面");
		set("value", 20);
		set("long",
			"一面打磨光潤的小竹牌﹐繫著一根青絨繩﹐正面以烙鐵燙著\n"
			"「甘泉」二字﹐背面刻著一口小小的六角古井與一縷裊裊的茶\n"
			"煙。這是甘泉客棧記給座上嘉賓的彩頭信物﹐掌櫃說﹐持牌的\n"
			"都是客棧念著的貴客﹐來日打婁縣經過﹐儘管進店歇腳吃茶﹐\n"
			"圖個甘泉潤客的好意頭。牌子小巧﹐佩在身上﹐隱隱沾著一縷\n"
			"清茶的香氣。\n");
		set("no_sell", 1);
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
