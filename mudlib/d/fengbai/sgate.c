// Room: /d/fengbai/sgate.c

inherit ROOM;

void create()
{
    set("short", "楓柏村南口");
    set("long", @LONG
這裡是楓柏村的南口﹐兩棵巨大的楓樹像門神一樣立在路的兩側﹐
樹冠交疊形成了一座天然的拱門。地上鋪著青石板﹐倒比村裡的泥
路平整不少。一塊木牌上寫著「楓柏村」三個字﹐下面還刻了一行
小字﹕「往南通五堂﹐往北至黑風」。
LONG
    );
    set("outdoors", "village");
    set("detail", ([
        "木牌" : "一塊立在路邊的木牌﹐指示著前方道路的方向。\n",
        "楓樹" : "兩棵參天的老楓樹﹐樹幹粗壯﹐枝椏上掛滿了紅黃相間的楓葉。\n",
    ]));
    set("exits", ([
        "north" : __DIR__"street2",
        "south" : "/d/road/fengbai_road",
    ]));

    setup();
    replace_program(ROOM);
}
