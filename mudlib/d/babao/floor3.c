// Room: /d/babao/floor3.c

inherit ROOM;

void create()
{
    set("short", "八寶樓三樓 - 鑄刀房");
    set("long", @LONG
第三層是一間灼熱的鑄刀房，中央架著一座巨大的熔爐，爐火通紅，
熱浪滾滾。四周的牆壁被烤得發黑，地上散落著各種打鐵的工具。鑄刀
房的主人崇白虎是夜叉族人，一生醉心於鍛造，據說他打出的兵器無不
鋒利無比。
LONG
    );
    set("objects", ([
        "/d/wutang/npc/chong_baihu" : 1,
    ]));
    set("detail", ([
        "熔爐" : "巨大的熔爐燒得通紅，爐口不時冒出幾朵火星。\n",
        "工具" : "地上散落著鐵鉗、鐵錘和各種鑄造工具。\n",
    ]));
    set("exits", ([
        "down" : __DIR__"floor2",
        "up" : __DIR__"floor4",
    ]));

    setup();
    replace_program(ROOM);
}
