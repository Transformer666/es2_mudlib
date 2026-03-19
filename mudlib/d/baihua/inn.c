// Room: /d/baihua/inn.c

#include <room.h>

inherit INN;

void create()
{
	set("short", "百花客棧");
	set("long", @LONG
一間溫馨的小客棧，牆上掛滿了各式各樣的乾燥花束，散發著淡
淡的花香。幾張木桌擦得乾乾淨淨，桌上各擺著一隻小花瓶，插著當
季的鮮花。窗外便是一望無際的花田，景色宜人，令人心曠神怡。
LONG
	);
	set("valid_startroom", 1);
	set("no_fight", 1);
	set("exits", ([
		"south" : __DIR__"entrance",
	]));

	setup();
}
