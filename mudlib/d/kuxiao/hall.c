inherit ROOM;

void create()
{
    set("short", "哭笑堂");
    set("long", @LONG
哭笑堂是哭笑門的正廳﹐正面牆上掛著一幅巨大的陰陽臉圖﹐左邊
是哭臉﹐右邊是笑臉。堂中陳列著各種奇門兵器﹐散發著一股詭異的氣
氛。
LONG
    );
    set("objects", ([
        __DIR__"npc/liuyi" : 1,
        __DIR__"npc/lieutenant" : 1,
    ]));
    set("exits", ([
        "south" : __DIR__"yard",
        "west"  : __DIR__"quarters",
    ]));

    setup();
    replace_program(ROOM);
}
