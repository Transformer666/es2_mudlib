// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "迷霧深處");
	set("long", @LONG
這裡是水霧最為濃密的區域，四周一片白茫茫，完全失去了方向感。地面上佈滿了枯枝落葉，踩上去發出令人不安的碎裂聲。空氣中的水分凝結在每一個表面上，到處都是滴答滴答的滴水聲。
LONG
	);
	set("outdoors", "wilderness");
	set("objects", ([
		__DIR__"npc/centipede" : 1,
	]));
	set("exits", ([
		"west" : __DIR__"fog_path",
	]));

	setup();
	replace_program(ROOM);
}
