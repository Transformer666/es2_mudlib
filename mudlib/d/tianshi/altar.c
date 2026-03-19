inherit ROOM;

void create()
{
    set("short", "煉法壇");
    set("long", @LONG
一座圓形的法壇﹐壇上繪著太極八卦圖﹐四周擺放著金木水火土五
行的法器。法壇中央燃著一爐青煙﹐隱約可聞雷聲和風聲在壇上迴盪
﹐似乎蘊含著某種道法的力量。
LONG
    );
    set("exits", ([
        "south" : __DIR__"hall",
    ]));

    setup();
    replace_program(ROOM);
}
