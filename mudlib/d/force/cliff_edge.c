// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "練功崖");
	set("long", @LONG
這是一處面對深谷的懸崖邊緣，崖下是萬丈深淵，風從谷底呼嘯而上。在這種險要之地練功，需要極大的定力和膽量。崖邊的岩石上留有許多深深的掌印和腳印，都是歷代武者練功留下的痕跡。
LONG
	);
	set("outdoors", "wilderness");
	set("exits", ([
		"west" : __DIR__"arena",
		"down" : __DIR__"waterfall",
	]));

	setup();
	replace_program(ROOM);
}
