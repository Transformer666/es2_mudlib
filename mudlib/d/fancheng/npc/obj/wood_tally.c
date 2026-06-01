// wood_tally.c -- 檒城非戰鬥支線「望安港的斷龍骨」的信物：
//                 衛兵統領劉開親筆畫押、加蓋「勇」字火印的領料木牌。
//                 港城的好龍骨木料素由官中統一調撥﹐憑此木牌方能往老松林
//                 一帶的料場支領一截堪作船骨的好松木﹐以修葺擱在塢裡那艘
//                 折了主桅的渡海大船。須交到望安港船塢的船屋老人手上。
//
// 用途：純為支線送件信物（quest/fancheng_sea），不堪戰、不能賣。
//       由 d/fancheng/npc/captain.c 交付﹐交還 d/fancheng/npc/boatman.c 領賞。

inherit ITEM;

void create()
{
	set_name("領料木牌", ({ "wood tally", "tally", "mupai" }) );
	set_weight(120);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "面");
		set("value", 1);
		set("long",
			"一面巴掌大小的硬木牌子﹐打磨得溜光﹐繫著一根褪色的紅絨\n"
			"繩。牌面以刀刻著「望安港料場 領龍骨一」幾個字﹐填了黑漆\n"
			"﹐字口已被摩挲得發亮﹔牌角烙著一方「勇」字的火印﹐正是\n"
			"檒城衛兵所的記認。背面有衛兵統領劉開的親筆畫押。\n"
			"憑這面木牌﹐便能往老松林一帶的官料場﹐支領一截堪作船骨\n"
			"的筆直好松木。劉統領吩咐過﹐領了料﹐記得把這牌子交還望\n"
			"安港船塢的船屋老人﹐由他驗看下料。\n");
		set("no_sell", 1);
		set("no_steal", 1);
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
