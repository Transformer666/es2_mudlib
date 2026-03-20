// vim: syntax=lpc

#include <room.h>

inherit INN;

private void create()
{
	set("short", "鄉村客棧");
	set("long", @LONG
這是一間十分簡陋的小客棧，幾張粗木桌椅擺放得歪歪斜斜，牆角堆著一些柴草。雖然條件簡陋，但老闆娘總是笑容滿面地招呼著每一位過客。灶台上冒著熱氣，飄來陣陣飯菜的香味。
LONG
	);
	set("valid_startroom", 1);
	set("no_fight", 1);
	set("objects", ([
		__DIR__"npc/village_innkeeper" : 1,
	]));
	set("exits", ([
		"west" : __DIR__"street",
	]));

	setup();
}
