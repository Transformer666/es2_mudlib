// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "草原溪邊");
	set("long", @LONG
一條清澈的小溪在草原中蜿蜒流淌，溪邊長著各種野花和蘆葦。溪水發出潺潺的聲響，幾隻蜻蜓在水面上飛舞。順著溪流往東走，可以看到一個天然形成的小水潭。
LONG
	);
	set("outdoors", "wilderness");
	set("exits", ([
		"west" : __DIR__"grassland_n",
		"east" : __DIR__"pond",
	]));

	setup();
	replace_program(ROOM);
}
