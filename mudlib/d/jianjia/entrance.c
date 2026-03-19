inherit ROOM;

void create()
{
    set("short", "劍甲門入口");
    set("long", @LONG
鐵匠鋪的後面隱藏著一道暗門﹐穿過暗門便來到劍甲門的地盤。這
裡彌漫著鐵水的灼熱氣息﹐不時傳來叮叮噹噹的打鐵聲。
LONG
    );
    set("exits", ([
        "west" : "/d/wutang/smithy",
        "east" : __DIR__"hall",
    ]));

    setup();
    replace_program(ROOM);
}
