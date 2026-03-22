// Room: /d/city/temple.c

#include <room.h>
inherit TEMPLE;

void create()
{
	set("short", "城隍廟");
	set("long", @LONG
一座古老的城隍廟坐落於此，香火鼎盛。廟門前一對石獅子栩栩
如生，大殿中央供奉著城隍爺的金身塑像，前方的香案上插滿了信眾
供奉的線香。殿內燭光搖曳，青煙繚繞，幾名虔誠的香客正在叩首
禱告。
LONG
	);
	set("objects", ([
		__DIR__"npc/temple_monk" : 1,
	]));
	set("no_fight", 1);
	set("exits", ([
		"west" : __DIR__"square",
	]));

	setup();
	replace_program(TEMPLE);
}
