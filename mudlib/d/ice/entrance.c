// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "冰域入口");
	set("long", @LONG
空氣在此驟然變得寒冷刺骨，路面上覆蓋著一層薄冰，踩上去嘎吱作響。前方是一片銀白色的冰雪世界，北風呼嘯而過，捲起漫天的雪花。遠處可見幾座晶瑩剔透的冰柱矗立在風雪之中。
LONG
	);
	set("outdoors", "wilderness");
	set("exits", ([
		"south" : "/d/road/mountain_road2",
		"north" : __DIR__"ice_field",
	]));

	setup();
	replace_program(ROOM);
}
