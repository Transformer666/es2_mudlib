// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "白骨荒原");
	set("long", @LONG
這是一片令人毛骨悚然的荒原，地面上鋪滿了白森森的骸骨，堆積如山。骨堆中不時傳出咔嚓咔嚓的聲響，似乎有什麼東西在骨堆中蠕動。天空是一片暗紅色，沒有太陽也沒有月亮，一切都籠罩在一種令人窒息的壓抑之中。
LONG
	);
	set("objects", ([
		__DIR__"npc/skeleton_guard" : 2,
	]));
	set("outdoors", "wilderness");
	set("exits", ([
		"south" : __DIR__"dark_path",
		"north" : __DIR__"throne",
	]));

	setup();
	replace_program(ROOM);
}
