// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "神殿內殿");
	set("long", @LONG
內殿是神殿中最為神聖的所在，只有經過允許的人才能進入。殿內光線幽暗，牆壁上鑲嵌著各種寶石，在微弱的燭光中閃爍著神秘的光芒。殿中央有一座古老的石台，上面刻著複雜的符文和陣法圖案。
LONG
	);
	set("no_fight", 1);
	set("exits", ([
		"south" : __DIR__"main_hall",
	]));

	setup();
	replace_program(ROOM);
}
