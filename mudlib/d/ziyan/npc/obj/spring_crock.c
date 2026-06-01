// spring_crock.c -- 紫煙鎮非戰鬥支線「安神香湯」的盛湯信物（空罐盛了溫泉水）：
//                   一隻紫泥燒的小陶罐，是紫煙溫泉燒湯老叟司爐汲水的家什。
//                   老叟見玩家受紫煙小棧掌櫃之託來備安神香湯，便汲了一罐最新鮮的
//                   紫煙溫泉水交與玩家，囑其持往沉香小亭尋焙香師和香。
//
// 用途：純為支線送件信物（quest/ziyan_incense），不堪戰、不能賣、不能偷。
//       由 d/ziyan/npc/springman.c 在玩家接了任務後交付﹐持往
//       d/ziyan/npc/incenseman.c 和香（和香時此罐銷除、改交和好的 incense_crock）。
//       送件進度記在玩家身上的旗標﹐本物件只作憑證﹐自身不記狀態。

inherit ITEM;

void create()
{
	set_name("溫泉陶罐", ({ "spring crock", "crock", "wenquantaoguan" }) );
	set_weight(500);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "隻");
		set("value", 1);
		set("long",
			"一隻紫泥燒的小陶罐﹐罐口拿一片荷葉虛掩著﹐罐身還凝著\n"
			"溫溫的水汽﹐原是紫煙溫泉燒湯老叟司爐汲水的家什。罐裡盛著\n"
			"一罐新汲的紫煙溫泉水﹐溫熱清澈﹐隱隱透著一絲礦泉的氣味﹐\n"
			"正好拿去和一罐安神的香湯。\n"
			"該拿它到沉香小亭尋焙香師和香﹕ask incenseman about 香湯﹐或 give spring crock to incenseman。\n");
		set("no_sell", 1);
		set("no_steal", 1);
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
