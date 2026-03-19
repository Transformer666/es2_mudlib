inherit ROOM;

void create()
{
    set("short", "鍛造室");
    set("long", @LONG
鍛造室中央擺放著一座巨大的鍛造爐﹐爐火熊熊燃燒。旁邊是一座
沈重的鐵砧和各種鍛造工具。牆上掛著幾把正在製作中的劍器﹐有的已
經成形﹐有的還只是粗胚。
LONG
    );
    set("objects", ([
        __DIR__"npc/smith" : 1,
    ]));
    set("exits", ([
        "south" : __DIR__"hall",
    ]));

    setup();
    replace_program(ROOM);
}
