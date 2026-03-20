// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "溫泉池");
	set("long", @LONG
一個天然形成的溫泉池嵌在岩石之間，泉水清澈見底，不斷冒著細小的氣泡。池邊的岩石被溫泉水長年沖刷，變得光滑圓潤。池水溫度恰到好處，據說有舒筋活血、治療傷病的功效。
LONG
	);
	set("objects", ([
		__DIR__"npc/pilgrim" : 1,
	]));
	set("outdoors", "wilderness");
	set("exits", ([
		"south" : __DIR__"spring_path",
		"north" : __DIR__"pool",
	]));

	setup();
	replace_program(ROOM);
}
