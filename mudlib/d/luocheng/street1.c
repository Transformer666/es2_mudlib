// Room: /d/luocheng/street1.c

inherit ROOM;

void create()
{
    set("short", "羅城商街");
    set("long", @LONG
這裡是羅城最繁華的商業街道﹐兩旁店鋪鱗次櫛比﹐綢緞莊、
茶葉行、藥材鋪、當鋪一應俱全。街道上車水馬龍﹐南來北往的
商隊絡繹不絕﹐吆喝聲、討價還價聲交織在一起﹐好不熱鬧。
LONG
    );
    set("outdoors", "town");
    set("exits", ([
        "south" : __DIR__"square",
        "east"  : __DIR__"inn_hall",
    ]));

    setup();
    replace_program(ROOM);
}
