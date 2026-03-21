// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "瞭望塔");
    set("long", @LONG
軍營大門東側的一座瞭望塔，以粗壯的木柱搭建，高約三丈有餘。
塔頂搭著一個簡易的棚子，擋風遮雨。站在塔上可以遠眺營外的官道和
周圍的山嶺，任何風吹草動都逃不過哨兵的眼睛。塔邊架著一面牛皮大
鼓，一旦發現異狀便擂鼓示警。
LONG
    );
    set("exits", ([
        "west" : __DIR__"gate",
        "east" : __DIR__"gate",
    ]));
    set("objects", ([
        __DIR__"npc/sentry" : 1,
    ]));

    setup();
}
