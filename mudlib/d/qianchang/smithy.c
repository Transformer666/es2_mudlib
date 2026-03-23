// Room: /d/qianchang/smithy.c

inherit ROOM;

void create()
{
	set("short", "鐵匠鋪");
	set("long", @LONG
一間煙火氣十足的小鐵匠鋪，爐中炭火通紅，不時迸出幾點火星。
一座沉重的鐵砧擺在屋子中央，牆上掛滿了各式鉗子、錘子和火鉗。
角落裡堆著些打好的鋤頭、鐮刀和菜刀，都是鄉間常用的農具。空
氣中瀰漫著鐵銹和煤煙的味道。
LONG
	);
	set("objects", ([
		__DIR__"npc/blacksmith" : 1,
	]));
	set("exits", ([
		"north" : __DIR__"street2",
	]));

	setup();
	replace_program(ROOM);
}
