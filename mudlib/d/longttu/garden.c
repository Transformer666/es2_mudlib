// vim: syntax=lpc
// Quest support: jiang_herb_debt (search well for purple_lingzhi)

inherit ROOM;

void create()
{
    set("short", "藥草園");
    set("long", @LONG
一片精心照料的藥草園﹐各種珍貴的藥草分區種植﹐標著名牌。靈
芝、人參、何首烏等名貴藥材在這裡都能見到。園中有一口石井﹐用來
灌溉藥草。井壁上長著一些青苔﹐隱約還有別的什麼東西。
LONG
    );
    set("detail", ([
        "石井" : "一口古老的石井﹐井壁上長滿了青苔﹐井水清澈見底。\n"
                 "仔細看去﹐井壁的陰暗處似乎長著一些特別的東西。\n",
        "藥草" : "各種珍貴藥材整齊排列﹐名牌標示清楚﹐照料得十分用心。\n",
    ]));
    set("exits", ([
        "west"  : __DIR__"hall",
        "east"  : __DIR__"lab",
        "north" : __DIR__"storehouse",
    ]));

    setup();
}

void init()
{
    add_action("do_search", "search");
}

int do_search(string arg)
{
    object player;

    player = this_player();
    if( !player ) return 0;

    if( !arg || (strsrch(arg, "石井") < 0 && strsrch(arg, "井") < 0
    &&  strsrch(arg, "well") < 0 && strsrch(arg, "井壁") < 0) )
        return notify_fail("你想搜尋什麼﹖\n");

    if( player->query("quest/jiang_herb_debt_done") ) {
        write("你已經採過紫靈芝了﹐井壁上暫時沒有新的。\n");
        return 1;
    }

    if( !player->query_temp("pending/jiang_herb_debt") ) {
        write("你探頭往井裡看了看﹐井壁上長著一些青苔﹐井水清澈。\n");
        return 1;
    }

    if( present("purple_lingzhi", player) ) {
        write("你已經採到紫靈芝了﹐趕緊拿去給江述仁吧。\n");
        return 1;
    }

    message_vision(
        "$N趴在井沿﹐小心翼翼地往井壁上張望。\n",
        player);

    write(
        "你探頭往井裡看去﹐井壁上長滿了青苔。\n"
        "忽然﹐你發現在陰暗的角落裡﹐有一株散發著淡淡紫光的靈芝﹗\n"
        "你伸手小心翼翼地將它摘了下來。\n");

    message("vision",
        this_player()->name() + "從井壁上摘下了一株發著紫光的靈芝。\n",
        environment(player), player);

    new(__DIR__"npc/obj/purple_lingzhi")->move(player);
    return 1;
}
