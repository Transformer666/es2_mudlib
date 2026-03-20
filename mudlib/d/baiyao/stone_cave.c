// Room: /d/baiyao/stone_cave.c

inherit ROOM;

void create()
{
    set("short", "石洞");
    set("long", @LONG
穿過瀑布後，是一個寬敞的天然石洞。洞壁上生長著發光的苔蘚，
散發出幽幽的綠光，照亮了整個洞穴。洞中央有一個天然的石臺，石臺
上擺放著幾個石碗和一些乾枯的藥草殘渣。洞穴深處傳來一股灼熱的
氣息，彷彿有什麼強大的生物潛伏在更深處。
LONG
    );
    set("detail", ([
        "石臺" : "天然形成的石臺，表面異常光滑，上面有煉藥的痕跡。\n",
        "苔蘚" : "一種罕見的發光苔蘚，在黑暗中散發著幽綠色的光芒。\n",
    ]));
    set("exits", ([
        "east" : __DIR__"waterfall",
        "down" : __DIR__"deep_cave",
    ]));

    setup();
    replace_program(ROOM);
}
