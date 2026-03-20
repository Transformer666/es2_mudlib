// Room: /d/kangping/herb_garden.c

inherit ROOM;

void create()
{
	set("short", "藥圃");
	set("long", @LONG
一片用籬笆圍起來的藥圃，裡面種著各種常見的草藥。幾畦藥田
整整齊齊，有金銀花、板藍根、黃芪等，空氣中瀰漫著淡淡的草藥清
香。一位老農正彎腰在田間除草，看起來對這些草藥瞭如指掌。
LONG
	);
	set("objects", ([
		__DIR__"npc/herbalist" : 1,
	]));
	set("exits", ([
		"south" : __DIR__"street",
		"north" : __DIR__"stone_cave",
	]));

	setup();
	replace_program(ROOM);
}
