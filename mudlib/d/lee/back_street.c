// Room: /d/lee/back_street.c
// Quest: 李老伯的傳家寶 — 搜尋小賊

inherit ROOM;

int do_search(string arg);

void create()
{
	set("short", "村後小路");
	set("long", @LONG
村口北邊的一條小路﹐路旁長著幾棵桃樹﹐落英繽紛﹐地上鋪了一
層粉色的花瓣。路邊有幾間矮小的柴房﹐堆放著劈好的柴禾。一隻黃
狗趴在路邊打盹﹐偶爾豎起耳朵聽聽動靜。
LONG
	);
	set("detail", ([
		"柴房" : "幾間低矮的柴房﹐門半掩著﹐裡面堆著木柴和雜物。\n",
		"黃狗" : "一隻懶洋洋的黃狗﹐對你不太感興趣。\n",
	]));
	set("exits", ([
		"south" : __DIR__"square",
		"north" : __DIR__"shop",
	]));

	setup();
}

void init()
{
	::init();
	add_action("do_search", "search");
}

int do_search(string arg)
{
	object player, thief;

	if( !arg || (strsrch(arg, "柴房") < 0 && strsrch(arg, "shed") < 0
	&&  strsrch(arg, "房") < 0 && strsrch(arg, "四周") < 0
	&&  strsrch(arg, "around") < 0) )
		return notify_fail("你要搜尋什麼﹖\n");

	player = this_player();

	if( player->query("quest/lee_heirloom_done") ) {
		write("你仔細搜索了一番﹐柴房裡只有木柴和蜘蛛網。\n");
		return 1;
	}

	if( !player->query_temp("pending/lee_heirloom") ) {
		write("你隨意看了看柴房﹐裡面堆放著木柴﹐沒什麼特別的。\n");
		return 1;
	}

	// 如果小賊已經在房間裡了
	if( present("thief", environment(player)) ) {
		write("小賊就在這裡﹐你還在找什麼﹖\n");
		return 1;
	}

	message_vision("$N走到柴房門口﹐推開門仔細搜索著。\n", player);
	write("你推開柴房的門﹐忽然一個人影從裡面竄了出來﹗\n");

	thief = new(__DIR__"npc/thief");
	thief->move(environment(player));

	message_vision(
		"一個賊眉鼠眼的年輕人從柴房裡衝了出來﹐手裡握著一把短刀﹗\n"
		"小賊喝道﹕多管閒事﹗看我不宰了你﹗\n",
		player);

	return 1;
}
