// Room: /d/shuiyue/egate.c

inherit ROOM;

void create()
{
    set("short", "水月村東口");
    set("long", @LONG
這裡是水月村的南邊出口﹐一條小路穿過竹林向南延伸﹐通往
雪吟莊的方向。竹林中不時傳來鳥鳴聲﹐清風拂過竹葉沙沙作響﹐
十分清幽。
LONG
    );
    set("outdoors", "village");
    set("exits", ([
        "west" : __DIR__"square",
        "south" : "/d/xueyin/entrance",
    ]));

    setup();
    replace_program(ROOM);
}
