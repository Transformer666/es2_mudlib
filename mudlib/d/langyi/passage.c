inherit ROOM;

void create()
{
    set("short", "幽暗通道");
    set("long", @LONG
一條幽暗狹窄的通道﹐兩壁是粗糙的岩石﹐滴著水珠。通道蜿蜒曲
折﹐走在其中伸手不見五指﹐只能靠牆壁上偶爾出現的夜明珠辨認方
向。空氣中帶著一股霉味。
LONG
    );
    set("objects", ([
        __DIR__"npc/assassin" : 1,
    ]));
    set("exits", ([
        "south" : __DIR__"tunnel",
        "north" : __DIR__"hall",
    ]));

    setup();
    replace_program(ROOM);
}
