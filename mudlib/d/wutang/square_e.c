// Room: /d/wutang/square_e.c

inherit ROOM;

void create()
{
	set("short", "廣場東邊");
	set("long", @LONG
這裡是五堂鎮廣場的東邊﹐一個擺滿各式符籙護身符的攤位佔據了
路邊的大半空間﹐攤主正賣力地向過往的行人推銷自家的辟邪之物。往
西可以回到廣場中央﹐東邊穿過一段短街就是鎮子的東門﹐南邊則是一
條通往大街的路。
LONG
	);
	set("objects", ([
		__DIR__"npc/shen" : 1,
	]));
	set("exits", ([
		"west" : __DIR__"square",
		"east" : __DIR__"egate",
		"south" : __DIR__"street1",
	]));

	setup();
	replace_program(ROOM);
}
