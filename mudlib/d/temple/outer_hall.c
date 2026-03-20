// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "神殿外殿");
	set("long", @LONG
穿過山門，便是神殿的外殿。外殿寬敞而莊嚴，地面鋪著光滑的大理石，兩旁矗立著數根雕龍石柱。殿中擺放著幾張供桌，上面放著鮮花和供品。牆壁上繪著各種神話故事的壁畫，色彩鮮艷，栩栩如生。
LONG
	);
	set("objects", ([
		__DIR__"npc/temple_guard" : 2,
	]));
	set("exits", ([
		"south" : __DIR__"entrance",
		"north" : __DIR__"main_hall",
		"east" : __DIR__"bell_tower",
	]));

	setup();
	replace_program(ROOM);
}
