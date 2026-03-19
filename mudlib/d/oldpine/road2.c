// Room: /d/oldpine/road2.c

inherit ROOM;

void create()
{
	set("short", "松林深處");
	set("long", @LONG
松林越來越密﹐小徑也越來越窄﹐勉強只容一人通過。兩旁的松樹
粗壯無比﹐樹幹上佈滿青苔﹐有些樹根裸露在外﹐盤根錯節如同蟒蛇
一般。林中瀰漫著一股潮濕腐朽的氣味﹐不時有蛇蟲從腳邊竄過。往
東有一個隱約可見的山洞入口﹐往南則繼續深入松林。仔細觀察﹐
往西的灌木叢中似乎有人走過的痕跡。
LONG
	);
	set("outdoors", "forest");
	set("objects", ([
		__DIR__"npc/wolf" : 1,
		__DIR__"npc/bandit" : 1,
	]));
	set("exits", ([
		"north" : __DIR__"road1",
		"south" : __DIR__"road3",
		"east" : __DIR__"cave",
		"west" : __DIR__"camp",
	]));

	setup();
	replace_program(ROOM);
}
