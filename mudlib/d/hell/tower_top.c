// vim: syntax=lpc
// Room: /d/hell/tower_top.c
// Quest: 地靈封印 (diling_summon) - 地獄塔頂版
// diling 透過法陣觸發召喚，不常駐房間

inherit ROOM;

void summon_diling(object player);

void create()
{
    set("short", "地氣塔頂");
    set("long", @LONG
地氣塔的最頂層﹐一個圓形的石室﹐四面無牆﹐只有幾根石柱支
撐著穹頂。從這裡可以俯瞰整個陰間﹐灰濛濛的迷霧在腳下翻湧﹐
遠處隱約可見連綿的山巒和幽暗的河流。塔頂中央有一座石台﹐台上
嵌著一個圓形的凹槽﹐似乎可以放入什麼物品。石台四周的地面上刻
滿了複雜的法陣﹐隱隱散發著攝人的威壓。
LONG
    );
    set("detail", ([
        "石台" : "一座三尺高的石台﹐台面上嵌著一個拳頭大小的圓形凹槽﹐凹槽邊緣刻著精密的符文。\n",
        "法陣" : "地面上刻著的法陣極為複雜﹐由數十個同心圓和數百條線條交織而成﹐散發著幽暗的光芒。\n",
        "符文" : "凹槽邊緣的符文似乎與大地之力有關﹐也許將某種蘊含地氣的物品放入凹槽﹐便能啟動法陣。\n",
    ]));
    set("exits", ([
        "down" : __DIR__"tower_mid",
    ]));

    setup();
}

void init()
{
    add_action("do_place", "place");
    add_action("do_place", "put");
}

int do_place(string arg)
{
    object player, orb;

    player = this_player();
    if( !player ) return 0;

    if( !arg || (strsrch(arg, "內丹") < 0 && strsrch(arg, "orb") < 0
    &&  strsrch(arg, "earth") < 0 && strsrch(arg, "凹槽") < 0) )
        return 0;

    if( player->query("quest/diling_summon_done") ) {
        write("法陣已經失去了力量﹐地靈不會再出現了。\n");
        return 1;
    }

    if( player->query_temp("pending/diling_summon_fighting") ) {
        write("地靈正在肆虐﹐你還是先對付他吧！\n");
        return 1;
    }

    orb = present("earth_orb", player);
    if( !orb ) orb = present("orb", player);

    if( !orb ) {
        write("你身上沒有適合放入凹槽的東西。\n");
        return 1;
    }

    message_vision(
        "$N將蘊含地氣的寶珠放入石台的凹槽之中。\n"
        "法陣上的符文猛然亮起﹐一道道褐黃色的光芒從地面湧出﹗\n",
        player);

    destruct(orb);

    message("vision",
        "整座塔頂劇烈震動﹐石柱上的灰塵簌簌落下﹗\n"
        "一股沉重而古老的力量從法陣中心爆發﹐\n"
        "大地的怒吼在陰間的虛空中迴盪！\n",
        environment(player));

    player->set_temp("pending/diling_summon_fighting", 1);
    call_out("summon_diling", 3, player);
    return 1;
}

void summon_diling(object player)
{
    object diling, env;

    if( !player ) return;
    env = environment(player);
    if( !env || base_name(env) != __DIR__"tower_top" ) return;

    diling = new(__DIR__"npc/diling");
    if( !diling ) return;
    diling->move(env);

    message("vision",
        "褐黃色光柱凝聚成一個高大威猛的人形﹐地靈從法陣中緩緩現身。\n"
        "他的身軀如同岩石一般堅硬﹐腳下的石板隨著他的每一步而龜裂。\n"
        "地靈沉聲道﹕竟有人在此地喚醒本靈﹐你們這些凡人 ... 找死！\n",
        env);
}
