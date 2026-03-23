inherit ROOM;

void create()
{
    set("short", "莊前街道");
    set("long", @LONG
雪吟莊大門前的一條小街﹐兩旁開著幾家店鋪。這裡是莊中弟子和
附近村民平日往來的地方﹐雖然不算繁華﹐但也頗有幾分人氣。往北走
是雪吟莊的大門﹐往東是一間客棧﹐南面有一個小廣場。
LONG
    );
    set("exits", ([
        "north" : __DIR__"entrance",
        "east"  : __DIR__"inn",
        "south" : __DIR__"square",
    ]));

    setup();
    replace_program(ROOM);
}
