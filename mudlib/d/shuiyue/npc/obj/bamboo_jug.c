// bamboo_jug.c -- 水月村非戰鬥支線「福安客棧的清泉」的盛泉信物（空筒）：
//                 一節剖口打磨過的粗竹筒，是水月瀑布崖下採藥老叟隨身盛水的家什。
//                 老叟見玩家受福安客棧掌櫃之託來尋清泉的源頭，便把這空竹筒交與
//                 玩家，囑其下浣月潭尋釣叟，到那疏通好的泉眼盛一筒甜泉回去。
//
// 用途：純為支線送件信物（quest/shuiyue_spring），不堪戰、不能賣、不能偷。
//       由 d/shuiyue/npc/herbman.c 在玩家接了任務後交付﹐持往
//       d/shuiyue/npc/angler.c 盛泉（盛泉時此空筒銷除、改交盛滿的 spring_jug）。
//       送件進度記在玩家身上的旗標﹐本物件只作憑證﹐自身不記狀態。

inherit ITEM;

void create()
{
	set_name("空竹筒", ({ "bamboo jug", "empty jug", "kongzhutong" }) );
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "節");
		set("value", 1);
		set("long",
			"一節剖口打磨過的粗竹筒﹐繫著一根麻繩好背在肩上﹐筒身\n"
			"被水氣與手澤養得油潤﹐原是水月瀑布崖下那採藥老叟隨身盛\n"
			"水的家什。如今空著﹐正好拿去盛一筒清泉。\n"
			"該拿它到浣月潭尋釣叟﹐盛一筒瀑後泉眼的甜泉﹕ask angler about 清泉﹐或 give bamboo jug to angler。\n");
		set("no_sell", 1);
		set("no_steal", 1);
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
