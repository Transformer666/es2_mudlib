// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "演武場");
    set("long", @LONG
一片寬闊的演武場，石柱上佈滿了刀痕劍跡，可見日常練功之激烈。
場中豎立著數個人形木樁，排列成陣。地面是堅硬的青石板，上面的刀
痕縱橫交錯，無聲地訴說著虎刀門弟子的刻苦修練。
LONG
    );
    set("exits", ([
        "west" : __DIR__"hall",
        "east" : __DIR__"disciple_quarters",
    ]));

    setup();
    replace_program(ROOM);
}
