inherit ROOM;

void create()
{
    set("short", "後花園");
    set("long", @LONG
後花園種著各種花卉和假山石﹐佈局雅致。園中有一座涼亭﹐亭下
擺著石桌石凳﹐是莊中人休閒小憩之所。
LONG
    );
    set("exits", ([
        "north" : __DIR__"yard",
    ]));

    setup();
    replace_program(ROOM);
}
