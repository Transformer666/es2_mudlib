// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "峽谷崖壁");
	set("long", @LONG
這裡是峽谷深處的一面巨大崖壁，岩壁上佈滿了各種奇形怪狀的鐘乳石和石筍。崖壁的裂縫中長出幾棵頑強的小樹，在風中瑟瑟發抖。南面的岩壁上有一處可以落腳的岩棚。
LONG
	);
	set("outdoors", "wilderness");
	set("exits", ([
		"west" : __DIR__"bridge",
		"south" : __DIR__"ledge",
	]));

	setup();
	replace_program(ROOM);
}
