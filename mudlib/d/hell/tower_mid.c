// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "地氣塔中層");
    set("long", @LONG
沿著石階盤旋而上﹐來到了地氣塔的中層。塔內的空間比想像中
要寬敞﹐四面牆壁上嵌著巨大的玄鐵鏡﹐鏡面漆黑如墨﹐隱約可以
看到一些模糊的影像在鏡中飄動。塔中央有一根粗大的石柱﹐石柱上
纏繞著數條鐵鏈﹐鐵鏈的另一端嵌入四面牆壁之中﹐似乎在鎖住什
麼東西。地氣在塔內凝聚翻湧﹐令人感到一股無形的壓迫。
LONG
    );
    set("detail", ([
        "玄鐵鏡" : "黑色的鏡面深不見底﹐偶爾會浮現出一些模糊的人影和場景﹐轉瞬即逝。\n",
        "鐵鏈" : "粗大的鐵鏈繃得極緊﹐隱隱傳來嗡嗡的震動聲﹐彷彿承受著巨大的力量。\n",
    ]));
    set("objects", ([
        __DIR__"npc/tower_guard" : 2,
    ]));
    set("exits", ([
        "down" : __DIR__"tower_base",
        "up"   : __DIR__"tower_top",
    ]));

    setup();
    replace_program(ROOM);
}
