// writing_case.c -- 文國縣非戰鬥支線「天風筆會」的回報信物（配齊的文房）：
//                   一隻筆墨俱備的天風筆匣。墨工把老筆匠安了新筆的空匣接過，揀一
//                   錠最得意的松煙好墨配進匣中，湊成筆墨相稱、可登大雅之堂的一副
//                   文房，封好匣蓋交還玩家，囑其速速持回天風客棧交與掌櫃。
//
// 用途：純為支線回報信物（quest/wenguo_brush），不堪戰、不能賣、不能偷。
//       由 d/wenguo/npc/inkmaker.c 在玩家持空筆匣來配墨後交付（同時銷除空匣）﹐
//       交還 d/wenguo/npc/keeper.c 領賞。送件進度記在玩家身上的旗標﹐
//       本物件只作憑證﹐自身不記狀態。

inherit ITEM;

void create()
{
	set_name("文房筆匣", ({ "writing case", "full case", "wenfang case" }) );
	set_weight(500);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "隻");
		set("value", 1);
		set("long",
			"一隻筆墨俱備的天風筆匣﹐匣蓋上烙著小小的「天風」二字。\n"
			"揭開來﹐軟綢襯著一管新紮的天風狼毫﹐旁邊安著一錠描金的\n"
			"松煙好墨﹐筆鋒尖圓﹐墨身烏亮﹐筆墨相稱﹐湊成了一副可登\n"
			"大雅之堂的文房。湊近一聞﹐隱隱透著一股清苦中帶幽香的松\n"
			"煙墨氣。\n"
			"該把它持回天風客棧交與掌櫃﹕ask keeper about 文房，或 give writing case to keeper。\n");
		set("no_sell", 1);
		set("no_steal", 1);
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
