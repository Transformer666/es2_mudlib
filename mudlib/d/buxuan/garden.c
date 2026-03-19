inherit ROOM;

void create()
{
    set("short", "沐華居花園");
    set("long", @LONG
一座精緻的小花園﹐佈局雅致。一條鵝卵石小路蜿蜒穿過花叢﹐兩
旁種著各種花卉﹐有蘭花、菊花、牡丹等﹐四季常開。園中有一座小亭
﹐亭中擺著棋盤和茶具。
LONG
    );
    set("exits", ([
        "west" : __DIR__"entrance",
        "east" : __DIR__"study",
    ]));

    setup();
    replace_program(ROOM);
}
