inherit ROOM;

void create()
{
    set("short", "弟子房");
    set("long", @LONG
龍圖丹派弟子的居所﹐擺放著幾張簡樸的木床和書桌。桌上放著藥
書和筆記﹐看得出來弟子們十分用功。牆角放著一些藥材和器具。
LONG
    );
    set("objects", ([
        __DIR__"npc/apprentice_npc" : 1,
    ]));
    set("no_fight", 1);
    set("exits", ([
        "west" : __DIR__"study",
    ]));

    setup();
    replace_program(ROOM);
}
