// Room: /d/jingji/bank.c

#include <room.h>

inherit BANK;

void create()
{
	set("short", "京畿錢莊");
	set("long", @LONG
京畿錢莊是天朝數一數二的大錢莊，門面氣派堂皇。厚重的鐵門
後面是堅固的金庫，幾名帳房先生在櫃臺後面忙碌地撥弄著算盤。
LONG
	);
	set("no_fight", 1);
	set("objects", ([
		__DIR__"npc/bank_guard" : 1,
	]));
	set("exits", ([
		"north" : __DIR__"yamen",
	]));

	setup();
	replace_program(BANK);
}
