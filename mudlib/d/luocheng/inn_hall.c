// Room: /d/luocheng/inn_hall.c

#include <room.h>

inherit INN;

void create()
{
    set("short", "通寶客棧");
    set("long", @LONG
這裡是通寶客棧的大廳﹐羅城最大的客棧之一。大廳寬敞明亮﹐
擺放著二十多張桌椅﹐客人熙來攘往﹐生意興隆。靠牆的貨架上擺
著各種好酒﹐空氣中瀰漫著酒菜的香氣。掌櫃在櫃臺後忙碌地撥著
算盤﹐幾個夥計端著菜盤穿梭在桌椅之間。
LONG
    );
    set("objects", ([
        __DIR__"npc/innkeeper" : 1,
    ]));
    set("valid_startroom", 1);
    set("no_fight", 1);
    set("detail", ([
        "櫃臺" : "櫃臺上放著一本厚厚的賬簿﹐旁邊是一把算盤和幾串銅錢。\n",
        "貨架" : "貨架上擺滿了各種酒罈﹐有本地釀的米酒﹐也有從外地運來的名酒。\n",
    ]));
    set("exits", ([
        "west" : __DIR__"street1",
    ]));

    setup();
}
