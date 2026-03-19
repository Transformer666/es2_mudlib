inherit ROOM;

void create()
{
    set("short", "暗影庭院");
    set("long", @LONG
庭院四周種滿了高大的黑松﹐遮擋了大部分的陽光﹐即使在白天也
顯得陰暗幽冷。庭院中央立著一座黑色的石碑﹐上面刻著天邪派的門規
戒律。幾名黑衣弟子在庭院中默默練功。
LONG
    );
    set("objects", ([
        __DIR__"npc/disciple" : 2,
    ]));
    set("exits", ([
        "south" : __DIR__"gate",
        "north" : __DIR__"hall",
        "east"  : __DIR__"training",
    ]));

    setup();
    replace_program(ROOM);
}
