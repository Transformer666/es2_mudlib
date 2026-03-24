// Room: /d/kangping/path.c

inherit ROOM;

void create()
{
	set("short", "田間小路");
	set("long", @LONG
一條蜿蜒的田間小路穿過金黃的稻田，遠處是連綿的丘陵。微風
吹過，稻浪翻滾，發出沙沙的聲響。路邊的水渠裡清水潺潺，幾隻青
蛙在田埂上跳來跳去。這裡瀰漫著泥土和稻穗的芬芳。
LONG
	);
	set("outdoors", "wilderness");
	set("objects", ([
		__DIR__"npc/farmer" : 1,
	]));
	set("exits", ([
		"north" : __DIR__"entrance",
		"west"  : __DIR__"bamboo_grove",
	]));

	setup();
	replace_program(ROOM);
}
