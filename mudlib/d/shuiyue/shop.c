// Room: /d/shuiyue/shop.c

inherit ROOM;

void create()
{
    set("short", "水月村雜貨鋪");
    set("long", @LONG
一間竹籬圍成的小鋪子﹐門口掛著一塊寫著「百物齋」的木牌。
鋪子裡擺著幾個竹製貨架﹐上面整齊地放著各種日用雜貨和乾糧。
角落裡堆著幾袋米糧﹐一股淡淡的草藥香味瀰漫在空氣中。掌櫃
是個勤快的中年人﹐正忙著整理貨物。
LONG
    );
    set("objects", ([
        __DIR__"npc/shopkeeper" : 1,
    ]));
    set("exits", ([
        "east" : __DIR__"street1",
    ]));

    setup();
    replace_program(ROOM);
}
