// Room: /d/weiguo/east_street.c

inherit ROOM;

void create()
{
	set("short", "東街");
	set("long", @LONG
衛國鎮東邊的一條寬闊街道﹐青石板路面被來往的車馬碾得光滑發
亮。幾輛裝滿糧草輜重的軍用馬車停靠在路旁﹐車伕們正忙著卸貨。巡
邏的士兵三五成群﹐邁著整齊的步伐沿街行進﹐甲冑鏗鏘﹐威風凜凜。
LONG
	);
	set("exits", ([
		"west"  : __DIR__"smithy",
		"south" : __DIR__"shop",
	]));

	setup();
	replace_program(ROOM);
}
