// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "晚月谷入口");
	set("long", @LONG
穿過一片竹林，眼前出現了一個幽靜的山谷。不知為何，這裡的天空總是呈現出一種黃昏般的暮色，月亮似乎永遠掛在天邊，灑下清冷的月光。山谷中瀰漫著一層薄薄的霧氣，景色如夢似幻。
LONG
	);
	set("outdoors", "wilderness");
	set("exits", ([
		"south" : "/d/road/wild_path2",
		"north" : __DIR__"moonlight_path",
	]));

	setup();
	replace_program(ROOM);
}
