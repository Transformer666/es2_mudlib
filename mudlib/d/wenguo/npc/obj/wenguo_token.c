// wenguo_token.c -- 文國縣非戰鬥支線「天風筆會」的酬謝信物：
//                   天風客棧掌櫃謝玩家替他備齊文房雅禮、相贈的一面「天風」竹牌。
//                   持此牌的是客棧記著的嘉賓﹐圖個彩頭與情分。純風味物件﹐
//                   不堪戰﹐亦不開啟任何折扣或功能（避免動到店家既有買賣邏輯﹐
//                   純作彩頭氣氛）。

inherit ITEM;

void create()
{
	set_name("天風竹牌", ({ "wenguo token", "tianfeng token", "bamboo token" }) );
	set_weight(30);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "面");
		set("value", 20);
		set("long",
			"一面打磨光潤的小竹牌﹐繫著一根青絨繩﹐正面以烙鐵燙著\n"
			"「天風」二字﹐背面刻著一管小小的筆與一錠墨。這是天風客\n"
			"棧記給嘉賓的彩頭信物﹐掌櫃說﹐持牌的都是客棧記著的雅\n"
			"客﹐來日打文國縣經過﹐儘管進店歇腳吃茶﹐圖個天風送遠的\n"
			"好意頭。牌子小巧﹐佩在身上﹐沾著文國的墨香。\n");
		set("no_sell", 1);
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
