// Room: /d/graveyard/grave3.c

inherit ROOM;

void create()
{
	set("short", "亂葬崗深處");
	set("long", @LONG
亂葬崗的最深處﹐四周的墳塚更加密集﹐有些墳墓已經被掘開﹐露
出裡面漆黑的棺木。夜風呼嘯而過﹐帶起一陣陣嗚咽似的聲音﹐不知
是風聲還是鬼哭。遠處有一座破舊的小廟﹐半隱在枯樹叢中。
LONG
	);
	set("outdoors", "wasteland");
	set("objects", ([
		__DIR__"npc/zombie" : 1,
	]));
	set("exits", ([
		"south" : __DIR__"grave2",
		"west" : __DIR__"shrine",
	]));

	setup();
	replace_program(ROOM);
}
