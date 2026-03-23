// Room: /d/fengbai/market.c

inherit ROOM;

void create()
{
    set("short", "楓柏村小集");
    set("long", @LONG
村子南邊一塊空地上﹐每逢趕集的日子便會有附近山裡的獵戶和
採藥人在此擺攤。地上鋪著幾張草蓆﹐上面擺著獸皮、藥材、
山菌和野蜂蜜等山貨。雖然規模不大﹐但對於這個偏僻的小村子
來說﹐已經算是最熱鬧的地方了。
LONG
    );
    set("outdoors", "village");
    set("objects", ([
        __DIR__"npc/market_hawker" : 1,
    ]));
    set("detail", ([
        "草蓆" : "幾張破舊的草蓆鋪在地上﹐上面擺著各種山貨。\n",
        "獸皮" : "幾張粗製的獸皮﹐大概是附近獵戶打來的野物。\n",
    ]));
    set("exits", ([
        "west" : __DIR__"street2",
    ]));

    setup();
    replace_program(ROOM);
}
