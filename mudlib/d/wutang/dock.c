// Room: /d/wutang/dock.c

inherit ROOM;

void create()
{
    set("short", "五堂碼頭");
    set("long", @LONG
這裡是五堂鎮的碼頭﹐一條寬闊的河流從鎮子西邊流過﹐河水
渾濁而湍急。碼頭邊停泊著幾條小漁船﹐一條稍大的渡船繫在木樁
上隨波起伏。河對岸隱約可以看到連綿的山巒。
LONG
    );
    set("detail", ([
	"渡船" : "一條不大的木船﹐船頭掛著一盞燈籠﹐上面寫著「渡」字。\n",
	"河水" : "河水渾濁湍急﹐看不到底﹐不時有漩渦出現。\n",
    ]));
    set("objects", ([
	__DIR__"npc/ferryman" : 1,
    ]));
    set("exits", ([
	"east" : __DIR__"street3",
    ]));

    setup();
    replace_program(ROOM);
}
