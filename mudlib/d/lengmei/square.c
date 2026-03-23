inherit ROOM;

void create()
{
    set("short", "梅林村廣場");
    set("long", @LONG
村落中央的一塊空地﹐地面鋪著碎石﹐被村民們踩得十分平整。廣場
中間有一棵大榕樹﹐樹下擺著幾條長凳﹐幾位老人坐在那裡閒話家常。
西面是一間客棧﹐東面有一家小商鋪﹐南面則是村中的小廟。
LONG
    );
    set("exits", ([
        "north" : __DIR__"street",
        "west"  : __DIR__"inn",
        "east"  : __DIR__"store",
        "south" : __DIR__"temple",
    ]));

    setup();
    replace_program(ROOM);
}
