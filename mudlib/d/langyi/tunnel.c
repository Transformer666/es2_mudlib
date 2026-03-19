inherit ROOM;

void create()
{
    set("short", "地道入口");
    set("long", @LONG
一個隱蔽的地道口﹐掀開暗門後﹐一股潮濕陰冷的空氣撲面而來。
石階向下延伸到黑暗之中﹐牆壁上嵌著幾顆夜明珠﹐散發出幽幽的光
芒﹐勉強照亮了前方的路。
LONG
    );
    set("exits", ([
        "up"    : "/d/wutang/lane2",
        "north" : __DIR__"passage",
    ]));

    setup();
    replace_program(ROOM);
}
