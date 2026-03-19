// Room: /d/choyin/inn.c

#include <room.h>

inherit INN;

void create()
{
	set("short", "喬陰客棧");
	set("long", @LONG
一間普通的小客棧﹐大廳裡擺著幾張方桌﹐桌面擦得乾乾淨淨。
靠牆的架子上擺著幾罈酒和一些碗碟。掌櫃站在櫃臺後面﹐臉上堆著
笑容招呼著客人。雖然比不上大城裡的酒樓氣派﹐但是飯菜可口﹐價
錢公道﹐在這小縣城裡算是不錯的歇腳之處了。
LONG
	);
	set("objects", ([
		__DIR__"npc/innkeeper" : 1,
	]));
	set("valid_startroom", 1);
	set("no_fight", 1);
	set("exits", ([
		"west" : __DIR__"sstreet",
	]));

	setup();
}
