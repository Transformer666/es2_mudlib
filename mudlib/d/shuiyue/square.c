// Room: /d/shuiyue/square.c

inherit ROOM;

void create()
{
    set("short", "水月村口");
    set("long", @LONG
這裡是水月村的村口﹐一條清澈的小溪從村前緩緩流過﹐溪水倒
映著天光雲影﹐大概就是水月村得名的由來。村子不大﹐四周環繞著
翠綠的竹林﹐幾間茅屋錯落其間﹐炊煙裊裊﹐一派寧靜祥和的景象。
村口有一棵大柳樹﹐樹下放著幾塊青石供人歇腳。
LONG
    );
    set("objects", ([
        __DIR__"npc/villager" : 1,
    ]));
    set("detail", ([
        "小溪" : "一條清澈見底的小溪﹐溪水潺潺﹐幾尾小魚在水中自在地游來游去。\n",
        "柳樹" : "一棵老柳樹﹐柳條隨風輕擺﹐樹幹上刻著不少到此一遊的字跡。\n",
    ]));
    set("exits", ([
        "north" : __DIR__"temple",
        "south" : __DIR__"street1",
        "west"  : __DIR__"wgate",
        "east"  : __DIR__"egate",
    ]));

    setup();
    replace_program(ROOM);
}
