// Room: /d/baiyao/deep_cave.c

inherit ROOM;

void create()
{
    set("short", "石洞深處");
    set("long", @LONG
石洞深處是一個巨大的地下洞穴，洞穴中央有一個血紅色的深潭，
潭水散發著灼熱的蒸氣和刺鼻的硫磺味。洞壁上佈滿了巨大的爪痕，
深達數寸，不知是何等兇猛的生物留下的。空氣中瀰漫著一股令人窒息
的龍氣，令人不寒而慄。
LONG
    );
    set("detail", ([
        "血潭" : "潭水呈暗紅色，不斷冒著熱氣泡，溫度極高。\n",
        "爪痕" : "巨大的爪痕深深嵌入岩壁，每道痕跡都有手臂粗細。\n",
    ]));
    set("objects", ([
        __DIR__"npc/chilong" : 1,
    ]));
    set("exits", ([
        "up" : __DIR__"stone_cave",
    ]));

    setup();
    replace_program(ROOM);
}
