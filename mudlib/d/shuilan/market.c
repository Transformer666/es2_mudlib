// Room: /d/shuilan/market.c

inherit ROOM;

void create()
{
    set("short", "水嵐集市");
    set("long", @LONG
這裡是水嵐縣的小集市﹐雖然規模不大﹐但因為靠近羿水渡口﹐
南來北往的商旅時常在此歇腳補給﹐所以也算得上熱鬧。幾個攤位上
擺著新鮮的魚蝦和蔬果﹐還有一些從北岸運來的乾貨和藥材。吆喝
叫賣聲和討價還價聲此起彼落﹐頗有幾分市井煙火氣。
LONG
    );
    set("outdoors", "town");
    set("objects", ([
        __DIR__"npc/merchant" : 1,
    ]));
    set("detail", ([
        "攤位" : "攤位上擺著各種南北貨物﹐從新鮮魚蝦到乾貨藥材﹐應有盡有。\n",
    ]));
    set("exits", ([
        "west"  : __DIR__"street2",
        "east"  : __DIR__"teahouse",
    ]));

    setup();
    replace_program(ROOM);
}
