inherit ROOM;

void create()
{
    set("short", "天邪大殿");
    set("long", @LONG
天邪大殿陰暗寬敞﹐殿中燃著幾盞幽綠色的長明燈﹐將四壁映得忽
明忽暗。正面的高台上擺著一把黑鐵交椅﹐椅背上雕著一隻展翅的蝙蝠
。兩側掛著黑色的幔帳﹐隱約可見帳後有暗門通往後殿。
LONG
    );
    set("objects", ([
        __DIR__"npc/master" : 1,
        __DIR__"npc/shadow_guard" : 1,
    ]));
    set("exits", ([
        "south" : __DIR__"yard",
        "west"  : __DIR__"quarters",
    ]));

    setup();
    replace_program(ROOM);
}
