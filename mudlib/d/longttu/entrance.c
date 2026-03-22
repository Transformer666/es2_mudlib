inherit ROOM;

void create()
{
    set("short", "龍圖丹房");
    set("long", @LONG
藥鋪後方別有洞天﹐穿過一道小門便來到龍圖丹派的丹房。空氣中
瀰漫著濃郁的藥香﹐幾個大藥罐整齊地擺放在牆邊。一名學徒正在研
磨藥材﹐專心致志。
LONG
    );
    set("exits", ([
        "west" : "/d/snow/herb_shop",
        "east" : __DIR__"hall",
    ]));

    setup();
    replace_program(ROOM);
}
