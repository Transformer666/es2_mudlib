// Room: /d/weiguo/training_ground.c

inherit ROOM;

void create()
{
	set("short", "練兵場");
	set("long", @LONG
一片開闊的練兵場﹐地面鋪著厚厚的黃沙﹐踩上去沙沙作響。場邊
架著幾排兵器架﹐上面整齊地擺放著木刀木槍等操練用的器械。場中央
立著幾個稻草紮成的靶人﹐身上滿是刀砍槍刺的痕跡。幾名士兵正在
烈日下揮汗操練﹐喊殺聲此起彼伏﹐氣勢十足。
LONG
	);
	set("exits", ([
		"east"  : __DIR__"armory",
		"south" : __DIR__"watchtower",
	]));

	setup();
	replace_program(ROOM);
}
