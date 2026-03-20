// Room: /d/babao/floor1.c

inherit ROOM;

void create()
{
    set("short", "八寶樓一樓 - 歐陽書屋");
    set("long", @LONG
八寶樓的第一層是一間寬敞的書房，四壁書架上堆滿了各種典籍和
卷軸。書桌上攤著一本翻開的兵書，旁邊放著一盞快要燃盡的油燈。這
裡的主人是「神算無疑」歐陽芝，大漠八魔之一，據說他的棋藝和算術
冠絕天下，但為人自視極高。
LONG
    );
    set("objects", ([
        "/d/wutang/npc/ouyang_zhi" : 1,
    ]));
    set("detail", ([
        "書架" : "書架上擺滿了各種兵書、棋譜和算經。\n",
        "兵書" : "翻開的一頁上畫著複雜的陣法圖解。\n",
    ]));
    set("exits", ([
        "down" : __DIR__"hall",
        "up" : __DIR__"floor2",
    ]));

    setup();
    replace_program(ROOM);
}
