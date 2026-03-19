inherit ROOM;

void create()
{
    set("short", "針灸房");
    set("long", @LONG
針灸房中擺放著數張診療床﹐每張床旁都放著一個精緻的針灸箱。
牆上掛滿了經絡穴位的圖譜﹐標注得十分詳細。一名學徒正在認真地
研究穴位圖。
LONG
    );
    set("exits", ([
        "south" : __DIR__"hall",
    ]));

    setup();
    replace_program(ROOM);
}
