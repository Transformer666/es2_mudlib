// Room: /d/graveyard/tomb.c

inherit ROOM;

void create()
{
	set("short", "古墓入口");
	set("long", @LONG
一座半掩在荒草中的古墓入口﹐墓門是一塊巨大的石板﹐已經被人
推開了一半。從裡面吹出一股冰冷的陰風﹐夾雜著一種難以形容的腐朽
氣味。墓門兩側刻著一些奇怪的符文﹐在陰暗的光線下隱約閃爍著微弱
的光芒。
LONG
	);
	set("exits", ([
		"west" : __DIR__"grave2",
		"north" : __DIR__"tomb_inner",
	]));

	setup();
	replace_program(ROOM);
}
