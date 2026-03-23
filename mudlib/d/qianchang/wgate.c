// Room: /d/qianchang/wgate.c

inherit ROOM;

void create()
{
	set("short", "西城門");
	set("long", @LONG
前場鎮的西城門，比東門略小一些，門洞上方長滿了青苔。城門外
是一條蜿蜒的土路，通往文國縣方向。西門進出的多是附近鄉間的
農夫和挑擔小販，不似東門那般繁忙。一陣微風吹過，帶來田野裡
莊稼的清香。
LONG
	);
	set("outdoors", "city");
	set("exits", ([
		"east" : __DIR__"street2",
		"west" : "/d/wenguo/egate",
	]));

	setup();
	replace_program(ROOM);
}
