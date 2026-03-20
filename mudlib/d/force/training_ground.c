// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "練武場");
	set("long", @LONG
這是一片平坦的空地，地面被踩踏得十分結實。空地四周插著幾根木樁，上面佈滿了刀砍斧劈的痕跡。場邊擺放著各種兵器架和石鎖，看來這裡經常有人在此練功。北面是一個擂台，東面有一處安靜的冥想之所。
LONG
	);
	set("outdoors", "wilderness");
	set("objects", ([
		__DIR__"npc/training_dummy" : 3,
	]));
	set("exits", ([
		"south" : __DIR__"entrance",
		"north" : __DIR__"arena",
		"east" : __DIR__"meditation",
	]));

	setup();
	replace_program(ROOM);
}
