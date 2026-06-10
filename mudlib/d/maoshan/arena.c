// Room: /d/maoshan/arena.c

inherit ROOM;

void create()
{
	set("short", "演法場");
	set("long", @LONG
這是茅山派弟子演練咒術的演法場﹐一片青石廣場上以白灰畫著一
座九宮法陣﹐陣眼處埋著一方刻滿符文的鎮陣石。場邊立著數具草人﹐
胸口貼著黃紙符咒﹐供弟子試演幽冥三箭之類的咒術。時有弟子立於陣
中﹐掐訣念咒﹐指尖隱隱透出幽冥之氣﹐射向草人﹐黃符應聲而焦。往
東可回到庭院。
LONG
	);
	set("detail", ([
		"法陣" : "青石地上以白灰畫成的九宮法陣按洛書之數排布﹐陣中演法可
借天地之力放大咒術的威能。
",
		"鎮陣石" : "陣眼處的鎮陣石以青石鑿成﹐通體刻滿幽冥符文﹐隱隱透著一
股陰寒之氣。
",
		"草人" : "場邊的草人束以稻草﹐胸口貼著黃符﹐專供弟子試演咒術之用﹐
被幽冥之氣擊中處皆已焦黑。
",
	]));
	set("outdoors", "snow");
	// 沒有設 no_fight，可在此 kill 草人試咒練功（沿用 /d/snow/drill.c 範式）。
	set("objects", ([
		__DIR__"npc/dummy" : 1,
	]));
	set("exits", ([
		"east" : __DIR__"yard",
	]));

	setup();
}
// vim: set ts=4 sw=4 syntax=lpc
