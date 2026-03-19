inherit ROOM;

void create()
{
    set("short", "僧寮");
    set("long", @LONG
僧寮是僧眾起居之所﹐幾張簡樸的木床沿牆擺放﹐被褥疊放得整整
齊齊。每個床頭都放著一串佛珠和一部經書﹐牆上掛著佛教經文。
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
