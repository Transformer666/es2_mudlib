// Room: /d/fengbai/shop.c

inherit ROOM;

void create()
{
    set("short", "楓柏村雜貨鋪");
    set("long", @LONG
一間簡陋的雜貨鋪子﹐門前掛著一塊褪了色的招牌。鋪子裡堆滿
了各式各樣的日用雜貨﹐從油鹽醬醋到草繩竹簍﹐應有盡有。一股
淡淡的藥材味道從櫃台後面飄來﹐看來掌櫃還兼賣些山裡採來的草
藥。
LONG
    );
    set("objects", ([
        __DIR__"npc/merchant" : 1,
    ]));
    set("detail", ([
        "招牌" : "一塊木頭招牌﹐上面歪歪斜斜地寫著「楓柏雜貨」四個字﹐漆色已經斑駁了。\n",
        "櫃台" : "一張粗糙的木頭櫃台﹐上面擺著幾個裝著藥材的竹簍。\n",
    ]));
    set("exits", ([
        "west" : __DIR__"street1",
    ]));

    setup();
    replace_program(ROOM);
}
