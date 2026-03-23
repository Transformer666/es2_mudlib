// Room: /d/wutang/wushan_path2.c
// Quest support: haidafu_herb (search for golden_herb)

inherit ROOM;

int herb_found = 0;

void create()
{
    set("short", "武山山徑");
    set("long", @LONG
山路更加陡峭了﹐有些地方甚至需要手腳並用才能攀爬。透過樹
木的間隙﹐可以看到山下五堂鎮的全景﹐房屋鱗次櫛比﹐河流如帶
般蜿蜒而過。路旁的岩縫和潮濕的陰影處長著一些不知名的野草。
LONG
    );
    set("detail", ([
	"野草" : "岩縫中長著一些不知名的野草﹐仔細看看也許能找到什麼有用的藥材。\n",
	"岩縫" : "潮濕的岩縫中似乎適合某些珍貴藥草生長。\n",
    ]));
    set("exits", ([
	"down" : __DIR__"wushan_path1",
	"up" : __DIR__"wushan_path3",
    ]));

    setup();
}

void init()
{
    add_action("do_search", "search");
}

int do_search(string arg)
{
    if( arg != "野草" && arg != "草叢" && arg != "岩縫" && arg != "藥草" )
	return 0;

    if( herb_found ) {
	message_vision("$N在路邊仔細搜尋﹐但是什麼也沒有找到。\n",
	    this_player());
	return 1;
    }

    if( !this_player()->query_temp("pending/haidafu_herb") ) {
	message_vision("$N在路邊隨手翻找了一下﹐只看到一些普通的雜草。\n",
	    this_player());
	return 1;
    }

    herb_found = 1;
    object ob = new(__DIR__"npc/obj/golden_herb");
    ob->move(this_player());
    message_vision(
	"$N在岩縫中仔細搜尋﹐竟然發現了一株金線蓮﹗\n",
	this_player());
    return 1;
}

void reset()
{
    herb_found = 0;
    ::reset();
}
