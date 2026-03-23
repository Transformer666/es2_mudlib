#include <room.h>

inherit TEMPLE;

void create()
{
    set("short", "城隍廟");
    set("long", @LONG
一座不大的城隍廟﹐廟門上方掛著「城隍廟」三個金字匾額。廟中
供奉著一尊城隍爺的石像﹐面容肅穆﹐手持笏板。石像前擺著一個大銅
香爐﹐爐中香煙繚繞﹐顯然平日香火不斷。
LONG
    );
    set("no_fight", 1);
    set("exits", ([
        "west" : __DIR__"square",
    ]));

    setup();
    replace_program(TEMPLE);
}
