// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "峽谷入口");
	set("long", @LONG
兩面高聳的岩壁在此收攏，形成一條幽深的峽谷。谷口處風聲呼嘯，地上散落著從山壁上崩落的碎石。一條窄窄的小路蜿蜒通往峽谷深處，路旁偶爾可見被水流沖刷出的奇異石紋。
LONG
	);
	set("outdoors", "wilderness");
	set("exits", ([
		"west" : "/d/road/mountain_road1",
		"east" : __DIR__"narrow_pass",
	]));

	setup();
	replace_program(ROOM);
}
