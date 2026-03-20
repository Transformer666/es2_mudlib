// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "望月亭");
	set("long", @LONG
一座六角涼亭建在山谷的高處，亭中掛著一盞長明燈，在月色中搖曳。從亭中向外望去，整個山谷的景色盡收眼底，月光如水般灑在萬物之上。亭柱上刻著一副對聯：「月照千山明如晝，風吹萬里靜無聲。」
LONG
	);
	set("outdoors", "wilderness");
	set("exits", ([
		"south" : __DIR__"moonlight_path",
		"north" : __DIR__"ruins",
	]));

	setup();
	replace_program(ROOM);
}
