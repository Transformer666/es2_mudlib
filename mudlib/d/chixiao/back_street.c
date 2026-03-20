// Room: /d/chixiao/back_street.c

inherit ROOM;

void create()
{
	set("short", "赤魈村後巷");
	set("long", @LONG
村子東邊一條幽暗的小巷﹐兩旁的房屋緊緊挨在一起﹐幾乎遮蔽
了頭頂的天空。巷子裡堆著一些廢棄的農具和破瓦爛罐﹐角落裡不
時傳來窸窸窣窣的聲響﹐不知是老鼠還是什麼東西在活動。巷子盡頭
有一座小廟﹐隱約能聞到香燭的氣味。
LONG
	);
	set("exits", ([
		"west"  : __DIR__"street",
		"south" : __DIR__"temple",
	]));

	setup();
	replace_program(ROOM);
}
