// Room: /d/fengbai/ngate.c

inherit ROOM;

void create()
{
    set("short", "楓柏村北口");
    set("long", @LONG
這裡是楓柏村的北邊出口﹐一條山路蜿蜒北上﹐通往黑風山的方
向。黑風山上據說有不少強盜出沒﹐所以村民平時都不敢走太遠。路
旁有一個用竹子搭的簡易涼亭﹐供來往的行人歇腳。
LONG
    );
    set("outdoors", "village");
    set("exits", ([
        "south" : __DIR__"square",
        "north" : "/d/heifeng/road1",
    ]));

    setup();
    replace_program(ROOM);
}
