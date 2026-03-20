// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "羊山谷底");
	set("long", @LONG
這是懸崖下方的一處幽深谷底，陽光幾乎照不到這裡，四周都是高聳的岩壁。谷底長滿了蕨類植物和苔蘚，空氣潮濕而陰冷。一條細流從岩壁上滲出，匯聚成一個小水窪。
LONG
	);
	set("exits", ([
		"up" : __DIR__"cliff",
	]));

	setup();
	replace_program(ROOM);
}
