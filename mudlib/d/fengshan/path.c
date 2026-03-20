// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "山間石道");
    set("long", @LONG
一條蜿蜒的石板路沿著山腰盤旋而上，兩旁古松參天，松濤陣陣。
山風穿過松林，帶來上方傳來的陣陣劍鳴聲，清脆悅耳。石道旁偶爾
可見被劍氣削平的岩石，顯示著封山派弟子日常練劍的痕跡。
LONG
    );
    set("exits", ([
        "south" : __DIR__"gate",
        "north" : __DIR__"main_hall",
        "west"  : __DIR__"waterfall",
    ]));

    setup();
    replace_program(ROOM);
}
