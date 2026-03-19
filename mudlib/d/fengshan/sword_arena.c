// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "劍道場");
    set("long", @LONG
一片開闊的崖頂平台，便是封山派弟子練劍的道場。四周沒有任何
遮擋，山風猛烈地吹拂著，完美契合封山派風劍技法的修練要求。平台
邊緣豎立著數根石柱，柱身上刻著劍痕，是弟子們以劍氣刻寫的心得。
LONG
    );
    set("exits", ([
        "west" : __DIR__"main_hall",
    ]));

    setup();
    replace_program(ROOM);
}
