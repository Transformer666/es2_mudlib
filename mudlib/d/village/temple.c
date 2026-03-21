// vim: syntax=lpc

#include <room.h>

inherit TEMPLE;

void create()
{
	set("short", "土地廟");
	set("long", @LONG
這是一間小小的土地廟，只有一間屋子大小。廟裡供奉著一尊石雕的土地公像，前面放著一個小香爐，裡面插著幾根燃了一半的香。牆壁已經斑駁脫落，但廟裡打掃得很乾淨，看來村民們還是經常來此上香祈福。
LONG
	);
	set("no_fight", 1);
	set("exits", ([
		"east" : __DIR__"street",
	]));
	set("objects", ([
		__DIR__"npc/priest" : 1,
	]));

	setup();
	replace_program(TEMPLE);
}
