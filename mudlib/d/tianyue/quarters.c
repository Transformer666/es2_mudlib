// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "尼寮");
    set("long", @LONG
尼寮是天月庵尼眾起居之所﹐幾張簡樸的木床沿牆排列﹐每張床
鋪都收拾得乾淨整齊﹐被褥疊得方方正正。床頭各放著一串念珠和一
部經書﹐牆上掛著幾幅佛教偈語的書法。雖然陳設極為簡單﹐但處處
透著一種清淨自在的氣息。
LONG
    );
    set("no_fight", 1);
    set("objects", ([
        __DIR__"npc/novice" : 1,
    ]));
    set("exits", ([
        "east" : __DIR__"hall",
    ]));

    setup();
    replace_program(ROOM);
}
