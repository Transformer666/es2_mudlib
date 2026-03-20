// Room: /d/weiguo/temple.c

#include <room.h>

inherit TEMPLE;

void create()
{
	set("short", "城隍廟");
	set("long", @LONG
街道西邊的一座城隍廟﹐廟門上方掛著一塊匾額﹐上書「護國城隍」
四字。廟裡香火不算旺盛﹐但打掃得很乾淨。正殿供奉著城隍爺的塑
像﹐身披鎧甲﹐威風凜凜﹐與這軍鎮的氣質倒是十分相配。據說鎮上
的將士出征前都會來此祈求平安。
LONG
	);
	set("objects", ([
		__DIR__"npc/temple_keeper" : 1,
	]));
	set("no_fight", 1);
	set("exits", ([
		"east" : __DIR__"street",
	]));

	setup();
	replace_program(TEMPLE);
}
