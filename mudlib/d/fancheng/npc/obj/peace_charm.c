// peace_charm.c -- 檒城非戰鬥支線「望安港的斷龍骨」的酬謝信物：
//                  望安港船戶世代供奉、求個「出海望平安」的平安符。
//                  船屋老人謝玩家奔走張羅龍骨木料﹐自貼身處摘下這道隨他
//                  討了大半輩子海的舊平安符相贈。純風味物件，不堪戰。

inherit ITEM;

void create()
{
	set_name("望安平安符", ({ "peace charm", "charm", "fuping" }) );
	set_weight(20);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "道");
		set("value", 30);
		set("long",
			"一道望安港船戶供奉求平安的舊平安符。黃綾為底﹐上頭以硃\n"
			"砂描著辟邪鎮潮的符文與一尾蜷曲的水神﹐外裹一層浸了桐油\n"
			"的油布防潮﹐邊角已被海風與汗手磨得起了毛。這符隨那老船\n"
			"匠在風浪裡討了大半輩子海﹐他說討海人信的就是這個——出\n"
			"海望平安﹐平平安安回得家來﹐便是天大的福分了。佩在身上\n"
			"﹐圖個心安。\n");
		set("no_sell", 1);
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
