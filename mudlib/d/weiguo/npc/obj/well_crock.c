// well_crock.c -- 衛國鎮非戰鬥支線「鎮關炒米茶」的盛水信物（瓦罐盛了古井甜水）：
//                 一隻粗瓦燒的小罐﹐是古井亭守井老叟絞水的家什。老叟見玩家受
//                 衛國客棧掌櫃之託來備鎮關炒米茶﹐便絞了一罐鎮口老古井的甜水交與
//                 玩家﹐囑其持往炒米坊尋炒米師傅沖茶。
//
// 用途：純為支線送件信物（quest/weiguo_tea），不堪戰、不能賣、不能偷。
//       由 d/weiguo/npc/welltender.c 在玩家接了任務後交付﹐持往
//       d/weiguo/npc/roaster.c 和茶（和茶時此罐銷除、改交和好的 tea_crock）。
//       送件進度記在玩家身上的旗標﹐本物件只作憑證﹐自身不記狀態。

inherit ITEM;

void create()
{
	set_name("井亭瓦罐", ({ "well crock", "crock", "jingtingwaguan" }) );
	set_weight(500);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "隻");
		set("value", 1);
		set("long",
			"一隻粗瓦燒的小罐﹐罐口拿一片箬葉虛掩著﹐罐身還沁著沁\n"
			"涼的水珠﹐原是古井亭守井老叟絞水的家什。罐裡盛著一罐剛絞\n"
			"上來的鎮口古井甜水﹐清冽回甘﹐正好拿去沖一罐鎮關炒米茶。\n"
			"該拿它到炒米坊尋炒米師傅和茶﹕ask roaster about 炒米茶﹐或 give well crock to roaster。\n");
		set("no_sell", 1);
		set("no_steal", 1);
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
