inherit ROOM;

void create()
{
    set("short", "窄巷");
    set("long", @LONG
一條幽暗的窄巷﹐兩側是高牆﹐陽光幾乎照不進來。巷中瀰漫著一
股怪異的氣氛﹐牆壁上畫著一張半哭半笑的面具圖案﹐令人毛骨悚然。
LONG
    );
    set("exits", ([
        "southwest" : "/d/snow/square_n",
        "north" : __DIR__"gate",
    ]));

    setup();
    replace_program(ROOM);
}
