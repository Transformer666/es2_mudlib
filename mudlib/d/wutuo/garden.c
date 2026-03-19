inherit ROOM;

void create()
{
    set("short", "藥圃");
    set("long", @LONG
一小片精心照料的藥圃﹐種著各種常用的草藥。空氣中瀰漫著清新
的藥草氣味。藥圃旁邊放著幾把園藝工具和一桶清水。
LONG
    );
    set("objects", ([
        __DIR__"npc/apprentice" : 1,
    ]));
    set("exits", ([
        "north" : __DIR__"hall",
    ]));

    setup();
    replace_program(ROOM);
}
