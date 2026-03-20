// Room: /d/weiguo/inn.c

#include <room.h>

inherit INN;

void create()
{
	set("short", "衛國客棧");
	set("long", @LONG
一間結實樸素的客棧，專為來往的戍邊將士和行商旅人提供食宿。
大廳裡的桌椅都是厚實的松木打造，經久耐用。牆上掛著幾把生了銹
的刀劍作為裝飾，角落裡還擺著一面殘破的戰鼓。掌櫃是個退伍的老
兵，說話嗓門極大。
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
