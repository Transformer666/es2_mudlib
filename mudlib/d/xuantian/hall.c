inherit ROOM;

void create()
{
    set("short", "玄天正殿");
    set("long", @LONG
玄天正殿中供奉著玄天上帝的神像﹐神像手持七星劍﹐足踏龜蛇﹐
威儀非凡。殿中香煙繚繞﹐幾名教眾正在虔誠地誦經。
LONG
    );
    set("objects", ([
        __DIR__"npc/master" : 1,
    ]));
    set("exits", ([
        "south" : __DIR__"gate",
        "east"  : __DIR__"meditation",
        "west"  : __DIR__"library",
        "north" : __DIR__"quarters",
    ]));

    setup();
    replace_program(ROOM);
}
