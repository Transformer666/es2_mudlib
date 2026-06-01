// tea_caddy.c -- 婁縣非戰鬥支線「甘泉茶會」的送件信物（空罐）：
//                一隻封了新摘「甘泉雀舌」嫩茶的小錫罐。甘泉園的老圃見玩家受
//                甘泉客棧掌櫃之託來辦茶會，便摘了一撮園裡最好的雀舌新芽，封進
//                這隻錫罐交與玩家，囑其下甘泉井畔尋守井老叟，注一罐井裡的甘泉
//                活水進去，方好回客棧烹那一席甘泉好茶。
//
// 用途：純為支線送件信物（quest/louxian_spring），不堪戰、不能賣、不能偷。
//       由 d/louxian/npc/gardener.c 在玩家接了任務後交付﹐持往
//       d/louxian/npc/welltender.c 注水（注水時此空罐銷除、改交盛滿的 spring_caddy）。
//       送件進度記在玩家身上的旗標﹐本物件只作憑證﹐自身不記狀態。

inherit ITEM;

void create()
{
	set_name("茶罐", ({ "tea caddy", "empty caddy", "chaguan" }) );
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "隻");
		set("value", 1);
		set("long",
			"一隻巴掌大的小錫罐﹐罐身擦得錚亮﹐蓋口拿一圈油紙仔細\n"
			"封著。揭開來一聞﹐裡頭是一撮剛從甘泉園茶圃摘下的「甘泉\n"
			"雀舌」嫩茶﹐形如雀舌﹐清香撲鼻。老圃說﹐有了好茶﹐還得\n"
			"配上一罐井裡的甘泉活水﹐方烹得出那一席好茶。\n"
			"該拿它到甘泉井畔尋守井老叟﹐注一罐甘泉﹕ask welltender about 甘泉﹐或 give tea caddy to welltender。\n");
		set("no_sell", 1);
		set("no_steal", 1);
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
