// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "月神祭壇");
	set("long", @LONG
遺跡深處有一座保存相對完好的圓形祭壇，祭壇由白色大理石砌成，中央刻著一個巨大的月亮圖案。祭壇周圍立著八根石柱，每根柱上都刻著不同的月相圖案。一股神秘的力量似乎在此處流轉，讓人不由自主地肅然起敬。
LONG
	);
	set("no_fight", 1);
	set("objects", ([
		__DIR__"npc/moon_priestess" : 1,
	]));
	set("exits", ([
		"west" : __DIR__"ruins",
	]));

	setup();
	replace_program(ROOM);
}
