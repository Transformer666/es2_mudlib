// Room: /d/longan/west_street.c

inherit ROOM;

void create()
{
	set("short", "西街");
	set("long", @LONG
龍安城西邊的一條街道，兩旁是普通的民居和小舖子。街面比大街
窄了不少，但也算整潔。幾位老人家坐在門前閒話家常，一個挑著擔子
的貨郎沿街吆喝著。遠處飄來陣陣茶香，混著街邊小販炊餅的麵香。
LONG
	);
	set("exits", ([
		"west" : __DIR__"back_street",
		"east" : __DIR__"alley",
	]));

	setup();
	replace_program(ROOM);
}
