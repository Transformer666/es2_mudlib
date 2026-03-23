// Room: /d/fengbai/temple.c

#include <room.h>

inherit TEMPLE;

void create()
{
    set("short", "楓柏村土地廟");
    set("long", @LONG
一座小小的土地廟﹐就建在一棵老楓樹下。廟裡只有一個簡陋的
神龕﹐裡面供著一尊小小的土地公神像。雖然廟宇簡陋﹐但從香爐
中裊裊的青煙可以看出﹐村民們對這位守護神十分虔誠。
LONG
    );
    set("detail", ([
        "神像" : "一尊小巧的土地公神像﹐木質的﹐雕工粗糙但看得出雕刻者的一番心意。\n",
        "香爐" : "一個陶製的小香爐﹐裡面插著幾柱燃了一半的線香。\n",
    ]));
    set("exits", ([
        "east" : __DIR__"square",
    ]));

    setup();
    replace_program(TEMPLE);
}
