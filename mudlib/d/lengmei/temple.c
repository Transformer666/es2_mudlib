#include <room.h>

inherit TEMPLE;

void create()
{
    set("short", "城隍廟");
    set("long", @LONG
一座小小的城隍廟﹐雖然規模不大﹐但香火卻頗為旺盛。廟中供奉著
一尊城隍爺的泥塑像﹐神態威嚴。案前擺放著一個銅香爐﹐裡面插滿了
香﹐青煙裊裊升起。牆上還掛著幾塊「有求必應」的匾額。
LONG
    );
    set("no_fight", 1);
    set("exits", ([
        "north" : __DIR__"square",
    ]));

    setup();
    replace_program(TEMPLE);
}
