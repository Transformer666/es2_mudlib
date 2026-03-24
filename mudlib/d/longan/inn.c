// Room: /d/longan/inn.c

#include <room.h>

inherit INN;

void create()
{
	set("short", "龍安客棧");
	set("long", @LONG
龍安城中一間頗具規模的客棧，來往的多是南北行商和官府差役。
大廳裡擺著紅木桌椅，牆上掛著幾幅山水字畫，角落裡一座青銅香爐
嫋嫋升煙。掌櫃坐在櫃臺後面撥弄算盤，小二殷勤地穿梭在桌椅之
間招呼客人。
LONG
	);
	set("objects", ([
		__DIR__"npc/innkeeper" : 1,
	]));
	set("valid_startroom", 1);
	set("no_fight", 1);
	set("exits", ([
		"south" : __DIR__"square",
		"north" : __DIR__"north_street",
	]));

	setup();
}
