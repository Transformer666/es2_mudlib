// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "掌門靜室");
    set("long", @LONG
掌門靜室佈置得清雅脫俗，一張古樸的蒲團置於正中，是掌門日常
打坐修煉之所。牆上掛著一幅太極八卦圖，旁邊的木架上擺放著幾卷
泛黃的道藏經典和一柄拂塵。窗外松風陣陣，令人心曠神怡，實在是
修身養性的絕佳之地。
LONG
    );
    set("no_fight", 1);
    set("exits", ([
        "west" : __DIR__"hall",
    ]));

    setup();
    replace_program(ROOM);
}
