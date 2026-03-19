// Room: /d/heifeng/yard.c

inherit ROOM;

void create()
{
	set("short", "山寨大院");
	set("long", @LONG
穿過寨門便是黑風寨的大院﹐地面是夯實的黃土﹐院子中央插著一
面黑色大旗。四周是一圈用木頭和泥巴砌成的房屋﹐有的是匪徒住的營
房﹐有的是堆放搶來贓物的倉庫。幾個匪徒在院子裡喝酒賭錢﹐吆五
喝六好不熱鬧。
LONG
	);
	set("objects", ([
		__DIR__"npc/bandit" : 2,
	]));
	set("exits", ([
		"south" : __DIR__"gate",
		"north" : __DIR__"hall",
		"east" : __DIR__"cell",
	]));

	setup();
	replace_program(ROOM);
}
