// Room: /d/road/road4.c

inherit ROOM;

void create()
{
	set("short", "官道");
	set("long", @LONG
官道蜿蜒穿過起伏的丘陵地帶，兩旁是大片的荒草和零星的灌木。
遠處隱約可見五堂鎮的城牆輪廓，在陽光下泛著灰白色的光芒。路面
雖然有些坑窪，但仍然算得上寬敞平坦，足以讓馬車通行無阻。
LONG
	);
	set("outdoors", "road");
	set("exits", ([
		"west" : __DIR__"road3",
		"east" : __DIR__"road5",
		"south" : "/d/baihua/road",
	]));

	setup();
	replace_program(ROOM);
}
