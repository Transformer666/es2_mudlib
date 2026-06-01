// incense_crock.c -- 紫煙鎮非戰鬥支線「安神香湯」的回報信物（和好的香湯罐）：
//                    一隻和好了安神香湯的紫泥陶罐。焙香師把燒湯老叟交與玩家的
//                    溫泉陶罐接過，調入新焙的沉香細末，封好罐口交還玩家，囑其速速
//                    持回紫煙小棧交與掌櫃，好教掌櫃以此香湯款待那位遠來的貴客。
//
// 用途：純為支線回報信物（quest/ziyan_incense），不堪戰、不能賣、不能偷。
//       由 d/ziyan/npc/incenseman.c 在玩家持溫泉陶罐來和香後交付（同時銷除空罐）﹐
//       交還 d/ziyan/npc/keeper.c 領賞。送件進度記在玩家身上的旗標﹐
//       本物件只作憑證﹐自身不記狀態。

inherit ITEM;

void create()
{
	set_name("安神香湯罐", ({ "incense crock", "soup crock", "anshenxiangtang" }) );
	set_weight(550);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "隻");
		set("value", 1);
		set("long",
			"一隻封好了口的紫泥陶罐﹐罐口拿一片荷葉嚴嚴地紮著﹐罐\n"
			"身溫溫的。湊近一聞﹐溫泉的礦氣裡融著一縷清甜醇雅的沉香﹐\n"
			"正是焙香師拿新汲的紫煙溫泉水﹐調進新焙的沉香細末和成的\n"
			"「安神香湯」﹐聞之令人神思俱定。焙香師說﹐這香湯既可溫\n"
			"飲﹐亦可傾入湯池泡浴﹐最是安神解乏。\n"
			"該把它持回紫煙小棧交與掌櫃﹕ask keeper about 香湯﹐或 give incense crock to keeper。\n");
		set("no_sell", 1);
		set("no_steal", 1);
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
