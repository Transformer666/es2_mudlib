// Room: /d/baiyao/entrance.c

inherit ROOM;

void create()
{
    set("short", "百藥谷入口");
    set("long", @LONG
一條隱蔽的山間小徑通往一個幽深的峽谷，谷口兩側的岩壁上長
滿了各種藥草，散發著一股清苦的藥香。一塊天然的巨石橫亙在谷口，
上面用硃砂寫著「百藥谷」三個大字，字跡蒼勁有力。谷中霧氣繚繞，
隱約可以聽到流水的聲音。
LONG
    );
    set("outdoors", "mountain");
    set("detail", ([
        "巨石" : "巨石上的硃砂字跡雖然歷經風雨，卻依然鮮紅如血。\n",
        "藥草" : "岩壁上生長著各種叫不出名字的草藥，散發著苦澀的氣味。\n",
    ]));
    set("exits", ([
        "northwest" : "/d/road/mountain_road1",
        "south" : __DIR__"valley_path",
    ]));

    setup();
    replace_program(ROOM);
}
