#include <room.h>

inherit INN;

private void create()
{
    set("short", "雪吟客棧");
    set("long", @LONG
一間樸實的客棧﹐門口掛著一面酒旗﹐上書「雪吟客棧」。大廳裡
擺放著幾張方桌和長凳﹐牆角放著一個大酒缸。雖然裝潢簡單﹐卻打
掃得十分乾淨﹐看得出掌櫃是個勤快人。
LONG
    );
    set("valid_startroom", 1);
    set("no_fight", 1);
    set("objects", ([
        __DIR__"npc/innkeeper" : 1,
    ]));
    set("exits", ([
        "west" : __DIR__"street",
    ]));

    setup();
}
