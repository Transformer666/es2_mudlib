inherit ROOM;

void create()
{
    set("short", "寺院前庭");
    set("long", @LONG
寺院前庭寬敞整潔﹐中央種著一棵古老的菩提樹﹐枝繁葉茂﹐據說
已有數百年的歷史。樹下放著幾個石凳﹐供僧眾和香客歇息。庭中有一
口石刻的蓮花水池﹐池水清澈見底。
LONG
    );
    set("objects", ([
        __DIR__"npc/greeter" : 1,
    ]));
    set("exits", ([
        "south" : __DIR__"gate",
        "north" : __DIR__"hall",
    ]));

    setup();
    replace_program(ROOM);
}
