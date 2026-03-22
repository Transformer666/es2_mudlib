// Room: /d/lee/r1.c

inherit ROOM;

void create()
{
	set("short", "河邊小路");
	set("long", @LONG
一條沿著河岸延伸的小石子路﹐河水在旁邊嘩嘩地流淌。路面由
碎石和泥土鋪成﹐兩旁長著幾叢蘆葦和野草。過了小橋往西南方向可
以回到雪亭鎮﹐順著河往東走便是李家村的方向。遠處可以看到幾縷
炊煙裊裊升起。
LONG
	);
	set("outdoors", "road");
	set("exits", ([
		"southwest" : "/d/snow/egate",
		"east" : __DIR__"gate",
	]));

	setup();
	replace_program(ROOM);
}
