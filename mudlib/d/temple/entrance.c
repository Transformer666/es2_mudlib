// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "神殿山門");
	set("long", @LONG
一座宏偉的石制山門矗立在眼前，門楣上刻著「天道神殿」四個金色大字，兩旁各立著一尊石獅。山門前的石階足有數十級，兩側種著蒼翠的松柏。門內隱約可見金碧輝煌的建築，香火的氣息從裡面飄出。
LONG
	);
	set("outdoors", "wilderness");
	set("exits", ([
		"south" : "/d/road/road5",
		"north" : __DIR__"outer_hall",
	]));

	setup();
	replace_program(ROOM);
}
