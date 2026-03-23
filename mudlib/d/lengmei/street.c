inherit ROOM;

void create()
{
    set("short", "梅林村落");
    set("long", @LONG
梅林小路在這裡稍微開闊了一些﹐路旁散落著幾戶人家﹐形成了一個
小小的村落。村民們大多是冷梅莊的佃戶和僕從﹐平日裡以務農為生。
往東走是冷梅莊的大門﹐南邊有一個小廣場。
LONG
    );
    set("outdoors", "snow");
    set("exits", ([
        "west"  : __DIR__"road",
        "east"  : __DIR__"gate",
        "south" : __DIR__"square",
    ]));

    setup();
    replace_program(ROOM);
}
