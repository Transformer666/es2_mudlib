// Room: /d/fengcheng/inn_hall.c

#include <room.h>

inherit INN;

void create()
{
    set("short", "朔風客棧");
    set("long", @LONG
這裡是朔風客棧的大廳﹐一進門便感到一股暖意撲面而來﹐大廳
中央燒著一個大火盆﹐把寒氣驅散得乾乾淨淨。廳裡擺著十來張桌
椅﹐不少旅人圍坐在火盆旁取暖喝酒。靠北牆有一道樓梯通往二樓
客房﹐櫃臺就在樓梯旁邊。門楣上掛著一塊招牌﹐上書「朔風客棧」。
LONG
    );
    set("objects", ([
        __DIR__"npc/innkeeper" : 1,
    ]));
    set("valid_startroom", 1);
    set("no_fight", 1);
    set("detail", ([
        "火盆" : "一個碩大的銅火盆﹐裡面燃燒著炭火﹐散發出陣陣暖意﹐在風城這種寒冷的地方﹐火盆可是必不可少的。\n",
        "櫃臺" : "櫃臺後面擺滿了酒罈﹐多半是北地特有的烈酒﹐據說能驅寒暖身。\n",
    ]));
    set("exits", ([
        "east" : __DIR__"square",
    ]));

    setup();
}
