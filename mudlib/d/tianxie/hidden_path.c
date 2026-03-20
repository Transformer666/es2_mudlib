inherit ROOM;

void create()
{
    set("short", "密林暗道");
    set("long", @LONG
一條隱蔽的小徑蜿蜒在密林之中﹐四周的樹木遮天蔽日﹐只有偶爾
透過的幾縷陽光照亮了腳下的路。地上覆蓋著厚厚的落葉﹐走在上面幾
乎沒有聲響。空氣中瀰漫著一股陰冷的氣息。
LONG
    );
    set("outdoors", "forest");
    set("objects", ([
        __DIR__"npc/daxiedaoren" : 1,
    ]));
    set("exits", ([
        "south" : "/d/manglin/path3",
        "north" : __DIR__"gate",
    ]));

    setup();
    replace_program(ROOM);
}
