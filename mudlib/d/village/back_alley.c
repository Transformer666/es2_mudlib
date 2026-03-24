// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "荒僻小巷");
	set("long", @LONG
水井東面是一條荒僻的小巷﹐兩旁的屋子大多已經空置﹐門窗破
舊﹐野草從牆縫中長了出來。這裡曾經住著幾戶人家﹐後來年輕
人都離開了﹐只剩下這些空屋子在風中搖搖欲墜。巷子盡頭有一
間廢棄的老宅﹐看上去很久沒有人住了。
LONG
	);
	set("outdoors", "wilderness");
	set("exits", ([
		"west" : __DIR__"well",
		"south" : __DIR__"abandoned_house",
	]));

	setup();
	replace_program(ROOM);
}
