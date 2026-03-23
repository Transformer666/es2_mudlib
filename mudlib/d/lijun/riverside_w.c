// Room: /d/lijun/riverside_w.c
// Quest: trader_cargo - search shallows for trader's lost cargo box

inherit ROOM;

void create()
{
	set("short", "河畔西段");
	set("long", @LONG
沿著河岸往西的一條小路﹐路旁種著幾棵垂柳﹐柳條隨風搖曳﹐
拂過水面。河邊散落著幾塊大石頭﹐是歇腳的好地方。遠處可以看到
清月樓的飛簷翹角從柳樹後面探出頭來。這裡比東邊清靜得多﹐偶爾
有釣魚的老翁在此垂釣。往北走可以到清月樓﹐往東回到碼頭。河水
在這一帶形成了一片淺灘﹐水中隱約可以看到一些被沖上岸的雜物。
LONG
	);
	set("outdoors", "water");
	set("detail", ([
		"淺灘" : "一片淺淺的灘地﹐水流平緩﹐泥沙中混雜著漂流物。\n",
		"雜物" : "一些樹枝、碎布和破爛的竹簍﹐都是被河水沖上來的。\n",
	]));
	set("exits", ([
		"east" : __DIR__"dock",
		"north" : __DIR__"teahouse",
	]));

	setup();
}

void init()
{
	add_action("do_search", "search");
}

int do_search(string arg)
{
	object player, box;

	player = this_player();
	if( !player ) return 0;

	if( !arg || (strsrch(arg, "淺灘") < 0 && strsrch(arg, "灘") < 0
	&&  strsrch(arg, "貨") < 0 && strsrch(arg, "cargo") < 0
	&&  strsrch(arg, "箱") < 0 && strsrch(arg, "shallow") < 0) )
		return notify_fail("你想搜尋什麼？\n");

	if( !player->query_temp("pending/trader_cargo") ) {
		write("你在淺灘上翻找了一下﹐只找到一些破爛的漂流物。\n");
		return 1;
	}

	if( player->query("quest/trader_cargo_done") ) {
		write("淺灘上已經沒有什麼值得找的東西了。\n");
		return 1;
	}

	if( present("cargo_box", player) ) {
		write("你已經找到貨箱了﹐趕快帶回去給行商吧。\n");
		return 1;
	}

	message_vision(
		"$N捲起褲腳﹐踏入淺灘中仔細翻找。\n",
		player);

	box = new(__DIR__"npc/obj/cargo_box");
	if( box ) box->move(player);

	write(
		"你在淺灘的泥沙中摸索了一陣﹐終於在幾塊大石頭後面發現\n"
		"一只半埋在泥裡的木箱。箱子上刻著一個「程」字﹐看起來\n"
		"就是行商丟失的貨箱﹗你用力將它從泥沙中拔出來。\n");
	message("vision",
		"$N從淺灘中拖出了一只木箱。\n",
		environment(player), ({player}));

	return 1;
}
