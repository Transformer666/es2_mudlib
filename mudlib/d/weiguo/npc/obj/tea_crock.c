// tea_crock.c -- 衛國鎮非戰鬥支線「鎮關炒米茶」的回報信物（和好的炒米茶罐）：
//                一隻和好了鎮關炒米茶的粗瓦罐。炒米師傅把守井老叟交與玩家的
//                井亭瓦罐接過﹐拿新焙的炒米沖了古井甜水﹐封好罐口交還玩家﹐囑其
//                速速持回衛國客棧交與掌櫃﹐好教掌櫃以這碗鄉味送行那位遠行的舊識。
//
// 用途：純為支線回報信物（quest/weiguo_tea），不堪戰、不能賣、不能偷。
//       由 d/weiguo/npc/roaster.c 在玩家持井亭瓦罐來和茶後交付（同時銷除空罐）﹐
//       交還 d/weiguo/npc/keeper.c 領賞。送件進度記在玩家身上的旗標﹐
//       本物件只作憑證﹐自身不記狀態。

inherit ITEM;

void create()
{
	set_name("鎮關炒米茶", ({ "tea crock", "rice tea", "zhenguanchaomicha" }) );
	set_weight(550);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "隻");
		set("value", 1);
		set("long",
			"一隻封好了口的粗瓦罐﹐罐口拿一片箬葉嚴嚴地紮著﹐罐身\n"
			"還溫溫的。湊近一聞﹐古井甜水的清冽裡透著炒米焙得金黃的焦\n"
			"香﹐正是炒米師傅拿新焙的炒米沖了鎮口古井的甜水和成的「鎮\n"
			"關炒米茶」﹐焦香頂飢、回甘解乏。炒米師傅說﹐這碗茶是衛國\n"
			"邊地送遠待客的鄉味﹐當年屯軍出關﹐喝的就是這一口。\n"
			"該把它持回衛國客棧交與掌櫃﹕ask keeper about 炒米茶﹐或 give tea crock to keeper。\n");
		set("no_sell", 1);
		set("no_steal", 1);
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
