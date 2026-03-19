inherit ROOM;

void create()
{
    set("short", "莊院");
    set("long", @LONG
莊院十分寬敞﹐地面鋪著青石板﹐打掃得一塵不染。院中種著幾棵
高大的松樹﹐松針蒼翠﹐不懼寒冬。幾名莊丁在院中巡邏。
LONG
    );
    set("objects", ([
        __DIR__"npc/servant" : 2,
    ]));
    set("exits", ([
        "west"  : __DIR__"entrance",
        "north" : __DIR__"hall",
        "south" : __DIR__"garden",
    ]));

    setup();
    replace_program(ROOM);
}
