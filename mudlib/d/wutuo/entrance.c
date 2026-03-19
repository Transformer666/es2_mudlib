inherit ROOM;

void create()
{
    set("short", "武陀堂");
    set("long", @LONG
從濟世堂藥鋪的後門穿過﹐來到一處別有洞天的院落。這裡便是武陀
一門的所在﹐院中擺放著幾張石桌﹐上面放著各種針灸器具和藥材。
LONG
    );
    set("exits", ([
        "west" : "/d/wutang/herb_shop",
        "east" : __DIR__"hall",
    ]));

    setup();
    replace_program(ROOM);
}
