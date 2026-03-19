// Room: /d/wutang/wgate.c

inherit ROOM;

void create()
{
	set("short", "五堂鎮西門");
	set("long", @LONG
這裡是五堂鎮的西門﹐城門比東門和南門都要小一些﹐平日裡進出
的多是附近的樵夫和獵戶。門外是一片莽莽蒼蒼的荒野﹐遠處隱約可
見連綿的山嶺。一名守衛靠在門邊﹐懶洋洋地曬著太陽。往東穿過門
洞便回到鎮內。
LONG
	);
	set("objects", ([
		__DIR__"npc/guard" : 1,
	]));
	set("exits", ([
		"east" : __DIR__"square_w",
		"west" : "/d/road/road5",
	]));

	setup();
	replace_program(ROOM);
}
