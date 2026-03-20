// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "霧中木橋");
	set("long", @LONG
一座搖搖欲墜的木橋橫跨在一條渾濁的溪流之上，橋板已經腐朽，踩上去吱嘎作響。溪水在霧中看不清顏色，但可以聽到水流湍急的聲音。橋的另一端隱沒在更深的霧氣之中。
LONG
	);
	set("outdoors", "wilderness");
	set("exits", ([
		"south" : __DIR__"fog_path",
		"north" : __DIR__"island",
	]));

	setup();
	replace_program(ROOM);
}
