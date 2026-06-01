// fuan_charm.c -- 水月村非戰鬥支線「福安客棧的清泉」的酬謝信物：
//                 福安客棧掌櫃謝玩家替他尋回清泉、相贈的一面「福安」竹牌。
//                 持此牌的是客棧記著的熟客﹐圖個彩頭與情分。純風味物件﹐
//                 不堪戰﹐亦不開啟任何折扣或功能（避免動到店家既有買賣邏輯﹐
//                 純作彩頭氣氛）。

inherit ITEM;

void create()
{
	set_name("福安竹牌", ({ "fuan charm", "bamboo charm", "fuanpai" }) );
	set_weight(30);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "面");
		set("value", 20);
		set("long",
			"一面打磨光潤的小竹牌﹐繫著一根青絨繩﹐正面以烙鐵燙著\n"
			"「福安」二字﹐背面刻著一彎小小的水月與一道飛瀑。這是福\n"
			"安客棧記給熟客的彩頭信物﹐掌櫃說﹐持牌的都是客棧記著的\n"
			"老主顧﹐來日打水月村經過﹐儘管進店歇腳吃茶﹐圖個福壽安\n"
			"康的好意頭。牌子小巧﹐佩在身上﹐沾著水月的清氣。\n");
		set("no_sell", 1);
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
