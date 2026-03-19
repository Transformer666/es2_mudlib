// Room: /d/baihua/garden.c

inherit ROOM;

void create()
{
	set("short", "小花園");
	set("long", @LONG
一座精心打理的小花園﹐用竹籬笆圍成一圈。園中種植著各種名貴
花卉﹐按顏色和種類分成幾個花圃﹐中間有一條碎石小徑供人行走。園
中立著一座小巧的涼亭﹐亭中擺著一張石桌和幾個石凳。往南是一片
瓜田。
LONG
	);
	set("exits", ([
		"east" : __DIR__"street",
		"south" : __DIR__"melon_farm",
	]));

	setup();
	replace_program(ROOM);
}
