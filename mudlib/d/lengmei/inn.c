#include <room.h>

inherit INN;

private void create()
{
    set("short", "寒梅客棧");
    set("long", @LONG
一間不大的客棧﹐佈置得乾淨素雅。牆上掛著幾幅梅花水墨畫﹐桌
椅雖然簡樸卻收拾得一塵不染。櫃臺後面的架子上擺放著幾壇自釀的
梅花酒﹐淡淡的酒香瀰漫在空氣中。
LONG
    );
    set("valid_startroom", 1);
    set("no_fight", 1);
    set("objects", ([
        __DIR__"npc/innkeeper" : 1,
    ]));
    set("exits", ([
        "east" : __DIR__"square",
    ]));

    setup();
}
