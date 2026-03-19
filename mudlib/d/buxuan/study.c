inherit ROOM;

void create()
{
    set("short", "沐華書齋");
    set("long", @LONG
書齋中琴棋書畫一應俱全﹐四壁掛滿了名家字畫。一張寬大的書桌
上擺放著文房四寶﹐旁邊堆著幾疊書卷。書架上的典籍從經史子集到武
學秘笈無所不有﹐可見主人學識淵博。
LONG
    );
    set("objects", ([
        __DIR__"npc/master" : 1,
    ]));
    set("exits", ([
        "west"  : __DIR__"garden",
        "north" : __DIR__"hall",
    ]));

    setup();
    replace_program(ROOM);
}
