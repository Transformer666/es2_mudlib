// vim: syntax=lpc
// Quest support: 菩提枯枝 (baixiang_bodhi_tree)
// Player collects sacred dew from the ancient bell

inherit ROOM;

void create()
{
	set("short", "鐘樓");
	set("long", @LONG
一座高聳的木製鐘樓，樓內懸掛著一口巨大的青銅古鐘，鐘身上
鑄刻著密密麻麻的佛經經文。站在鐘樓上可以遠眺四周的山林景色，
群山疊翠，雲霧繚繞，令人心曠神怡。
LONG
	);
	set("detail", ([
		"古鐘" : "青銅古鐘有數百年歷史﹐鐘身上密密麻麻的經文散發著古樸莊嚴的氣息。仔細看去﹐經文的凹槽中似乎凝結著一層晶瑩的露珠。\n",
		"經文" : "密密麻麻的梵文佛經﹐筆畫精細﹐歷經歲月仍然清晰可辨。\n",
		"露珠" : "經文的凹槽中凝結著細小的露珠﹐在光線下閃爍著淡淡的金色。\n",
	]));
	set("exits", ([
		"west" : __DIR__"courtyard",
	]));

	setup();
}

void init()
{
	add_action("do_collect", "collect");
	add_action("do_collect", "search");
}

int do_collect(string arg)
{
	object player, dew;

	player = this_player();
	if( !player ) return 0;

	if( !arg || (strsrch(arg, "露") < 0 && strsrch(arg, "dew") < 0
	&&  strsrch(arg, "鐘") < 0 && strsrch(arg, "bell") < 0
	&&  strsrch(arg, "經文") < 0) )
		return 0;

	if( player->query("quest/baixiang_bodhi_tree_done") ) {
		write("古鐘上的露水已經被你收集過了﹐新的金剛露還需要時日才會凝結。\n");
		return 1;
	}

	if( !player->query_temp("pending/baixiang_bodhi_tree") ) {
		write("你看著古鐘上的經文﹐心中肅然起敬﹐但也不知該做什麼。\n");
		return 1;
	}

	if( present("sacred_dew", player) ) {
		write("你已經收集了金剛露﹐趕快帶去給園頭僧吧。\n");
		return 1;
	}

	message_vision(
		"$N走近古鐘﹐仔細察看經文上凝結的露珠。\n",
		player);

	write(
		"你小心翼翼地用手指沿著經文的凹槽﹐將細小的露珠一滴一滴地\n"
		"收集起來。雖然每個字的凹槽中只有一丁點﹐但積少成多﹐竟也\n"
		"匯成了小小一捧晶瑩的金剛露。\n");

	message("vision",
		player->name() + "從古鐘的經文上小心地收集著露水。\n",
		environment(player), player);

	dew = new(__DIR__"npc/obj/sacred_dew");
	dew->move(player);

	tell_object(player, "( 你收集了一瓶金剛露 )\n");
	return 1;
}
