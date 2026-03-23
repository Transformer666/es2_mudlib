// Room: /d/jingji/garden.c
// Quest: 師爺的懸案 — search pavilion to find missing ledger page

inherit ROOM;

void create()
{
    set("short", "御花園");
    set("long", @LONG
衙門後方的一座精緻花園，園中亭台樓閣錯落有致，假山流水相映
成趣。花圃裡種植著各色牡丹和芍藥，開得嬌豔欲滴。一條鋪著鵝卵
石的小徑蜿蜒穿過一片修竹林，通往園中的涼亭。涼亭下擺著石桌石凳
，是官員們公務之餘品茶賞花之所。
LONG
    );
    set("detail", ([
        "涼亭" : "涼亭的飛簷翹角十分精美﹐石桌上還留著茶漬。仔細看去﹐石凳下面似乎有什麼東西。也許可以 search 涼亭。\n",
        "假山" : "假山由太湖石堆砌而成﹐造型奇特﹐山間有細流淙淙而下。\n",
        "花圃" : "各色牡丹和芍藥爭奇鬥豔﹐香氣撲鼻。\n",
    ]));
    set("exits", ([
        "west" : __DIR__"yamen",
    ]));
    set("no_fight", 1);

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

    if( !arg || (arg != "涼亭" && arg != "pavilion" && arg != "亭") )
        return 0;

    player = this_player();

    if( player->query("quest/jingji_ledger_done") ) {
        write("你仔細搜索了涼亭四周﹐但沒有發現什麼。\n");
        return 1;
    }

    if( !player->query_temp("pending/jingji_ledger") ) {
        write("涼亭下的石桌石凳﹐看起來沒什麼特別的。\n");
        return 1;
    }

    if( player->query_temp("pending/jingji_ledger") >= 2 ) {
        write("你已經找到帳冊殘頁了﹐該回去告訴師爺。\n");
        return 1;
    }

    message_vision("$N彎下腰﹐在涼亭的石凳石桌之間仔細搜索。\n", player);
    write(
        "你翻看了石桌石凳的每個角落﹐忽然注意到一張石凳的底部有個\n"
        "淺淺的凹槽。你伸手摸進去﹐觸到一張被折疊的紙張。\n"
        "\n"
        "小心翼翼地展開﹐只見上面密密麻麻地寫滿了數字和名目﹐正是\n"
        "一頁帳冊的殘頁。上面記載著「三月稅銀入庫﹕紋銀三千二百兩」﹐\n"
        "但旁邊用硃砂筆改為「二千四百兩」﹐差額整整八百兩﹗\n"
        "\n"
        "這就是師爺要找的證據﹗應該趕快拿回去給他看。\n");
    message("vision",
        player->name() + "從石凳底下翻出了什麼東西﹗\n",
        environment(), player);

    player->set_temp("pending/jingji_ledger", 2);

    return 1;
}
