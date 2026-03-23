// Room: /d/fengbai/inn_hall.c

#include <room.h>

inherit INN;

void create()
{
    set("short", "楓林小棧");
    set("long", @LONG
這裡是楓林小棧﹐楓柏村裡唯一的客棧。客棧很小﹐只有幾張
桌椅﹐但收拾得頗為整潔。牆角放著一個水缸﹐窗外就是一片楓林﹐
秋天的時候﹐推窗便能看見滿山的紅葉。掌櫃是個老實巴交的莊稼
漢﹐兼著做些客棧的生意﹐補貼家用。
LONG
    );
    set("objects", ([
        __DIR__"npc/innkeeper" : 1,
    ]));
    set("valid_startroom", 1);
    set("no_fight", 1);
    set("detail", ([
        "楓林" : "窗外一片楓林﹐微風吹過﹐楓葉沙沙作響﹐倒也別有一番意境。\n",
    ]));
    set("exits", ([
        "west" : __DIR__"square",
    ]));

    setup();
}
