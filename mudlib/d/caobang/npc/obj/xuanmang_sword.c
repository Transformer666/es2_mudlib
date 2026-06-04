// xuanmang_sword.c -- 漕幫信物兼利器「旋芒」(sword)。
//
// 來歷（承接 canon：docs 01-世界觀與劇情/05-主線任務與NPC.md L113
//   「宋安江 @ 吏部尚書府漕幫禮堂分舵主 → 給旋芒」）：
//   旋芒是漕幫壓箱底的一門功夫，亦是這門功夫所附的一柄信物兵刃。其勁路脫胎
//   自跑船人撐篙、收纜、破浪的水上工夫——使將開來，劍身在腕底盤旋成一片
//   寒芒，如水面上一圈圈盪開的旋光，故名「旋芒」。禮堂分舵主宋安江掌京畿漕
//   幫幫務，見有緣的少俠，便將這柄旋芒相贈，既是漕幫的信物，也是一柄趁手的
//   兵刃，盼它在江湖風波裡護持少俠周全。
//
// 用法：持(wield xuanmang / wield sword)於手即可禦敵。
//   設 no_sell：宋安江一片仗義相贈、又是漕幫的信物，玩家當留著自用，不宜變賣。
//
// 設計（鏡 d/snow/npc/obj/silversword.c 之 setup_sword 四參式、量級略高）：
//   旋芒乃漕幫信物兵刃，定位在「趁手利器」而非神兵，故量級從中——較雪亭鎮的
//   洗銀劍(setup_sword(2,15,40,4))為利，遠不及頂裝玄霜劍(setup_sword(5,20,150,10))
//   之神兵級。setup_sword(x,y,z,r) 依 feature/weapon/sword.c 展開：
//     sword(單手)      = init_damage(x,    y,      z,    r)
//     secondhand sword = init_damage(x,    y/2,    z,    r)
//     twohanded sword  = init_damage(x,    y*3/2,  z*4/3,r)
//   取 setup_sword(3, 18, 65, 5)：單手 乘數3 range18 bonus65 roll5——一柄趁手而
//   不逾矩的中階利劍，與其漕幫信物的定位相稱。

#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
	set_name(HIC "旋芒" NOR, ({ "xuanmang", "xuanmang sword", "旋芒", "sword" }) );
	set_weight(6800);
	setup_sword(3, 18, 65, 5);

	if( !clonep() ) {
		set("wield_as", ({ "sword" }) );
		set("unit", "把");
		set("value", 1);
		set("no_sell", 1);
		set("rigidity", 42);
		set("long",
			"這柄喚作『旋芒』的長劍，是漕幫壓箱底那門水上工夫所附的信物兵\n"
			"刃。劍身狹長而略帶弧勢，泛著一層水波似的青白光暈，劍脊上一道\n"
			"道細密的紋路盤旋而上，宛若漕船破浪時在水面盪開的一圈圈旋光，\n"
			"『旋芒』之名便由此而來。握在手中入手沉穩，劍勢一展，腕底便似\n"
			"有撐篙收纜的綿綿勁力盤旋不絕——這是漕幫數十萬跑船人，自大運河\n"
			"的風浪裡一篙一纜磨出來的勁路，使將開來，劍光在身周旋成一片寒\n"
			"芒，最是綿密難當。劍柄上纏著揉得極韌的青絲，絲尾墜著一枚小小\n"
			"的銅錨——那是漕幫的記認。\n");
		set("wield_msg",
			HIC "$N腕底一沉，那柄旋芒已亮在手中，劍身水波似的青芒一閃，"
			"劍勢盤旋如水上旋光！\n" NOR);
		set("unwield_msg", "$N收劍歸鞘，那一身盤旋的寒芒方才斂去。\n");
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
