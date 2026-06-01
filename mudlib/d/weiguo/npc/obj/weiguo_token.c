// weiguo_token.c -- 衛國鎮非戰鬥支線「鎮關炒米茶」的酬謝信物：
//                   衛國客棧掌櫃謝玩家替他和成鎮關炒米茶、相贈的一面「衛國」木牌。
//                   持此牌的是客棧記著的嘉賓﹐圖個彩頭與情分。純風味物件﹐
//                   不堪戰﹐亦不開啟任何折扣或功能（避免動到店家既有買賣邏輯﹐
//                   純作彩頭氣氛）。

inherit ITEM;

void create()
{
	set_name("衛國木牌", ({ "weiguo token", "wooden token", "weiguopai" }) );
	set_weight(30);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "面");
		set("value", 20);
		set("long",
			"一面棗木刻的小牌﹐繫著一根結實的麻繩﹐正面以剛硬的隸\n"
			"書刻著「衛國」二字﹐筆意與鎮門石匾如出一轍﹔背面淺刻著一\n"
			"座關門與一桿軍旗。牌子是拿鎮門那株老棗樹的木料刻的﹐繫在\n"
			"身上﹐隱隱透著一縷棗木的清香。這是衛國客棧記給嘉賓的彩頭\n"
			"信物﹐掌櫃說﹐持牌的都是客棧記著的貴客﹐來日打衛國鎮經過﹐\n"
			"儘管進店歇腳吃茶﹐圖個賓至如歸的好意頭。\n");
		set("no_sell", 1);
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
