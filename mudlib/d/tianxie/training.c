inherit ROOM;

void create()
{
    set("short", "暗殺練功場");
    set("long", @LONG
練功場中擺放著各種用於暗殺訓練的器械﹐牆上掛著人形靶﹐上面
插滿了飛刀和暗器。地面上畫著各種步法的軌跡﹐幾名弟子正在反覆練
習身法和暗器手法﹐動作迅捷無聲。
LONG
    );
    set("objects", ([
        __DIR__"npc/evil_daoist" : 1,
    ]));
    set("exits", ([
        "west" : __DIR__"yard",
    ]));

    setup();
    replace_program(ROOM);
}
