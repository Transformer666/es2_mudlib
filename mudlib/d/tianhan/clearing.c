// Room: /d/tianhan/clearing.c

inherit ROOM;

void create()
{
    set("short", "村北空地");
    set("long", @LONG
村子北邊是一片空曠的平地，地上散落著一些木樁和稻草人，看來
是村民練武的場所。遠處可以看到連綿的山脈，山頂覆蓋著皚皚白雪。
一面破舊的旗幟插在空地中央，上面的字跡已經辨認不清。
LONG
    );
    set("outdoors", "village");
    set("detail", ([
        "木樁" : "幾根插在地上的木樁，上面佈滿了刀劍砍過的痕跡。\n",
        "稻草人" : "用舊衣服和稻草紮成的靶子，千瘡百孔。\n",
    ]));
    set("exits", ([
        "south" : __DIR__"street",
        "west" : __DIR__"cottage",
    ]));

    setup();
    replace_program(ROOM);
}
