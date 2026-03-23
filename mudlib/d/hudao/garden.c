// vim: syntax=lpc
// Quest support: elder_well_blade - search well to find hidden blade

inherit ROOM;

int do_search(string arg);

void create()
{
    set("short", "後院");
    set("long", @LONG
內堂後方的一片小院落，院中種著幾棵枝幹粗壯的老榕樹，樹蔭
下擺著石桌石凳。院牆邊整齊地插著一排練功用的木刀，刀柄上磨出了
光亮的手印。角落裡有一口古井，井水清冽甘甜。這裡是虎刀門長輩們
閒暇時品茶論刀的所在。
LONG
    );
    set("detail", ([
        "古井" : "一口石砌的古井﹐井壁上長滿了青苔﹐井水深不見底。井沿上有不少刀痕﹐看來常有人在井邊練刀。\n",
        "木刀" : "一排木製練功刀﹐刀身磨得光滑﹐每一把都有數不清的劈砍痕跡。\n",
        "石桌" : "一張厚重的石桌﹐桌面上刻著棋盤﹐旁邊散落著幾顆黑白棋子。\n",
    ]));
    set("exits", ([
        "south" : __DIR__"inner_hall",
    ]));

    set("objects", ([ __DIR__"npc/elder" : 1 ]));
    setup();
}

void init()
{
    ::init();
    add_action("do_search", "search");
}

int do_search(string arg)
{
    object player, blade;

    player = this_player();
    if( !player ) return 0;

    if( !arg || (strsrch(arg, "井") < 0 && strsrch(arg, "well") < 0) )
        return notify_fail("你想搜尋什麼﹖\n");

    if( player->query("quest/elder_well_blade_done") ) {
        write("古井裡已經沒什麼特別的東西了。\n");
        return 1;
    }

    if( !player->query_temp("pending/elder_well_blade") ) {
        write("你探頭往井裡看了看﹐井水很深﹐看不到什麼特別的。\n");
        return 1;
    }

    if( present("old_blade", player) ) {
        write("你已經找到虎紋斷刀了﹐帶去給長老看看吧。\n");
        return 1;
    }

    message_vision(
        "$N趴在井沿上﹐伸手往井壁上摸索。\n",
        player);

    write(
        "你沿著井壁仔細摸索﹐在水面以下約一尺的地方﹐手指觸到了\n"
        "一塊突出的石磚。你用力一扳﹐石磚鬆動了﹐露出一個暗格。\n"
        "暗格裡塞著一個油布包裹﹐你小心翼翼地取了出來。\n"
        "打開油布﹐裡面是一把鏽跡斑斑的虎紋大刀﹐刀身已經斷了半截﹐\n"
        "但虎頭浮雕依然清晰可見。\n");
    message("vision",
        "$N從古井中取出了一個油布包裹﹐裡面似乎包著一把舊刀。\n",
        environment(player), ({player}));

    blade = new(__DIR__"npc/obj/old_blade");
    if( blade ) blade->move(player);

    tell_object(player, "( 你獲得了一把虎紋斷刀 )\n");
    return 1;
}
