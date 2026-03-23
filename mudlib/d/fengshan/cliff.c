// vim: syntax=lpc
// Quest support: 遺失的劍譜 (fengshan_lost_manual)
// Player searches cliff to find the lost sword scroll

inherit ROOM;

void create()
{
	set("short", "斷崖");
	set("long", @LONG
劍道場東面的懸崖邊緣，腳下便是萬丈深淵，雲霧在崖壁間翻湧
不息。這裡是封山派最險峻的所在，只有技藝高超的弟子才敢在此練劍。
崖壁上有歷代高手以劍氣刻下的字跡，有的龍飛鳳舞，有的筆力萬鈞，
每一筆每一劃都蘊含著精深的劍意。山風在崖間呼嘯，如同萬劍齊鳴。
LONG
	);
	set("outdoors", "mountain");
	set("detail", ([
		"字跡" : "崖壁上刻著歷代高手的劍意﹐每一筆都蘊含著精深的內力。\n",
		"石縫" : "崖壁上有不少裂縫﹐有些縫隙中似乎卡著什麼東西。\n",
	]));
	set("exits", ([
		"west" : __DIR__"sword_arena",
	]));

	setup();
}

void init()
{
	add_action("do_search", "search");
	add_action("do_search", "investigate");
}

int do_search(string arg)
{
	object player, scroll;

	player = this_player();
	if( !player ) return 0;

	if( !arg || (strsrch(arg, "崖") < 0 && strsrch(arg, "cliff") < 0
	&&  strsrch(arg, "石縫") < 0 && strsrch(arg, "crack") < 0
	&&  strsrch(arg, "縫") < 0 && strsrch(arg, "壁") < 0) )
		return 0;

	if( player->query("quest/fengshan_lost_manual_done") ) {
		write("崖壁上只剩歷代高手的劍痕字跡﹐別無他物。\n");
		return 1;
	}

	if( !player->query_temp("pending/fengshan_lost_manual") ) {
		write("崖壁上到處都是深深的劍痕﹐蔚為壯觀﹐但你也不知道該找什麼。\n");
		return 1;
	}

	if( present("sword_scroll", player) ) {
		write("你已經找到劍譜了﹐趕快帶回藏書閣交給長老吧。\n");
		return 1;
	}

	message_vision(
		"$N小心翼翼地沿著崖壁探查﹐仔細察看石縫中是否有什麼東西。\n",
		player);

	write(
		"你在一道深深的石縫中隱約看到一截竹簡的邊角﹐上面還殘留著字跡。\n"
		"你伸手探入石縫﹐費了好大功夫才將竹簡完整地取了出來。\n");

	message("vision",
		player->name() + "從崖壁的石縫中取出了一卷竹簡。\n",
		environment(player), player);

	scroll = new(__DIR__"npc/obj/sword_scroll");
	scroll->move(player);

	tell_object(player, "( 你找到了封山劍法殘譜 )\n");
	return 1;
}
