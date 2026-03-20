inherit ROOM;

void create()
{
    set("short", "隱教暗門");
    set("long", @LONG
密道盡頭是一道厚重的石門﹐門上刻著一隻展翅的蒼鷹。石門兩側
各站著一名面無表情的暗衛﹐冷冷地注視著來人。
LONG
    );
    set("objects", ([
        __DIR__"npc/dark_guard" : 2,
        __DIR__"npc/herald" : 1,
    ]));
    set("exits", ([
        "south" : __DIR__"secret_passage",
        "north" : __DIR__"hall",
    ]));

    setup();
    replace_program(ROOM);
}
