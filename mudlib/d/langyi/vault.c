inherit ROOM;

void create()
{
    set("short", "地窖");
    set("long", @LONG
一個陰暗潮濕的地窖﹐堆放著各種箱籠包裹﹐看起來都是從各地
「收集」來的贓物。牆角放著幾只上了鎖的鐵箱﹐不知道裡面藏著什
麼值錢的東西。
LONG
    );
    set("exits", ([
        "south" : __DIR__"hall",
    ]));

    setup();
    replace_program(ROOM);
}
