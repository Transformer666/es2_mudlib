// vim: syntax=lpc
// Room: /d/waterfog/deep_fog.c
// Quest: 霧林蜈蚣 (fog_centipede)
// Flow: hermit asks for help -> player searches deep_fog -> centipede spawns
//       -> defeat centipede -> get venom_sac -> give to hermit -> reward

inherit ROOM;

void spawn_centipede(object player);

void create()
{
	set("short", "迷霧深處");
	set("long", @LONG
這裡是水霧最為濃密的區域，四周一片白茫茫，完全失去了方向感。
地面上佈滿了枯枝落葉，踩上去發出令人不安的碎裂聲。空氣中的
水分凝結在每一個表面上，到處都是滴答滴答的滴水聲。地上散落
著一些甲殼碎片和黏液的痕跡﹐似乎有什麼巨大的蟲類在此出沒。
LONG
	);
	set("outdoors", "wilderness");
	set("detail", ([
		"甲殼" : "漆黑發亮的甲殼碎片﹐堅硬異常﹐上面還殘留著一些黏液。\n",
		"黏液" : "地上的黏液呈暗綠色﹐散發著刺鼻的腥臭﹐似乎帶有劇毒。\n",
		"痕跡" : "地面上有數道平行的刮痕﹐像是某種多足生物爬行留下的。\n",
	]));
	set("exits", ([
		"west" : __DIR__"fog_path",
	]));

	setup();
}

void init()
{
	add_action("do_search", "search");
	add_action("do_search", "listen");
}

int do_search(string arg)
{
	object player;

	player = this_player();
	if( !player ) return 0;

	if( !arg || (strsrch(arg, "蜈蚣") < 0 && strsrch(arg, "蟲") < 0
	&&  strsrch(arg, "蹤") < 0 && strsrch(arg, "聲") < 0
	&&  strsrch(arg, "centipede") < 0 && strsrch(arg, "track") < 0
	&&  strsrch(arg, "痕跡") < 0 && strsrch(arg, "甲殼") < 0) )
		return notify_fail("你想搜尋什麼？\n");

	if( player->query("quest/fog_centipede_done") ) {
		write("大蜈蚣已經被你除掉了﹐迷霧深處安靜了許多。\n");
		return 1;
	}

	if( !player->query_temp("pending/fog_centipede") ) {
		write("你四處張望了一下﹐除了地上的甲殼碎片和黏液﹐沒有發現什麼異狀。\n");
		return 1;
	}

	if( present("centipede", environment(player)) ) {
		write("大蜈蚣就在眼前﹐你還是先對付牠吧！\n");
		return 1;
	}

	message_vision(
		"$N蹲下身子﹐仔細查看地上的痕跡。\n"
		"黏液的痕跡還是新鮮的﹐旁邊的枯葉被壓出了一道深深的凹痕 ...\n",
		player);

	message("vision",
		"忽然﹐地面開始微微震動﹐一股腥臭的氣味從迷霧深處湧來﹗\n"
		"枯枝碎裂的聲音越來越近﹐越來越急促 ...\n",
		environment(player));

	call_out("spawn_centipede", 3, player);
	return 1;
}

void spawn_centipede(object player)
{
	object centipede, env;

	if( !player ) return;
	env = environment(player);
	if( !env || base_name(env) != __DIR__"deep_fog" ) return;
	if( present("centipede", env) ) return;

	centipede = new(__DIR__"npc/centipede");
	if( !centipede ) return;
	centipede->move(env);

	message("vision",
		"一條身長數丈的巨大蜈蚣從迷霧中鑽了出來﹗\n"
		"牠通體漆黑﹐無數節足如利刃般閃著寒光﹐\n"
		"觸鬚瘋狂地擺動著﹐發出令人毛骨悚然的嘶嘶聲﹗\n",
		env);
}
