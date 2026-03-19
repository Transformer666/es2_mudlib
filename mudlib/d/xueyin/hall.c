inherit ROOM;

void create()
{
    set("short", "雪吟大廳");
    set("long", @LONG
雪吟大廳裝飾得莊嚴豪氣﹐正面牆上掛著一幅巨大的雪景圖﹐畫中
一人持劍立於雪峰之巔。兩側的兵器架上陳列著各式兵器﹐以劍為最多
。大廳中央擺放著一張巨大的虎皮交椅。
LONG
    );
    set("objects", ([
        __DIR__"npc/yutieshan" : 1,
    ]));
    set("exits", ([
        "south" : __DIR__"yard",
        "east"  : __DIR__"training",
        "west"  : __DIR__"quarters",
    ]));

    setup();
    replace_program(ROOM);
}
