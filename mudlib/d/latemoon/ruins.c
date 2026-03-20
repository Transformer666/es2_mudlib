// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "晚月遺跡");
	set("long", @LONG
這裡是一片古老的建築遺跡，殘垣斷壁上長滿了藤蔓和野草。從殘留的石柱和雕刻來看，這裡曾經是一座宏偉的宮殿或廟宇。月光從殘破的屋頂灑下，照亮了地面上隱約可見的古老圖案。
LONG
	);
	set("outdoors", "wilderness");
	set("objects", ([
		__DIR__"npc/wind_god" : 1,
	]));
	set("exits", ([
		"south" : __DIR__"pavilion",
		"east" : __DIR__"altar",
	]));

	setup();
	replace_program(ROOM);
}
