// Room: /d/kangping/inn.c

#include <room.h>

inherit INN;

void create()
{
	set("short", "小客店");
	set("long", @LONG
一間簡陋的小客店﹐屋頂是茅草鋪的﹐牆壁用泥巴糊成。店裡只
有三四張桌子﹐一個木頭櫃臺。雖然簡陋﹐但收拾得還算乾淨﹐桌上
擺著粗瓷的茶壺和碗碟。一股草藥茶的清香從櫃臺後面飄來。
LONG
	);
	set("objects", ([
		__DIR__"npc/innkeeper" : 1,
	]));
	set("valid_startroom", 1);
	set("no_fight", 1);
	set("exits", ([
		"south" : __DIR__"square",
	]));

	setup();
}
