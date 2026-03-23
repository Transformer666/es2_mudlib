// Room: /d/shuiyue/street1.c

inherit ROOM;

void create()
{
    set("short", "水月村小路");
    set("long", @LONG
這是一條用碎石鋪成的鄉間小路﹐兩旁種著幾棵桃樹﹐路邊有
幾戶人家﹐偶爾能聽到雞鳴狗吠之聲。北面通往村口﹐東邊有一間
小客棧。這裡遠離塵囂﹐是個清幽的好地方。
LONG
    );
    set("outdoors", "village");
    set("exits", ([
        "north" : __DIR__"square",
        "east"  : __DIR__"inn_hall",
    ]));

    setup();
    replace_program(ROOM);
}
