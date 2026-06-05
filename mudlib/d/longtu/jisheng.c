// Room: /d/longtu/jisheng.c -- 濟生藥鋪
//
// 出處﹕docs/02-遊戲系統與機制/06-煉丹與書本系統.md 煉丹流程 L57
//   「2. 去濟生藥鋪找藥鋪掌櫃 buy mixture for minor heal pill   # 92兩50文/份」。
//   煉丹正規流程須先向藥鋪掌櫃購得「藥引（mixture）」﹐方能塞入丹鼎、入爐起火結丹。
//   原雪亭鎮已有一間「順生堂」小藥鋪(d/snow/herb_shop﹐賣成藥)﹐此「濟生藥鋪」係
//   另一間﹐專營方士煉丹所需的藥引﹐故獨立設室、不奪順生堂既有之物。
//
// 入既有房﹕本室掛在龍圖丹派山門(d/longtu/gate)之東——山門本就西北通雪亭鎮廣場、
//   北上丹院丹房﹐藥鋪設於山門旁﹐方士買了藥引便可北上丹房 refine﹐動線最順。
//   gate.c 用 plain set("exits")(無 replace_program)﹐故僅安全補一道 east 出口﹐
//   不動其餘設定。
//
// 掌櫃 NPC 由 npc/jisheng 提供(本批次另檔)﹐以 set("objects") 入室。

inherit ROOM;

void create()
{
	set("short", "濟生藥鋪");
	set("long", @LONG
這是一間開在龍圖丹派山門旁的藥鋪﹐門楣上懸著一方「濟生」舊
匾。鋪子不大﹐三面牆都立著頂天的藥櫃﹐密密麻麻的小抽屜貼著籤
條﹐當歸、黃耆、辰砂、雄黃之屬一應俱全。靠裡一張烏木長櫃後立著
位掌櫃﹐櫃上擺著戥子、藥碾與一摞紙包﹐專替上山煉丹的方士秤配各
色藥引(mixture)。藥香混著紙墨氣息在鋪中瀰漫﹐往西便是龍圖丹派
的山門。
LONG
	);
	set("detail", ([
		"藥櫃" : "三面頂天的藥櫃上百個小抽屜分裝著各色藥材﹐每格皆貼著
工整的籤條﹐取用便捷。
",
		"匾額" : "門楣上「濟生」二字漆色已舊﹐筆勢卻仍見渾厚﹐道盡這藥
鋪濟世活人的本分。
",
		"藥引" : "掌櫃替方士秤配的「藥引(mixture)」﹐是按丹方配伍、研末
紙包的半成藥料。買回後塞入丹鼎入爐起火﹐方能結成丹藥。
你可向掌櫃 buy mixture for <丹方> 購得(如 buy mixture for minor heal pill)。
",
		"戥子" : "櫃上一桿小巧的戥子﹐專秤金石細料﹐分毫不差﹐是配藥引
時論斤兩的傢伙。
",
	]));
	set("objects", ([
		__DIR__"npc/jisheng" : 1,
	]));
	set("outdoors", "snow");
	set("exits", ([
		"west" : __DIR__"gate",
	]));

	setup();
}
// vim: set ts=4 sw=4 syntax=lpc
