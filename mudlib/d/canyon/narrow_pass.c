// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "峽谷窄道");
	set("long", @LONG
峽谷在此變得極為狹窄，兩面岩壁幾乎要觸碰在一起，僅容一人側身通過。頭頂只能看到一線天空，谷底十分陰暗。腳下的石頭被水流磨得光滑，走起來需要格外小心。
LONG
	);
	set("outdoors", "wilderness");
	set("exits", ([
		"west" : __DIR__"entrance",
		"east" : __DIR__"bridge",
	]));

	setup();
	replace_program(ROOM);
}
