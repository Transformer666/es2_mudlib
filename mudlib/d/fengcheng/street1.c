// Room: /d/fengcheng/street1.c

inherit ROOM;

void create()
{
    set("short", "風城大街");
    set("long", @LONG
這裡是風城的主要街道﹐兩旁是各式各樣的商舖和民居。街道
用大塊的青石板鋪成﹐經過無數行人的踩踏已經變得光滑發亮。
北面通往廣場﹐南面則是通往城門的方向。街邊偶爾能看到幾個
來自天山各門派的武林人士﹐在此地補給歇息。
LONG
    );
    set("outdoors", "town");
    set("exits", ([
        "north" : __DIR__"square",
        "south" : __DIR__"sgate",
        "east"  : __DIR__"well",
    ]));

    setup();
    replace_program(ROOM);
}
