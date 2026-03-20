// Room: /d/road/wild_path2.c

inherit ROOM;

void create()
{
	set("short", "荒野小徑");
	set("long", @LONG
小徑在這裡轉了一個彎﹐繼續往東延伸。路旁的荒草逐漸變得稀
疏﹐取而代之的是一些矮小的灌木和碎石。遠處隱約可以看見一個
小村莊的輪廓﹐幾縷炊煙從茅草屋頂上升起。往西可以回到之前的
荒野小徑。
LONG
	);
	set("outdoors", "wild");
	set("exits", ([
		"west" : __DIR__"wild_path1",
		"east" : "/d/chixiao/entrance",
	]));

	setup();
	replace_program(ROOM);
}
