// Room: /d/shuilan/inn_hall.c

#include <room.h>

inherit INN;

void create()
{
    set("short", "臨水客棧");
    set("long", @LONG
這裡是臨水客棧的大廳﹐因為靠近羿水渡口﹐生意還算不錯。大
廳裡擺著十幾張桌椅﹐靠窗的位子可以透過薄霧隱約看到遠處的
水面。掌櫃是個精明的婦人﹐操著一口南方口音﹐手腳麻利地招呼
著客人。牆上掛著一塊匾額﹐上書「臨水客棧」四個大字。
LONG
    );
    set("objects", ([
        __DIR__"npc/innkeeper" : 1,
    ]));
    set("valid_startroom", 1);
    set("no_fight", 1);
    set("detail", ([
        "匾額" : "一塊木製的匾額﹐上面的字是用金漆寫的﹐雖然有些剝落﹐但仍然看得出當年的氣派。\n",
    ]));
    set("exits", ([
        "east" : __DIR__"square",
    ]));

    setup();
}
