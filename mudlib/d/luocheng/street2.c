// Room: /d/luocheng/street2.c

inherit ROOM;

void create()
{
    set("short", "羅城東街");
    set("long", @LONG
這裡是羅城的東街﹐是通往東門的必經之路。街道兩旁多是貨棧
和倉庫﹐不時有搬運工人扛著沉重的貨物匆匆走過。靠南邊有一條
小巷通往集市﹐空氣中飄著各種乾貨的氣味。
LONG
    );
    set("outdoors", "town");
    set("exits", ([
        "west"  : __DIR__"store",
        "east"  : __DIR__"egate",
        "south" : __DIR__"market",
    ]));

    setup();
    replace_program(ROOM);
}
