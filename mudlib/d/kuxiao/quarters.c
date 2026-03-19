inherit ROOM;

void create()
{
    set("short", "門人居室");
    set("long", @LONG
門人居室陳設簡單﹐只是牆上掛滿了各種面具﹐有的在哭﹐有的在笑
﹐有的半哭半笑﹐入夜之後想必頗為嚇人。
LONG
    );
    set("no_fight", 1);
    set("exits", ([
        "east" : __DIR__"hall",
    ]));

    setup();
    replace_program(ROOM);
}
