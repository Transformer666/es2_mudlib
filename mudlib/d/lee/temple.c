// Room: /d/lee/temple.c

#include <room.h>

inherit TEMPLE;

void create()
{
	set("short", "李家村土地廟");
	set("long", @LONG
廣場南邊一間小小的土地廟﹐青磚黛瓦﹐門楣上掛著一塊褪色的木
匾﹐隱約可辨「土地祠」三字。廟裡供著一尊土地公的泥像﹐雖然
不大﹐香火倒也不斷。神像前的供桌上擺著幾碟村民供奉的瓜果﹐
一個老廟祝正在整理香燭。
LONG
	);
	set("objects", ([
		__DIR__"npc/temple_keeper" : 1,
	]));
	set("no_fight", 1);
	set("exits", ([
		"north" : __DIR__"square",
	]));

	setup();
	replace_program(TEMPLE);
}
