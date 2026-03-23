// Room: /d/lijun/riverside_e.c
// Quest: ferryman_memento - search reed stash after defeating bandit

inherit ROOM;

void create()
{
	set("short", "河畔東段");
	set("long", @LONG
沿著河岸往東走的一條小路﹐路面泥濘﹐長滿了雜草。右邊是奔
流不息的羿水﹐左邊是幾叢茂密的蘆葦。偶爾能看到水鳥從蘆葦叢中
飛起﹐發出幾聲清脆的啼叫。這一帶比較偏僻﹐偶爾有河匪出沒﹐行
人最好結伴而行。往北走可以到小市集﹐往西回到碼頭。
LONG
	);
	set("outdoors", "water");
	set("objects", ([
		__DIR__"npc/bandit" : 1,
	]));
	set("detail", ([
		"蘆葦" : "幾叢茂密的蘆葦長得比人還高﹐裡面黑漆漆的﹐似乎可以藏人藏物。\n",
	]));
	set("exits", ([
		"west" : __DIR__"dock",
		"north" : __DIR__"market",
	]));

	setup();
}

void init()
{
	add_action("do_search", "search");
}

int do_search(string arg)
{
	object player, pendant;

	player = this_player();
	if( !player ) return 0;

	if( !arg || (strsrch(arg, "蘆葦") < 0 && strsrch(arg, "reed") < 0
	&&  strsrch(arg, "stash") < 0 && strsrch(arg, "藏") < 0) )
		return notify_fail("你想搜尋什麼？\n");

	if( !player->query_temp("pending/ferryman_memento") ) {
		write("你撥開蘆葦叢看了看﹐除了幾隻受驚的水鳥﹐沒什麼特別的。\n");
		return 1;
	}

	if( player->query("quest/ferryman_memento_done") ) {
		write("蘆葦叢裡已經沒有什麼值得注意的東西了。\n");
		return 1;
	}

	if( present("bandit", environment(player)) ) {
		write("河匪就在旁邊虎視眈眈﹐你沒辦法安心搜索。\n");
		return 1;
	}

	if( present("jade_pendant", player) ) {
		write("你已經找到玉佩了﹐趕快帶回去給老艄公吧。\n");
		return 1;
	}

	message_vision(
		"$N小心翼翼地撥開茂密的蘆葦叢﹐在裡面翻找了一番。\n",
		player);

	pendant = new(__DIR__"npc/obj/jade_pendant");
	if( pendant ) pendant->move(player);

	write(
		"在蘆葦叢深處﹐你發現了一個用油布包裹的小包袱﹐\n"
		"裡面除了幾枚銅錢﹐還有一塊翠綠色的玉佩。\n"
		"玉佩上刻著一個小小的「蓮」字﹐應該就是老艄公說的信物。\n");
	message("vision",
		"$N從蘆葦叢中翻出了一個小包袱。\n",
		environment(player), ({player}));

	player->carry_money("coin", 50);
	return 1;
}
