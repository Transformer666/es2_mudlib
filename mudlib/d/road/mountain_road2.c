// Room: /d/road/mountain_road2.c

inherit ROOM;

void create()
{
	set("short", "山路");
	set("long", @LONG
一條蜿蜒曲折的山路穿過茂密的樹林，林間光線昏暗，偶爾有幾
縷陽光從枝葉的縫隙中灑落。從東邊隱隱傳來陣陣誦經聲，那是百象
寺的方向。路旁的樹幹上繫著紅布條，似乎是信徒們留下的祈福之物。
LONG
	);
	set("outdoors", "road");
	set("exits", ([
		"south" : __DIR__"crossroad",
		"east" : "/d/baixiang/gate",
		"west" : "/d/tianyue/mountain_path",
	]));

	setup();
	replace_program(ROOM);
}
