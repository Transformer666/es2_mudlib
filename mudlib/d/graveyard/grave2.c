// Room: /d/graveyard/grave2.c

inherit ROOM;

void create()
{
	set("short", "亂葬崗");
	set("long", @LONG
這裡是真正的亂葬崗了﹐地面上到處是裸露的白骨和破碎的棺木。
空氣中瀰漫著一股令人作嘔的腐臭味﹐地上的泥土呈現出不正常的暗
紅色。幾縷綠色的磷火在墳塚之間飄忽不定﹐忽明忽暗﹐像是亡者不
安的靈魂。
LONG
	);
	set("outdoors", "wasteland");
	set("objects", ([
		__DIR__"npc/ghost" : 1,
		__DIR__"npc/zombie" : 1,
	]));
	set("exits", ([
		"south" : __DIR__"grave1",
		"north" : __DIR__"grave3",
		"east" : __DIR__"tomb",
	]));

	setup();
	replace_program(ROOM);
}
