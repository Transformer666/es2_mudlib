// Room: /d/wutang/dock.c

inherit ROOM;

void create()
{
    set("short", "五堂碼頭");
    set("long", @LONG
這裡是五堂鎮的碼頭﹐一條寬闊的河流從鎮子西邊流過﹐河水
渾濁而湍急。碼頭邊停泊著幾條小漁船﹐一條稍大的渡船繫在木樁
上隨波起伏。河對岸隱約可以看到連綿的山巒。
你可以搭乘渡船(board)到鯉君渡方向去。
LONG
    );
    set("detail", ([
	"渡船" : "一條不大的木船﹐船頭掛著一盞燈籠﹐上面寫著「渡」字。你可以 board 搭船過河。\n",
	"河水" : "河水渾濁湍急﹐看不到底﹐不時有漩渦出現。\n",
    ]));
    set("objects", ([
	__DIR__"npc/ferryman" : 1,
    ]));
    set("exits", ([
	"east"  : __DIR__"street3",
	"south" : __DIR__"river_bend",
    ]));

    setup();
}

void init()
{
    ::init();
    add_action("do_board", "board");
}

int do_board(string arg)
{
    object ferry;

    if( this_player()->query("life_form") == "ghost" ) {
	write("你現在是鬼魂﹐沒辦法搭船。\n");
	return 1;
    }
    write("你跳上渡船﹐渡船夫開始撐篙。\n");
    message_vision("$N跳上了渡船。\n", this_player());
    ferry = new(__DIR__"ferry");
    this_player()->move(ferry);
    return 1;
}
