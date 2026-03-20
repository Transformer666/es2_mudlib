// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "無底深淵");
	set("long", @LONG
在冥王座的東側，大地突然裂開一道巨大的深淵，深淵中漆黑一片，看不到底部。從深淵中不斷湧出冰冷的氣流，伴隨著似有若無的低語聲。深淵的邊緣搖搖欲墜，靠近時可以感受到一股強大的吸引力在拉扯著你的身體。
LONG
	);
	set("exits", ([
		"west" : __DIR__"throne",
	]));

	setup();
	replace_program(ROOM);
}
