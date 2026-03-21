// Room: /d/baiyao/herb_garden.c

inherit ROOM;

void create()
{
    set("short", "藥圃");
    set("long", @LONG
谷中一處平坦的空地上，有人精心開闢了一片藥圃。圃中種植著
各種名貴藥材，有靈芝、何首烏、天山雪蓮等，每一株都照料得十分
細心。藥圃旁邊搭著一個簡陋的草棚，裡面擺放著採藥的工具。看來
曾經有人在此隱居採藥。
LONG
    );
    set("outdoors", "mountain");
    set("detail", ([
        "靈芝" : "一株紫紅色的靈芝，傘蓋碩大，散發著淡淡的清香。\n",
        "草棚" : "草棚裡放著藥鋤、竹簍和一些曬乾的藥材。\n",
    ]));
    set("objects", ([
        __DIR__"npc/herb_guardian" : 1,
    ]));
    set("exits", ([
        "west" : __DIR__"valley_path",
    ]));

    setup();
    replace_program(ROOM);
}
