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
    set("exits", ([
        "west" : __DIR__"valley_path",
    ]));

    setup();
}

void init()
{
    ::init();
    add_action("do_pick", "pick");
    add_action("do_pick", "take");
}

int do_pick(string arg)
{
    object guardian;

    if( !arg ) return 0;
    if( strsrch(arg, "靈芝") < 0 && strsrch(arg, "藥") < 0
    &&  strsrch(arg, "herb") < 0 && strsrch(arg, "雪蓮") < 0
    &&  strsrch(arg, "何首烏") < 0 )
        return 0;

    // 如果守衛已經存在，不再生成
    if( present("herb_guardian", this_object()) ) {
        write("草藥守衛正守在那裡，你根本無法靠近藥圃。\n");
        return 1;
    }

    write("你剛伸手想採摘藥材，忽然腳下的藤蔓猛地扭動起來！\n");
    say(this_player()->query("name") + "伸手去採藥材，突然藤蔓竄動起來！\n");

    guardian = new(__DIR__"npc/herb_guardian");
    if( guardian ) {
        guardian->move(this_object());
        tell_room(this_object(),
            "一團藤蔓和草藥纏繞在一起，化為一個人形生物，忠實地守護著藥圃！\n");
    }
    return 1;
}
