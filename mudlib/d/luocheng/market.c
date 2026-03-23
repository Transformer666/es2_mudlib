// Room: /d/luocheng/market.c

inherit ROOM;

void create()
{
    set("short", "羅城集市");
    set("long", @LONG
這裡是羅城的集市﹐因為地處南北交通的要衝﹐各地的貨物都匯
聚於此﹐比尋常縣城的集市熱鬧了不止一倍。綢緞莊、茶葉行、藥
材鋪、皮貨行一家挨著一家﹐操著各地口音的商人在攤位前討價還價。
一股混合著香料和乾貨的氣味撲面而來﹐讓人精神為之一振。
LONG
    );
    set("outdoors", "town");
    set("objects", ([
        __DIR__"npc/merchant" : 1,
        __DIR__"npc/old_woman" : 1,
    ]));
    set("detail", ([
        "攤位" : "攤位上擺著各式各樣的貨品﹐從絲綢到藥材﹐琳瑯滿目。\n",
    ]));
    set("exits", ([
        "north" : __DIR__"street2",
        "south" : __DIR__"teahouse",
    ]));

    setup();
    replace_program(ROOM);
}
