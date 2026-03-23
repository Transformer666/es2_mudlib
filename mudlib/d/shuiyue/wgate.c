// Room: /d/shuiyue/wgate.c

inherit ROOM;

void create()
{
    set("short", "水月村西口");
    set("long", @LONG
這裡是水月村的西邊入口﹐一條蜿蜒的山路通往西邊的野羊山。
路旁立著一塊木牌﹐上面歪歪斜斜地寫著「水月村」三個字﹐看來
已經有些年頭了。遠處能隱約看到野羊山的輪廓。
LONG
    );
    set("outdoors", "village");
    set("exits", ([
        "east" : __DIR__"square",
        "west" : "/d/goathill/peak",
    ]));

    setup();
    replace_program(ROOM);
}
