// Room: /d/chixiao/temple.c

#include <room.h>

inherit TEMPLE;

void create()
{
	set("short", "赤魈村城隍廟");
	set("long", @LONG
一座陰暗低矮的小廟﹐供奉著城隍爺。廟裡的泥像面目猙獰﹐在
昏暗的光線下顯得格外陰森。神像前的香爐裡插著幾根燃了一半的
香﹐青煙裊裊﹐在廟裡繚繞不散。牆壁上畫著一些斑駁的壁畫﹐隱約
能辨認出地獄審判的場景。一個老廟祝佝僂著腰在廟裡忙碌著。
LONG
	);
	set("objects", ([
		__DIR__"npc/temple_keeper" : 1,
	]));
	set("no_fight", 1);
	set("exits", ([
		"north" : __DIR__"back_street",
	]));

	setup();
	replace_program(TEMPLE);
}
