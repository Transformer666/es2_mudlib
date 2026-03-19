// Room: /d/manglin/path1.c

inherit ROOM;

void create()
{
	set("short", "莽林小徑");
	set("long", @LONG
叢林中的小徑越來越窄﹐兩旁的灌木和荊棘幾乎要把路堵死。地上
落滿了厚厚的枯葉﹐踩上去嘎吱作響。林中不時傳來各種奇怪的聲音﹐
讓人不禁心生警惕。往東有一片開闊的空地﹐往北則繼續深入莽林。
LONG
	);
	set("outdoors", "forest");
	set("objects", ([
		__DIR__"npc/wild_boar" : 1,
	]));
	set("exits", ([
		"south" : __DIR__"entrance",
		"north" : __DIR__"path2",
		"east" : __DIR__"clearing",
	]));

	setup();
	replace_program(ROOM);
}
