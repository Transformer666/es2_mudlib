// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "鐘樓");
	set("long", @LONG
一座高聳的鐘樓矗立在外殿東側，樓內懸掛著一口巨大的銅鐘，鐘身上鑄著密密麻麻的經文。每當鐘聲響起，悠揚的鐘聲便會迴盪在整座神殿之中，據說有安神定魄的功效。樓內的木梯已經有些年頭了，走起來嘎吱作響。
LONG
	);
	set("objects", ([
		__DIR__"npc/bell_keeper" : 1,
	]));
	set("exits", ([
		"west" : __DIR__"outer_hall",
	]));

	setup();
	replace_program(ROOM);
}
