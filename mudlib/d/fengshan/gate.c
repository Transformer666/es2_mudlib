// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "封山派山門");
    set("long", @LONG
封山派的山門建在懸崖峭壁之上，一條石階蜿蜒而上，通往一座高
大的石制牌坊。牌坊上雕刻著劍與雲的圖案，古樸而莊嚴。山風呼嘯
而過，帶來一陣陣清冽的松香，遠處隱約可聞金鐵交鳴之聲。
LONG
    );
    set("exits", ([
        "south" : "/d/road/mountain_road1",
        "north" : __DIR__"path",
    ]));

    setup();
    replace_program(ROOM);
}
