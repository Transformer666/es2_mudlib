// abao_keepsake.c -- 半舊的青布手帕（「阿寶的心願」支線信物）
//
// 瞎眼老太婆貼身收著的一方舊手帕，角上以細線繡著一個歪歪扭扭的「寶」字
// ——那是她當年替孫女阿寶縫的。婆婆把它交給玩家，要玩家拿去給樹上的阿寶
// 看，好讓阿寶知道：婆婆已放下尋仇的執念，只盼她回家。
//
// 此物為「阿寶的心願」(quest/snow_abao) 支線信物，id 為 abao_keepsake，
// 與雪亭鎮既有的紅木梳子(annatto comb)、破布(__ID_CHALLIE__) 等 try/fon
// 任務物件【互不相干】，不會與封山入派那條舊任務鏈相混。
//
// value=0：純劇情信物，不值錢、不可賣個好價，避免玩家當廢品賣掉而卡關
//（弄丟了可再 ask gammer about 信物 向婆婆討一方）。

inherit ITEM;

void create()
{
	set_name("青布手帕", ({ "abao keepsake", "keepsake", "handkerchief" }));
	set_weight(20);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "方");
		set("value", 0);
		set("long",
			"一方半舊的青布手帕﹐邊角已被摩挲得起了毛邊。手帕的一角用\n"
			"褪了色的紅線繡著一個歪歪扭扭的「寶」字﹐針腳生澀﹐想是出自\n"
			"一雙不甚靈巧的手。布上還隱隱透著一股淡淡的、說不清是藥香還\n"
			"是體己的氣味﹐教人聞著心頭發暖。\n");
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
