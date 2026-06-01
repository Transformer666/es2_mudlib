// spring_caddy.c -- 婁縣非戰鬥支線「甘泉茶會」的回報信物（滿罐）：
//                   一隻茶、水俱備的茶罐。守井老叟把老圃交與玩家的茶罐接過，
//                   到甘泉井裡汲了滿滿一注清冽的甘泉活水注進去，封好罐口交還
//                   玩家，囑其速速持回甘泉客棧交與掌櫃，好教掌櫃烹那一席甘泉
//                   好茶，待那遠來的貴客。
//
// 用途：純為支線回報信物（quest/louxian_spring），不堪戰、不能賣、不能偷。
//       由 d/louxian/npc/welltender.c 在玩家持茶罐來注水後交付（同時銷除空茶罐）﹐
//       交還 d/louxian/npc/keeper.c 領賞。送件進度記在玩家身上的旗標﹐
//       本物件只作憑證﹐自身不記狀態。

inherit ITEM;

void create()
{
	set_name("甘泉茶罐", ({ "spring caddy", "full caddy", "ganquanchaguan" }) );
	set_weight(600);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "隻");
		set("value", 1);
		set("long",
			"一隻茶、水俱備的小錫罐﹐沉甸甸的﹐蓋口拿油紙與細繩封\n"
			"得嚴實﹐罐身沁出涼涼的水珠。裡頭是甘泉園新摘的雀舌嫩\n"
			"茶﹐並一注守井老叟才從井裡汲的清冽甘泉。守井老叟說﹐這\n"
			"茶配這水﹐是天造地設的一對﹐烹出來的茶湯清甘無比。\n"
			"該把它持回甘泉客棧交與掌櫃﹕ask keeper about 甘泉﹐或 give spring caddy to keeper。\n");
		set("no_sell", 1);
		set("no_steal", 1);
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
