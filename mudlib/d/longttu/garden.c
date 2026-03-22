inherit ROOM;

void create()
{
    set("short", "藥草園");
    set("long", @LONG
一片精心照料的藥草園﹐各種珍貴的藥草分區種植﹐標著名牌。靈
芝、人參、何首烏等名貴藥材在這裡都能見到。園中有一口石井﹐用來
灌溉藥草。
LONG
    );
    set("exits", ([
        "west"  : __DIR__"hall",
        "east"  : __DIR__"lab",
        "north" : __DIR__"storehouse",
    ]));

    setup();
    replace_program(ROOM);
}
