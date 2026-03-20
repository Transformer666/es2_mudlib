// Room: /d/tianhan/entrance.c

inherit ROOM;

void create()
{
    set("short", "天寒村村口");
    set("long", @LONG
天寒村的村口立著一塊飽經風霜的石碑，上面刻著「天寒村」三個
字，筆劃已被歲月侵蝕得有些模糊。村子四周是一片荒涼的原野，寒
風呼嘯而過，捲起地上的枯葉。往東是一條通往官道的小路，村子裡則
往西延伸著一條泥土路。
LONG
    );
    set("outdoors", "road");
    set("objects", ([
        __DIR__"npc/guard" : 1,
    ]));
    set("exits", ([
        "northeast" : "/d/road/road2",
        "west" : __DIR__"street",
    ]));

    setup();
    replace_program(ROOM);
}
