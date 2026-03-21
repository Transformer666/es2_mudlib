// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "羊山山頂");
	set("long", @LONG
站在羊山頂上，視野開闊。東面是一望無際的草原，北面群山連綿，西面則是一片懸崖峭壁。山頂上有一塊平坦的巨石，上面刻著一些古老的符文，已經被風雨侵蝕得模糊不清了。
LONG
	);
	set("outdoors", "wilderness");
	set("objects", ([
		__DIR__"npc/eagle" : 1,
	]));
	set("exits", ([
		"south" : __DIR__"hillside",
		"west" : __DIR__"cliff",
	]));

	setup();
	replace_program(ROOM);
}
