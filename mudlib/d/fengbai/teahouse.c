// Room: /d/fengbai/teahouse.c

inherit ROOM;

void create()
{
    set("short", "楓柏茶棚");
    set("long", @LONG
路邊搭了一個簡單的茶棚﹐幾根竹竿撐起一塊粗布遮陽。棚下
擺著兩張竹桌﹐桌上放著粗陶的茶壺和茶碗。一位老婆婆守著
一個燒水的爐子﹐專門招待過路的行人。茶雖然只是山裡常見的
野茶﹐但勝在清香爽口﹐一碗下去滿身的疲累都消散了不少。
LONG
    );
    set("outdoors", "village");
    set("objects", ([
        __DIR__"npc/tea_granny" : 1,
    ]));
    set("detail", ([
        "爐子" : "一個簡陋的泥爐﹐上面坐著一把燻得發黑的銅壺﹐壺嘴正冒著白氣。\n",
        "茶碗" : "粗陶燒製的茶碗﹐碗沿有幾道缺口﹐但洗得很乾淨。\n",
    ]));
    set("exits", ([
        "east" : __DIR__"street1",
    ]));

    setup();
    replace_program(ROOM);
}
