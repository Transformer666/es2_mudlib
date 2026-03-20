// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "茅山山門");
    set("long", @LONG
茅山山門的石柱上雕刻著陰陽太極的圖案，山嵐霧氣繚繞在門前，
若隱若現。穿過山門，前方分出三條岔路，分別通往三座不同的道觀。
北面通往靈雲觀，東面通往隱風觀，西面通往幻霧觀。
LONG
    );
    set("exits", ([
        "northeast" : "/d/road/road5",
        "north" : __DIR__"lingyun",
        "east"  : __DIR__"yinfeng",
        "west"  : __DIR__"huanwu",
    ]));

    setup();
    replace_program(ROOM);
}
