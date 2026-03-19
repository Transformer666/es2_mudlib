inherit ROOM;

void create()
{
    set("short", "客房");
    set("long", @LONG
一間雅致的客房﹐佈置得十分舒適。靠窗擺著一張書桌和一把太師
椅﹐桌上放著幾本書和一壺清茶。窗外可以看到花園中的景色。
LONG
    );
    set("no_fight", 1);
    set("objects", ([
        __DIR__"npc/maid" : 1,
    ]));
    set("exits", ([
        "south" : __DIR__"hall",
    ]));

    setup();
    replace_program(ROOM);
}
