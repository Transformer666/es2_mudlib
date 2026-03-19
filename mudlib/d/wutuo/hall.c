inherit ROOM;

void create()
{
    set("short", "武陀正堂");
    set("long", @LONG
武陀正堂佈置得整潔有序﹐正面牆上掛著一幅人體經絡圖﹐旁邊還
有幾幅針灸穴位圖。堂中擺放著一張診療床和幾把椅子﹐看起來像是
一間診所。
LONG
    );
    set("objects", ([
        __DIR__"npc/master" : 1,
    ]));
    set("exits", ([
        "west"  : __DIR__"entrance",
        "north" : __DIR__"needle_room",
        "south" : __DIR__"garden",
        "east"  : __DIR__"quarters",
    ]));

    setup();
    replace_program(ROOM);
}
