// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "冥王座");
	set("long", @LONG
這裡是死亡領域的核心，一座巨大的黑色石椅矗立在高台之上，石椅上刻滿了古老的死亡符文。石椅前方是一片開闊的空地，地面上用暗紅色的線條畫著一個巨大的魔法陣。空氣中充斥著強烈的死亡氣息，讓人感到一陣陣的暈眩。
LONG
	);
	set("objects", ([
		__DIR__"npc/soul_judge" : 1,
	]));
	set("exits", ([
		"south" : __DIR__"bone_field",
		"east" : __DIR__"abyss",
	]));

	setup();
	replace_program(ROOM);
}
