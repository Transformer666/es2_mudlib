// ziyan_token.c -- 紫煙鎮非戰鬥支線「安神香湯」的酬謝信物：
//                  紫煙小棧掌櫃謝玩家替他和成安神香湯、相贈的一面「紫煙」香牌。
//                  持此牌的是客棧記著的嘉賓﹐圖個彩頭與情分。純風味物件﹐
//                  不堪戰﹐亦不開啟任何折扣或功能（避免動到店家既有買賣邏輯﹐
//                  純作彩頭氣氛）。

inherit ITEM;

void create()
{
	set_name("紫煙香牌", ({ "ziyan token", "incense token", "ziyanpai" }) );
	set_weight(30);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "面");
		set("value", 20);
		set("long",
			"一面溫潤的紫泥小牌﹐繫著一根紫絨繩﹐正面以細篆印著\n"
			"「紫煙」二字﹐背面浮雕著一縷裊裊的香煙與一彎溫泉。牌子\n"
			"似是拿和香的香泥摻著沉香末壓製陰乾的﹐貼身佩著﹐隱隱透\n"
			"著一縷安神的沉香。這是紫煙小棧記給嘉賓的彩頭信物﹐掌櫃\n"
			"說﹐持牌的都是客棧記著的貴客﹐來日打紫煙鎮經過﹐儘管進\n"
			"店泡湯吃茶﹐圖個賓至如歸的好意頭。\n");
		set("no_sell", 1);
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
