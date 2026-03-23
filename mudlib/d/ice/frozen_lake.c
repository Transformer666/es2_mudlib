// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "冰湖");
	set("long", @LONG
這是一面完全結凍的湖泊，冰面如鏡一般光滑，透過冰層可以隱約看到湖底的水草和游魚被凝固在冰中。湖面上覆蓋著一層薄雪，留著幾行不知名動物的爪印。湖的北面是一片壯觀的冰川。
LONG
	);
	set("outdoors", "wilderness");
	set("detail", ([
		"冰層" : "冰層下方隱約可見一個巨大的暗影，形狀像是一隻蟾蜍，但體型遠超尋常。冰面上留有一灘黏液的痕跡，觸之刺骨寒冷。\n",
	]));
	set("objects", ([
		__DIR__"npc/ice_wolf" : 1,
	]));
	set("exits", ([
		"south" : __DIR__"ice_field",
		"north" : __DIR__"glacier",
	]));

	setup();
	replace_program(ROOM);
}
