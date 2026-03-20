// Room: /d/baihua/street.c

inherit ROOM;

void create()
{
	set("short", "花村小徑");
	set("long", @LONG
碎石鋪成的小徑在村子裡蜿蜒前行﹐路旁每隔幾步就種著一叢花﹐
有薔薇、牡丹、茉莉、桂花﹐爭奇鬥艷。一個賣花姑娘挎著花籃坐在
路邊﹐笑盈盈地向行人招手。往西有一座小花園﹐往南是一片湖邊。
LONG
	);
	set("objects", ([
		__DIR__"npc/flowergirl" : 1,
		__DIR__"npc/student" : 1,
	]));
	set("exits", ([
		"north" : __DIR__"square",
		"south" : __DIR__"lake",
		"west" : __DIR__"garden",
	]));

	setup();
	replace_program(ROOM);
}
