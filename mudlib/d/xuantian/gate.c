inherit ROOM;

void create()
{
    set("short", "玄天教壇");
    set("long", @LONG
教壇前立著一座石牌坊﹐牌坊上刻著「玄天上帝」四個大字。牌坊
兩側各立著一面黑色旗幟﹐在風中獵獵作響。通過牌坊便可進入玄天教
的正殿。
LONG
    );
    set("exits", ([
        "south" : __DIR__"path",
        "north" : __DIR__"hall",
    ]));

    setup();
    replace_program(ROOM);
}
