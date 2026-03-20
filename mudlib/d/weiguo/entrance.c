// Room: /d/weiguo/entrance.c

inherit ROOM;

void create()
{
	set("short", "衛國鎮門口");
	set("long", @LONG
一座戒備森嚴的邊防要塞，高高的瞭望塔上可以看到巡邏士兵的
身影。城門兩側的牆壁上佈滿了箭孔，城樓上旌旗招展。這裡是衛國
鎮，扼守著邊境要道，氣氛緊張而有序。進出的行人都要接受盤查，
幾名巡邏的士兵正沿著預定的路線來回走動。
LONG
	);
	set("outdoors", "fortress");
	set("exits", ([
		"east"  : "/d/road/wild_path1",
		"north" : __DIR__"street",
		"west"  : __DIR__"back_street",
	]));

	setup();
	replace_program(ROOM);
}
