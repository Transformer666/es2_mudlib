inherit ROOM;

void create()
{
    set("short", "試劍場");
    set("long", @LONG
試劍場地面上擺放著幾個木製的假人﹐上面滿是劈砍的痕跡。牆邊
整齊地插著一排練習用的劍﹐場地中間還放著幾塊用來試劍的鐵板和石
塊。
LONG
    );
    set("exits", ([
        "west" : __DIR__"hall",
    ]));

    setup();
    replace_program(ROOM);
}
