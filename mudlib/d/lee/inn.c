// Room: /d/lee/inn.c

#include <room.h>

inherit INN;

void create()
{
	set("short", "李家客棧");
	set("long", @LONG
李家村唯一的一間客棧﹐門面不大但收拾得乾淨整齊。幾張方桌上
鋪著藍花布﹐桌上擺著粗瓷的茶具。靠牆的架子上擺著幾罈子自釀的
米酒﹐旁邊掛著一塊寫著「李家客棧」的木牌。掌櫃是個笑容滿面的
老實人。
LONG
	);
	set("objects", ([
		__DIR__"npc/innkeeper" : 1,
	]));
	set("valid_startroom", 1);
	set("no_fight", 1);
	set("exits", ([
		"south" : __DIR__"street",
	]));

	setup();
}
