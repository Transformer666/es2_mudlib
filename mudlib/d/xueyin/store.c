inherit ROOM;

void create()
{
    set("short", "雜貨商鋪");
    set("long", @LONG
一間不大的商鋪﹐貨架上擺放著各種兵器和日用雜貨。掌櫃在櫃臺
後面忙碌著﹐不時朝進來的客人招呼幾聲。雪吟莊的弟子們常來此處
添置裝備。
LONG
    );
    set("no_fight", 1);
    set("objects", ([
        __DIR__"npc/vendor" : 1,
    ]));
    set("exits", ([
        "east" : __DIR__"square",
    ]));

    setup();
    replace_program(ROOM);
}
