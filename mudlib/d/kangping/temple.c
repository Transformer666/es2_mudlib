// Room: /d/kangping/temple.c

#include <room.h>

inherit TEMPLE;

void create()
{
	set("short", "康平土地廟");
	set("long", @LONG
村子南邊一座小小的土地廟﹐廟門低矮﹐牆壁斑駁﹐看起來已有些
年頭。廟裡供著一尊土地公的泥塑像﹐雖然粗糙﹐卻被香火薰得烏黑
發亮。神像前的香爐裡插著幾根香﹐嫋嫋的青煙在廟中繚繞。一個老
廟祝正在廟裡打掃。
LONG
	);
	set("objects", ([
		__DIR__"npc/temple_keeper" : 1,
	]));
	set("no_fight", 1);
	set("exits", ([
		"west" : __DIR__"well",
	]));

	setup();
	replace_program(TEMPLE);
}
