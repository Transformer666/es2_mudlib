// Room: /d/road/road3.c

inherit ROOM;

void create()
{
	set("short", "官道");
	set("long", @LONG
這裡是一處十字路口，路邊豎著一根高大的木製指路牌，上面用墨
字標示著各個方向的去處。往北通往振武軍營，往東是前往五堂鎮的官
道，往南則可以回到雪亭鎮的方向。來往的行人商旅在此歇腳辨認方向
，地面被踩得格外平整。
LONG
	);
	set("outdoors", "road");
	set("exits", ([
		"south" : __DIR__"road2",
		"northwest" : "/d/zhenwu/gate",
		"east"  : __DIR__"crossroad",
		"west"  : "/d/green/entrance",
	]));

	setup();
	replace_program(ROOM);
}
