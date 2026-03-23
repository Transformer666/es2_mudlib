// Room: /d/shuiyue/inn_hall.c

#include <room.h>

inherit INN;

void create()
{
    set("short", "水月小棧");
    set("long", @LONG
這裡是水月村裡唯一的一間小客棧﹐規模不大﹐只有幾張桌椅﹐
但收拾得頗為整潔。牆上掛著幾幅山水畫﹐靠窗的位子可以望見窗
外的竹林和小溪﹐倒也別有一番情趣。掌櫃是個和藹的老婦人﹐手
藝不錯﹐做得一手好菜。
LONG
    );
    set("objects", ([
        __DIR__"npc/innkeeper" : 1,
    ]));
    set("valid_startroom", 1);
    set("no_fight", 1);
    set("detail", ([
        "山水畫" : "幾幅素雅的山水畫﹐畫的似乎就是水月村周圍的景色。\n",
    ]));
    set("exits", ([
        "west" : __DIR__"street1",
    ]));

    setup();
}
