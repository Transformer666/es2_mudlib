// Room: /d/weiguo/square.c

inherit ROOM;

void create()
{
	set("short", "衛國鎮廣場");
	set("long", @LONG
鎮中心的廣場是士兵們集合操練的場所，地面是夯實的黃土，被無
數雙軍靴踩踏得堅硬如鐵。廣場中央插著一面大旗，上書一個斗大的
「衛」字，在風中獵獵作響。北面是一間供來往軍民歇腳的客棧，東面
則是軍營的營房。一名老兵正坐在旗桿下擦拭著他的長矛。
LONG
	);
	set("exits", ([
		"south" : __DIR__"street",
		"north" : __DIR__"inn",
		"east"  : __DIR__"barracks",
	]));

	set("objects", ([
		__DIR__"npc/soldier" : 1,
	]));

	setup();
	replace_program(ROOM);
}
