// Room: /d/choyin/ngate.c

inherit ROOM;

void create()
{
	set("short", "喬陰北門");
	set("long", @LONG
喬陰縣城的北門﹐城門雖然不大﹐但修建得頗為堅固﹐厚重的木門
上包著鐵皮﹐門楣上刻著「喬陰」二字。城門外是一條通往老松林的小
路﹐進入城門便是喬陰縣的北街。兩名衙役模樣的守衛百無聊賴地靠在
城門邊﹐有一搭沒一搭地聊著天。
LONG
	);
	set("objects", ([
		__DIR__"npc/cityguard" : 2,
	]));
	set("exits", ([
		"north" : "/d/oldpine/road4",
		"south" : __DIR__"nstreet",
	]));

	setup();
	replace_program(ROOM);
}
