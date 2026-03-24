// Room: /d/sanyen/east_lane.c

inherit ROOM;

void create()
{
	set("short", "村東小巷");
	set("long", @LONG
村子東邊一條幽深的窄巷﹐兩旁是年久失修的土牆﹐牆面上爬滿了
青苔與枯藤。石板路的縫隙間長出了叢叢野草﹐隨風搖曳。巷子盡頭
隱約傳來幾聲犬吠﹐空氣中帶著一絲泥土與枯葉的氣息﹐顯得荒涼而
寂寥。
LONG
	);
	set("exits", ([
		"south" : __DIR__"old_well",
	]));

	setup();
	replace_program(ROOM);
}
