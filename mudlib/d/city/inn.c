// Room: /d/city/inn.c

#include <room.h>

inherit INN;

void create()
{
	set("short", "天風客棧");
	set("long", @LONG
天風客棧是城中最大的客棧，三層高的木樓裝潢考究，大廳寬敞
明亮。紅木桌椅擦得一塵不染，牆上掛著名家字畫。掌櫃站在櫃臺後
笑臉迎客，夥計們端著菜餚在桌間穿梭。一陣陣酒菜香氣撲鼻而來，
令人食指大動。
LONG
	);
	set("objects", ([
		__DIR__"npc/innkeeper" : 1,
	]));
	set("valid_startroom", 1);
	set("no_fight", 1);
	set("exits", ([
		"east" : __DIR__"square",
	]));

	setup();
}
