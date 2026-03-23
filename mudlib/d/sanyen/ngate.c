// Room: /d/sanyen/ngate.c

inherit ROOM;

void create()
{
	set("short", "焱硝村北口");
	set("long", @LONG
焱硝村北面的出入口﹐用幾根粗木樁和繩索搭成的簡易路障橫在
路中間﹐勉強算是一道關卡。路障旁邊釘著一塊木板﹐上面潦草地寫
著「焱硝村」三個字。往北是通往黑風山的山路﹐遠遠便能看到山上
飄著的黑色旗幟。往南進入村子﹐可以聽到村裡隱約傳來的說話聲。
LONG
	);
	set("outdoors", "village");
	set("objects", ([
		__DIR__"npc/guard" : 1,
	]));
	set("exits", ([
		"north" : "/d/heifeng/road2",
		"south" : __DIR__"entrance",
	]));

	setup();
	replace_program(ROOM);
}
