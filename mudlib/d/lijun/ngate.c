// Room: /d/lijun/ngate.c

inherit ROOM;

void create()
{
	set("short", "鯉君渡北門");
	set("long", @LONG
鯉君渡北面的入口﹐兩根粗大的石柱撐起一座簡樸的門樓﹐門楣
上懸著一塊木匾﹐寫著「鯉君渡」三個字。門樓雖不算氣派﹐但在這
荒涼的野地裡倒也顯得頗為醒目。兩名守衛站在石柱旁﹐盤查著來往
的行人和商旅。門外是一條通往北方的荒野小徑﹐門內便是鯉君渡口。
LONG
	);
	set("outdoors", "town");
	set("objects", ([
		__DIR__"npc/river_guard" : 2,
	]));
	set("exits", ([
		"north" : "/d/road/wild_path1",
		"south" : __DIR__"entrance",
	]));

	setup();
	replace_program(ROOM);
}
