// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "水井旁");
	set("long", @LONG
村子東南角有一口古老的水井，井沿用青石砌成，上面架著一個轆轤。井水清涼甘甜，是村民們日常飲水的來源。井旁放著幾個木桶和一條長繩，看來經常有人來此打水。
LONG
	);
	set("outdoors", "wilderness");
	set("exits", ([
		"west" : __DIR__"farm",
	]));
	set("objects", ([
		__DIR__"npc/merchant" : 1,
	]));

	setup();
	replace_program(ROOM);
}
