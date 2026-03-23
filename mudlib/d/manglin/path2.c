// Room: /d/manglin/path2.c
// Quest: hunter_beast - search for tiger tracks to spawn devilish tiger

inherit ROOM;

void spawn_tiger(object player);

void create()
{
	set("short", "莽林深處");
	set("long", @LONG
莽林深處﹐光線更加昏暗﹐巨大的樹幹上纏繞著粗壯的藤蔓﹐有
些樹根裸露在外﹐形成天然的障礙。空氣中瀰漫著一股腐朽的氣味﹐
地上散落著一些白骨﹐不知是獸骨還是人骨。偶爾能聽到低沉的嗥叫
聲從更深處傳來。
LONG
	);
	set("outdoors", "forest");
	set("objects", ([
		__DIR__"npc/black_bear" : 1,
	]));
	set("detail", ([
		"虎爪痕" : "幾棵大樹的樹幹上有深深的爪痕﹐看起來是某種巨型猛虎磨爪留下的﹐令人不寒而慄。\n",
		"白骨" : "地上散落著幾根獸骨﹐有些還帶著撕裂的肉片﹐上面有巨大的齒痕﹐似乎是被什麼猛獸啃咬過的。\n",
	]));
	set("exits", ([
		"south" : __DIR__"path1",
		"north" : __DIR__"path3",
	]));

	setup();
}

void init()
{
	add_action("do_search", "search");
}

int do_search(string arg)
{
	object player;

	player = this_player();
	if( !player ) return 0;

	if( !arg || (strsrch(arg, "虎") < 0 && strsrch(arg, "蹤") < 0
	&&  strsrch(arg, "爪") < 0 && strsrch(arg, "track") < 0
	&&  strsrch(arg, "tiger") < 0) )
		return notify_fail("你想搜尋什麼？\n");

	if( !player->query_temp("pending/hunter_beast") ) {
		write("你四處張望了一下﹐除了樹幹上的爪痕﹐沒有發現什麼異狀。\n");
		return 1;
	}

	if( player->query("quest/hunter_beast_done") ) {
		write("狻猊已經被你除掉了﹐林中安靜了許多。\n");
		return 1;
	}

	if( present("devilish_tiger", environment(player)) ) {
		write("狻猊就在眼前﹐你還是先對付牠吧！\n");
		return 1;
	}

	message_vision(
		"$N蹲下身子﹐仔細查看地上的痕跡。\n"
		"泥地上有幾個深深的巨大爪印﹐旁邊還有拖拽獵物留下的血跡 ...\n",
		player);

	message("vision",
		"忽然﹐四周的樹葉劇烈搖動﹐一股令人窒息的陰氣從密林中湧出﹗\n"
		"低沉而震人心魄的咆哮聲從黑暗中傳來 ...\n",
		environment(player));

	call_out("spawn_tiger", 2, player);
	return 1;
}

void spawn_tiger(object player)
{
	object tiger, env;

	if( !player ) return;
	env = environment(player);
	if( !env || base_name(env) != __DIR__"path2" ) return;
	if( present("devilish_tiger", env) ) return;

	tiger = new(__DIR__"npc/devilish_tiger");
	if( !tiger ) return;
	tiger->move(env);

	message("vision",
		"一頭週身纏繞著陰氣的巨虎從密林中猛撲而出﹗\n"
		"狻猊血紅的雙眼掃視著四周﹐發出令人膽寒的低吼。\n",
		env);
}
