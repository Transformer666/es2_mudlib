// lijia_token.c -- 李家村非戰鬥支線「李家祭祖供果」的酬謝信物：
//                  李家族長謝玩家替合族備齊祭祖供盤、自神龕前討來相贈的一道「李氏香火福符」。
//                  持此符的是李氏宗祠記著的善客﹐圖個沾先祖香火的福分與情分。純風味物件﹐
//                  不堪戰﹐亦不開啟任何折扣或功能（不動任何買賣或機制邏輯﹐純作彩頭氣氛）。
//
// id 註記：查找專用獨有 id「lijiafushu」﹐另掛通名 id「lijia token」「charm」便於辨識。

inherit ITEM;

void create()
{
	set_name("李氏香火福符", ({ "lijiafushu", "lijia token", "charm" }) );
	set_weight(20);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "道");
		set("value", 20);
		set("long",
			"一道黃箋朱筆寫就的小福符﹐摺得方正﹐繫著一縷紅線﹐是\n"
			"李氏宗祠祭祖時在神龕前供過、沾了合族香火的。符面拿朱砂寫\n"
			"著「李氏宗親、福蔭子孫」幾字﹐邊角還留著一點祠堂老桂的清\n"
			"香。族長說﹐持這道福符的﹐都是替李家先祖盡過一份心的善\n"
			"客﹐來日打李家村經過﹐合村李姓都記著這份情分。\n");
		set("no_sell", 1);
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
