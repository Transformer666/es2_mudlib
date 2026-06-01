// wenfang_pen.c -- 羅城非戰鬥支線「羅城客棧的尋硯」的酬謝信物：
//                  羅城客棧掌櫃謝玩家替客棧了結了遺硯失物這樁臉面事、相贈的
//                  一枝客棧備著饋客的湖筆。純風味物件﹐不堪戰﹐亦不開啟任何
//                  功能（不改任何屬性、不作兵器﹐純作彩頭氣氛）。

inherit ITEM;

void create()
{
	set_name("湖筆", ({ "wenfang pen", "writing brush", "hubi" }) );
	set_weight(20);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "枝");
		set("value", 30);
		set("long",
			"一枝做工精緻的湖筆﹐斑竹的筆桿溫潤﹐羊毫的筆鋒挺括飽\n"
			"滿﹐筆桿上以泥金細細刻著「羅城客棧」四個小字。這是羅城\n"
			"客棧備著饋贈相熟貴客的彩頭物事﹐掌櫃謝你替客棧了結了那\n"
			"樁遺硯失物的臉面事﹐特特取一枝相贈。筆雖尋常﹐這份心意\n"
			"卻是難得﹐佩在身上﹐倒也添幾分書卷的雅氣。\n");
		set("no_sell", 1);
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
