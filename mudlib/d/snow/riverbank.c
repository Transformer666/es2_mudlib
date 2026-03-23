// Room: /d/snow/riverbank.c
// Quest support: smith_black_iron (search/dig for black iron ore)

inherit ROOM;

int ore_found = 0;

void create()
{
    set("short", "河邊空地");
    set("long", @LONG
這裡是河邊的一處空地﹐湍急的河流從你的北邊往東南邊流去﹐離
這裡的河岸往北一丈多遠的地方可以看見一個水車﹐南邊則是一間破舊
的大宅院﹐牆壁上一個大缺口足足可以讓人通過。河岸的岩壁上露出
一些深色的礦石紋路。
LONG
    );
    set("outdoors", "snow");
    set("detail", ([
	"岩壁" : "河岸的岩壁經過長年河水沖刷﹐露出了一些深色的礦石紋路。\n",
	"礦石" : "仔細看﹐岩壁上有些深色的紋路和普通石頭不太一樣。\n",
    ]));
    set("exits", ([
	"south" : __DIR__"ruin2",
	"east"  : __DIR__"old_house",
    ]));

    setup();
}

void init()
{
    add_action("do_search", "search");
    add_action("do_dig", "dig");
}

int do_search(string arg)
{
    if( arg != "岩壁" && arg != "礦石" ) return 0;

    if( ore_found ) {
	message_vision("$N仔細端詳岩壁﹐但那些深色紋路只是普通的石頭。\n",
	    this_player());
	return 1;
    }

    if( !this_player()->query_temp("pending/smith_black_iron") ) {
	message_vision("$N隨意看了看河岸的岩壁﹐沒發現什麼特別的。\n",
	    this_player());
	return 1;
    }

    message_vision(
	"$N仔細端詳岩壁﹐發現有一處深色的礦脈看起來不太一樣。\n",
	this_player());
    tell_object(this_player(),
	"你可以試試用力把它挖(dig)下來。\n");
    this_player()->set_temp("pending/found_ore_vein", 1);
    return 1;
}

int do_dig(string arg)
{
    object ob;

    if( arg != "岩壁" && arg != "礦石" && arg != "礦脈" ) return 0;

    if( !this_player()->query_temp("pending/found_ore_vein") ) {
	message_vision("$N用力挖了挖﹐但什麼也沒挖到。\n",
	    this_player());
	return 1;
    }

    if( ore_found ) {
	message_vision("$N用力挖了半天﹐但是這裡的玄鐵已經被挖光了。\n",
	    this_player());
	return 1;
    }

    ore_found = 1;
    this_player()->delete_temp("pending/found_ore_vein");
    ob = new(__DIR__"npc/obj/black_iron");
    ob->move(this_player());
    message_vision(
	"$N費了好大力氣﹐終於從岩壁上鑿下了一塊烏黑發亮的礦石﹗\n",
	this_player());
    return 1;
}

void reset()
{
    ore_found = 0;
    ::reset();
}
