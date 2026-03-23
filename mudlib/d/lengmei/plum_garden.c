// Room: /d/lengmei/plum_garden.c
// Quest: 梅園夜影 — search footprints to find hidden letter

inherit ROOM;

void create()
{
    set("short", "梅園");
    set("long", @LONG
梅園中種滿了各種品種的梅花﹐紅梅、白梅、綠梅交相輝映。園中
有一塊平整的空地﹐看痕跡是莊中弟子常常在此對練劍法的場所。
仔細看去﹐空地邊緣的泥土上似乎有一些凌亂的腳印。
LONG
    );
    set("detail", ([
        "腳印" : "地上的腳印大小不一﹐其中有一串較新的腳印從園牆方向延伸到空地中央﹐在一塊大石旁消失了。也許可以 search 腳印。\n",
        "大石" : "一塊青灰色的大石﹐表面長滿了苔蘚。\n",
        "梅花" : "各色梅花在枝頭綻放﹐暗香浮動。\n",
    ]));
    set("exits", ([
        "west" : __DIR__"yard",
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
    object player;

    if( !arg || (arg != "腳印" && arg != "footprint" && arg != "footprints") )
        return 0;

    player = this_player();

    if( player->query("quest/lengmei_garden_done") ) {
        write("你仔細搜索了一遍﹐但已經沒有什麼新發現了。\n");
        return 1;
    }

    if( !player->query_temp("pending/lengmei_garden") ) {
        write("你注意到一些凌亂的腳印﹐但不確定該怎麼辦。也許該找人問問。\n");
        return 1;
    }

    if( player->query_temp("pending/lengmei_garden") >= 2 ) {
        write("你已經搜索過了﹐該回去告訴莊丁你的發現。\n");
        return 1;
    }

    message_vision("$N蹲下身子﹐沿著腳印仔細搜索。\n", player);
    write(
        "你順著腳印追蹤到那塊大石旁﹐發現石頭底部的泥土被翻動過。\n"
        "你費力地搬開大石的一角﹐在下面發現了一封用油紙包好的信。\n"
        "\n"
        "信上寫著﹕「師兄﹐寒梅劍的位置已經確認﹐就在大廳西側的\n"
        "暗格中。下次月黑風高之夜﹐我從梅園翻牆進入﹐你在外面接應。\n"
        "此事萬不可走漏風聲。」\n"
        "\n"
        "看來有人密謀盜取莊中的寒梅劍﹗應該趕快回去告訴莊丁。\n");
    message("vision",
        player->name() + "在大石下面發現了什麼東西﹗\n",
        environment(), player);

    player->set_temp("pending/lengmei_garden", 2);

    return 1;
}
