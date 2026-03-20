// Room: /d/baiyao/waterfall.c

inherit ROOM;

void create()
{
    set("short", "瀑布前");
    set("long", @LONG
小徑盡頭是一道飛瀑，水流從數十丈高的崖壁上傾瀉而下，激起
漫天的水霧。瀑布下方是一個清澈見底的水潭，潭水碧綠如玉。瀑布
的轟鳴聲在峽谷中迴盪，震耳欲聾。仔細觀察，瀑布後面似乎隱約透
著一絲光亮，看來後面別有洞天。
LONG
    );
    set("outdoors", "mountain");
    set("detail", ([
        "瀑布" : "水流從高處傾瀉而下，水花四濺，蔚為壯觀。\n",
        "水潭" : "潭水清澈見底，可以看到水底的鵝卵石和游動的小魚。\n",
    ]));
    set("exits", ([
        "north" : __DIR__"valley_path",
        "west" : __DIR__"stone_cave",
    ]));

    setup();
    replace_program(ROOM);
}
