// Room: /d/baixiang/arena.c

inherit ROOM;

void create()
{
	set("short", "演武場");
	set("long", @LONG
這是白象寺羅漢一脈演練武功的演武場﹐一片寬闊的青石廣場上立
著一排木人樁﹐供僧人錘鍊杖法拳腳。場心一座青石台上斜插著數根禪
杖﹐杖頭的銅環在風中叮噹輕響。場邊一道粉牆上繪著羅漢降魔的壁畫
﹐筆勢雄渾﹐時有灰衣武僧赤膊掄杖﹐杖風虎虎﹐喝聲震天。場角石碑
上刻著金剛伏魔杖法的招式口訣。往東可回到庭院。
LONG
	);
	set("detail", ([
		"木人樁" : "一排木人樁以硬木製成﹐樁身遍佈凹痕﹐想是僧人日復一日捶
打所致。
",
		"禪杖" : "青石台上斜插的禪杖通體烏沉﹐杖頭套著數枚銅環﹐既是法器﹐
亦是羅漢降魔的兵刃。
",
		"壁畫" : "粉牆上的壁畫繪著羅漢降龍伏虎之態﹐筆勢雄渾﹐隱隱透著一股
金剛伏魔的氣勢。
",
		"石碑" : "石碑上刻著金剛伏魔杖法的招式口訣﹐字句精微﹐須得勤加參詳
演練方能領會。
",
	]));
	set("outdoors", "snow");
	// 沒有設 no_fight，可在此 kill 木人樁練功（沿用 /d/snow/drill.c 範式）；
	// 禪杖供取用練杖，reset 時 std/room.c 會自動補齊缺失的 clone。
	set("objects", ([
		__DIR__"npc/dummy" : 1,
		__DIR__"obj/zen_staff" : 1,
	]));
	set("exits", ([
		"east" : __DIR__"yard",
	]));

	setup();
}
// vim: set ts=4 sw=4 syntax=lpc
