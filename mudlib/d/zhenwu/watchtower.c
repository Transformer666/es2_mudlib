// vim: syntax=lpc
// Quest support: biyong_talisman - search tower to find lost talisman

inherit ROOM;

int do_search(string arg);

void create()
{
    set("short", "瞭望塔");
    set("long", @LONG
軍營大門東側的一座瞭望塔，以粗壯的木柱搭建，高約三丈有餘。
塔頂搭著一個簡易的棚子，擋風遮雨。站在塔上可以遠眺營外的官道和
周圍的山嶺，任何風吹草動都逃不過哨兵的眼睛。塔邊架著一面牛皮大
鼓，一旦發現異狀便擂鼓示警。
LONG
    );
    set("detail", ([
        "大鼓" : "一面碩大的牛皮鼓﹐鼓面繃得緊緊的﹐鼓槌放在一旁。這是示警用的戰鼓。\n",
        "柱子" : "粗壯的木柱支撐著整座瞭望塔﹐柱身上有不少刀刻的記號﹐大概是哨兵無聊時刻下的。\n",
        "縫隙" : "木板之間有不少縫隙﹐風大的時候呼呼作響。\n",
    ]));
    set("exits", ([
        "east" : __DIR__"gate",
    ]));
    set("objects", ([
        __DIR__"npc/sentry" : 1,
    ]));

    setup();
}

void init()
{
    ::init();
    add_action("do_search", "search");
}

int do_search(string arg)
{
    object player, talisman;

    player = this_player();
    if( !player ) return 0;

    if( !arg || (strsrch(arg, "縫隙") < 0 && strsrch(arg, "crack") < 0
    &&  strsrch(arg, "塔") < 0 && strsrch(arg, "tower") < 0
    &&  strsrch(arg, "木板") < 0 && strsrch(arg, "兵符") < 0) )
        return notify_fail("你想搜尋什麼﹖\n");

    if( player->query("quest/biyong_talisman_done") ) {
        write("瞭望塔上已經沒什麼特別的東西了。\n");
        return 1;
    }

    if( !player->query_temp("pending/biyong_talisman") ) {
        write("你四處看了看﹐除了遠處的風景﹐沒發現什麼特別的。\n");
        return 1;
    }

    if( present("military_talisman", player) ) {
        write("你已經找到兵符了﹐趕快帶回去給必勇吧。\n");
        return 1;
    }

    message_vision(
        "$N蹲下身子﹐仔細檢查著瞭望塔的木板縫隙。\n",
        player);

    write(
        "你趴在地上﹐沿著木板間的縫隙一寸一寸地摸索。在靠近鼓架\n"
        "的角落﹐你發現一塊木板翹起了一角﹐縫隙裡隱約閃著銅光。\n"
        "你伸手進去一摸﹐果然觸到了一塊冰涼的金屬。用力一拔﹐一\n"
        "塊半虎形的銅製兵符從縫隙中滑了出來﹐上面刻著「振武」二字。\n");
    message("vision",
        "$N從木板縫隙中摸出了一塊銅製的兵符。\n",
        environment(player), ({player}));

    talisman = new(__DIR__"npc/obj/military_talisman");
    if( talisman ) talisman->move(player);

    tell_object(player, "( 你獲得了一塊兵符 )\n");
    return 1;
}
