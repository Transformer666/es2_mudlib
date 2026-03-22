// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "茅山山門");
    set("long", @LONG
茅山山門的石柱上雕刻著陰陽太極的圖案，山嵐霧氣繚繞在門前，
若隱若現。穿過山門，正前方是茅山派的三清殿，東面通往隱風觀，
西面通往幻霧觀。
LONG
    );
    set("exits", ([
        "northeast" : "/d/road/road5",
        "north" : __DIR__"hall",
        "east"  : __DIR__"yinfeng",
        "west"  : __DIR__"huanwu",
    ]));

    setup();
    replace_program(ROOM);
}
