// Room: /d/city/alley.c

inherit ROOM;

void create()
{
	set("short", "小巷");
	set("long", @LONG
離開繁華的大街，這條幽暗的小巷顯得格外寂靜。兩旁的房屋年
久失修，牆壁上爬滿了青苔和藤蔓。地上散落著一些枯葉和碎石，偶
爾有野貓從陰暗的角落竄過。巷子盡頭似乎有一間當鋪。
LONG
	);
	set("objects", ([
		__DIR__"npc/beggar" : 1,
	]));
	set("exits", ([
		"east"  : __DIR__"main_street",
		"north" : __DIR__"pawnshop",
	]));

	setup();
	replace_program(ROOM);
}
