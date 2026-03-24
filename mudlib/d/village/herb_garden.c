// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "草藥園");
	set("long", @LONG
土地廟南面有一小片草藥園﹐用低矮的竹籬圍著。園中種著金銀
花、當歸、黃芪等常見藥材﹐空氣中瀰漫著淡淡的藥草清香。一
位老婦人正蹲在田間除草﹐身旁放著一個竹編的藥簍。這些草藥
是村裡人治病的主要來源。
LONG
	);
	set("outdoors", "wilderness");
	set("objects", ([
		__DIR__"npc/herbalist" : 1,
	]));
	set("exits", ([
		"north" : __DIR__"temple",
	]));

	setup();
	replace_program(ROOM);
}
