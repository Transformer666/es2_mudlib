// Room: /d/jingji/west_street.c

inherit ROOM;

void create()
{
	set("short", "西巷");
	set("long", @LONG
書院南面的一條靜謐小巷，青磚鋪地，兩旁是粉牆黛瓦的民居。
偶有幾個書生模樣的人匆匆走過，手中抱著書卷。巷子東頭連著後巷，
北面可以通往明德書院。這裡遠離市集的喧囂，倒也清雅宜人。
LONG
	);
	set("exits", ([
		"north" : __DIR__"library",
		"east" : __DIR__"back_alley",
	]));

	setup();
	replace_program(ROOM);
}
