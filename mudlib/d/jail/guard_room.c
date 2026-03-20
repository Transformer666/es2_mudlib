// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "獄卒值房");
	set("long", @LONG
這是獄卒們值班休息的房間，屋內擺著幾張粗糙的木桌和長凳。桌上放著幾副手銬腳鐐和一些刑具，牆上掛著一串串的鑰匙。角落裡的火盆還冒著餘煙，旁邊放著幾個酒壺和剩菜殘羹，看來獄卒們剛剛吃過飯。
LONG
	);
	set("objects", ([
		__DIR__"npc/jailer" : 1,
	]));
	set("exits", ([
		"south" : __DIR__"corridor",
		"north" : __DIR__"dungeon",
	]));

	setup();
	replace_program(ROOM);
}
