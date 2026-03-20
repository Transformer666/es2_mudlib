// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "松林外大路");
    set("long", @LONG
一條沿著老松林外圍的大路﹐路面被來往的商旅和軍士踩踏得十分
平整。右手邊是鬱鬱蔥蔥的老松林﹐偶爾能聽到林中傳來鳥鳴聲﹐左
手邊是一片開闊的草地。路上不時可以看到軍士巡邏的身影﹐讓人安心
不少。往東回到雪亭鎮﹐往西可以到振武軍營。
LONG
    );
    set("outdoors", "road");
    set("exits", ([
	"east"  : "/d/snow/sgate",
	"west"  : __DIR__"south_road2",
    ]));

    setup();
    replace_program(ROOM);
}
