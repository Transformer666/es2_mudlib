// vim: syntax=lpc
// Quest: 暗影試煉 (evil_daoist_trial)
// Flow: search room -> discover shadow presence -> evil_daoist appears to test player

inherit ROOM;

void spawn_daoist(object player);

void create()
{
    set("short", "暗殺練功場");
    set("long", @LONG
練功場中擺放著各種用於暗殺訓練的器械﹐牆上掛著人形靶﹐上面
插滿了飛刀和暗器。地面上畫著各種步法的軌跡﹐幾名弟子正在反覆練
習身法和暗器手法﹐動作迅捷無聲。角落裡的暗影似乎比別處更加濃重。
LONG
    );
    set("detail", ([
        "暗影" : "練功場角落裡的暗影濃重得不自然﹐仔細看去﹐似乎有什麼東西\n"
            "隱藏在其中﹐偶爾閃過一絲令人心悸的寒光。也許可以仔細搜索一下。\n",
        "人形靶" : "人形靶上插滿了各式暗器﹐看得出弟子們的訓練十分刻苦。\n",
        "步法" : "地面上的步法軌跡複雜精妙﹐是天邪派獨有的暗殺身法。\n",
    ]));
    set("exits", ([
        "west" : __DIR__"yard",
    ]));

    setup();
}

void init()
{
    add_action("do_search", "search");
    add_action("do_search", "搜索");
}

int do_search(string arg)
{
    object player;

    player = this_player();
    if( !player ) return 0;

    if( !arg || (strsrch(arg, "暗影") < 0 && strsrch(arg, "shadow") < 0
    &&  strsrch(arg, "角落") < 0 && strsrch(arg, "corner") < 0) )
        return notify_fail("搜索什麼？\n");

    if( player->query("quest/evil_daoist_trial_done") ) {
        write("暗影中已經沒有任何異常了﹐那股壓迫感早已消散。\n");
        return 1;
    }

    if( player->query_temp("pending/evil_daoist_trial") ) {
        write("暗影中的存在已經現身了！\n");
        return 1;
    }

    if( present("evil_daoist", environment(player)) ) {
        write("大邪道人已經在這裡了！\n");
        return 1;
    }

    message_vision(
        "$N小心翼翼地靠近練功場角落裡那片不自然的暗影。\n",
        player);

    player->set_temp("pending/evil_daoist_trial", 1);

    message("vision",
        "暗影中忽然傳出一聲低沉的冷笑﹐一股令人窒息的殺氣瞬間瀰漫開來。\n",
        environment(player));

    call_out("spawn_daoist", 3, player);
    return 1;
}

void spawn_daoist(object player)
{
    object daoist, env;

    if( !player ) return;
    env = environment(player);
    if( !env || base_name(env) != __DIR__"training" ) {
        if( player ) player->delete_temp("pending/evil_daoist_trial");
        return;
    }

    daoist = new(__DIR__"npc/evil_daoist");
    if( !daoist ) {
        player->delete_temp("pending/evil_daoist_trial");
        return;
    }
    daoist->move(env);

    message("vision",
        "暗影猛然凝聚﹐一個身穿黑色道袍的身影從黑暗中緩緩走出。\n"
        "他面容枯槁﹐雙目中閃爍著攝人的精光﹐周身散發著令人窒息的\n"
        "陰暗氣息——大邪道人竟然一直潛伏在此處！\n",
        env);
}
