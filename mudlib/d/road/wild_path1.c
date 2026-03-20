// Room: /d/road/wild_path1.c

inherit ROOM;

void create()
{
	set("short", "荒野小徑");
	set("long", @LONG
一條幾乎被野草和灌木淹沒的小徑，若不是仔細辨認，根本看不
出這裡曾經有路。兩旁的荒草長得比人還高，隨風發出窸窸窣窣的聲
響，令人不由得提高警覺。這一帶看起來頗為危險，獨行的旅人最好
多加小心。往北可以回到岔路口。
LONG
	);
	set("outdoors", "wild");
	set("exits", ([
		"north" : __DIR__"crossroad",
		"south" : "/d/lijun/entrance",
		"east"  : __DIR__"wild_path2",
	]));

	setup();
	replace_program(ROOM);
}
