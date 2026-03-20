// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "霧林空地");
	set("long", @LONG
小島的東端是一片意外的開闊地，霧氣在此散去了大半，陽光透過薄霧灑下，形成一片金色的光柱。空地中央有一棵巨大的古木，樹幹粗得要幾個人才能合抱，樹枝上掛滿了不知名的果實。這裡似乎是水霧林的核心所在。
LONG
	);
	set("outdoors", "wilderness");
	set("objects", ([
		__DIR__"npc/fog_hermit" : 1,
	]));
	set("exits", ([
		"west" : __DIR__"island",
	]));

	setup();
	replace_program(ROOM);
}
