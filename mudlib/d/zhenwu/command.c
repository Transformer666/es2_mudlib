// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "帥帳");
    set("long", @LONG
帥帳內擺放著一張巨大的沙盤，上面插滿了代表各方勢力的小旗。
桌案上攤開著幾幅軍事地圖，旁邊壓著幾卷尚未批閱的軍報。主座後
方豎立著一面碩大的「令」字大旗，兩側刀槍林立，氣勢威嚴。
LONG
    );
    set("exits", ([
        "south" : __DIR__"yard",
    ]));
    set("no_fight", 1);

    setup();
    replace_program(ROOM);
}
