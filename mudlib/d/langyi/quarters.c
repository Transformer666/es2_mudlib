inherit ROOM;

void create()
{
    set("short", "密室");
    set("long", @LONG
一間隱蔽的密室﹐四壁裝飾得頗為精緻﹐與外面的粗獷風格截然不
同。幾張舒適的榻椅和一張寬大的書桌佔據了房間的大部分空間﹐桌上
散落著一些書信和地圖。
LONG
    );
    set("no_fight", 1);
    set("exits", ([
        "east" : __DIR__"hall",
    ]));

    setup();
    replace_program(ROOM);
}
