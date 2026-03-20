// Room: /d/tianhan/well.c

inherit ROOM;

void create()
{
    set("short", "古井旁");
    set("long", @LONG
村子西邊有一口年代久遠的石砌古井，井口用一塊厚重的石板半掩
著，井沿上長滿了青苔。井邊立著一個木桶和一根粗麻繩，供村民打水
使用。旁邊有一棵枯了半邊的老柳樹，枝條在寒風中瑟瑟發抖。
LONG
    );
    set("outdoors", "village");
    set("detail", ([
        "古井" : "探頭往井裡看去，黑漆漆的什麼都看不見。\n",
        "木桶" : "一個用鐵箍箍住的木桶，看來還能用。\n",
        "柳樹" : "這棵柳樹枯了半邊，但另半邊居然還有些綠意。\n",
    ]));
    set("exits", ([
        "east" : __DIR__"street",
    ]));

    setup();
    replace_program(ROOM);
}
