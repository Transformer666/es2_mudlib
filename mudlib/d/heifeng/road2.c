// Room: /d/heifeng/road2.c

inherit ROOM;

void create()
{
	set("short", "山腳小路");
	set("long", @LONG
官道在這裡分成兩條岔路。一條往北蜿蜒上山﹐通往一處山寨的方
向﹐遠遠便能看到山上飄著一面黑色大旗﹐上面繡著「黑風」二字。另
一條往南通往焱硝村。路旁有一尊石佛像﹐半埋在草叢中。
LONG
	);
	set("outdoors", "road");
	set("exits", ([
		"west" : __DIR__"road1",
		"north" : __DIR__"gate",
		"south" : "/d/sanyen/ngate",
		"east" : __DIR__"buddha",
	]));

	setup();
	replace_program(ROOM);
}
