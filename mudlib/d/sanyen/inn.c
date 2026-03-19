// Room: /d/sanyen/inn.c

#include <room.h>

inherit INN;

void create()
{
	set("short", "村中客店");
	set("long", @LONG
一間十分簡陋的客店﹐只有幾張粗木桌子和幾條板凳。牆角堆著一
些乾草﹐那大概就是客人過夜的地方了。雖然條件簡陋﹐但在這偏僻的
地方能有個遮風避雨的去處已是不易。店裡的老闆正在櫃臺後面打瞌睡。
LONG
	);
	set("objects", ([
		__DIR__"npc/innkeeper" : 1,
	]));
	set("valid_startroom", 1);
	set("no_fight", 1);
	set("exits", ([
		"east" : __DIR__"street",
	]));

	setup();
}
