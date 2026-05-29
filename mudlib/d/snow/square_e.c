// Room: /d/snow/square_e.c

inherit ROOM;

void create()
{
	set("short", "廣場");
	set("long", @LONG
這裡是雪亭鎮廣場東邊﹐往東是一條僻靜的巷子﹐西邊有一株高大
的榕樹﹐南邊是一家打鐵鋪子﹐不過店門不在這一邊。往東北的山道上去
﹐隱約可見一座道家牌坊﹐想是天師派的山門﹔往東南的小徑上﹐則飄
來陣陣藥香﹐想是龍圖丹派的所在﹔往西北雲霧繚繞的石階上去﹐隱隱
傳來誦咒之聲﹐想是茅山派的道觀。
LONG
	);
	set("exits", ([ /* sizeof() == 4 */
		"east" : __DIR__"epath",
		"west" : __DIR__"square",
		"northeast" : "/d/tianshi/gate",
		"southeast" : "/d/longtu/gate",
		"northwest" : "/d/maoshan/gate",
]));
	set("outdoors", "snow");

	setup();
	replace_program(ROOM);
}
