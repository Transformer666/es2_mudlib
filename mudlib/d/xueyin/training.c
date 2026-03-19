inherit ROOM;

void create()
{
    set("short", "練武場");
    set("long", @LONG
寬闊的練武場﹐地面是夯實的黃土﹐四周擺放著各種練功器械。場邊
的兵器架上插著木劍和竹劍﹐供弟子們練習。幾個稻草靶立在場地一端
﹐上面佈滿了劈砍的痕跡。
LONG
    );
    set("objects", ([
        __DIR__"npc/renegade" : 1,
    ]));
    set("exits", ([
        "west" : __DIR__"hall",
    ]));

    setup();
    replace_program(ROOM);
}
