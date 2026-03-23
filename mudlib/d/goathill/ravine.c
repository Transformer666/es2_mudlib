// vim: syntax=lpc
// Quest support: 隱士的棋局 - search ravine for chess piece

inherit ROOM;

void create()
{
	set("short", "羊山谷底");
	set("long", @LONG
這是懸崖下方的一處幽深谷底，陽光幾乎照不到這裡，四周都是高聳的岩壁。谷底長滿了蕨類植物和苔蘚，空氣潮濕而陰冷。一條細流從岩壁上滲出，匯聚成一個小水窪。
LONG
	);
	set("exits", ([
		"up" : __DIR__"cliff",
	]));
	set("detail", ([
		"水窪" : "一小窪積水﹐清澈見底﹐水底鋪著細碎的碎石和泥沙。\n",
		"蕨類" : "蕨類植物長得很茂密﹐在岩壁的陰影下隨風輕擺。\n",
	]));

	setup();
}

void init()
{
	add_action("do_search_ravine", "search");
	add_action("do_search_ravine", "找");
}

int do_search_ravine(string arg)
{
	object player, piece;

	player = this_player();
	if( !player ) return 0;

	if( !arg || (strsrch(arg, "水窪") < 0 && strsrch(arg, "谷") < 0
	&&  strsrch(arg, "地") < 0 && strsrch(arg, "ravine") < 0
	&&  strsrch(arg, "pool") < 0 && strsrch(arg, "棋") < 0) )
		return notify_fail("你想搜索什麼﹖\n");

	if( player->query("quest/hermit_chess_done") ) {
		write("你在谷底四處看了看﹐什麼也沒發現。\n");
		return 1;
	}

	if( !player->query_temp("pending/hermit_chess") ) {
		write("你在谷底翻找了一陣﹐除了碎石和苔蘚﹐什麼也沒找到。\n");
		return 1;
	}

	if( player->query_temp("pending/hermit_chess") == 2 ) {
		write("你已經找到棋子了﹐快帶回去給隱士吧。\n");
		return 1;
	}

	message_vision("$N蹲下身﹐在水窪邊仔細地翻找著。\n", player);
	write("你撥開水窪邊的蕨類和碎石﹐在泥沙中摸到了一個光滑的小物件。\n");
	write("拿起來一看﹐是一枚玉質的棋子﹐雖然沾了些泥﹐但擦乾淨後依然溫潤光亮。\n");

	piece = new(__DIR__"npc/obj/jade_chess_piece");
	if( piece->move(player) )
		piece->move(environment(player));

	player->set_temp("pending/hermit_chess", 2);
	return 1;
}
