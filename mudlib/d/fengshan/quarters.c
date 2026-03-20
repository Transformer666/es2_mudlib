// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "弟子房");
    set("long", @LONG
簡樸的石室沿著山壁排列，每間石室內只有一張木床和一個劍架，
別無他物。封山派崇尚簡約，弟子們的生活起居也一如他們的劍法一般
，摒棄繁華，追求純粹。石壁上偶爾可見弟子以劍尖刻下的練功心得。
LONG
    );
    set("objects", ([
        __DIR__"npc/disciple" : 1,
    ]));
    set("exits", ([
        "east" : __DIR__"main_hall",
    ]));
    set("no_fight", 1);

    setup();
    replace_program(ROOM);
}
