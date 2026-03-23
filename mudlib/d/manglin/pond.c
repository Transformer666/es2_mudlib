// Room: /d/manglin/pond.c
// Quest: 莽林鮫蛟 (manglin_hydra) - search water to spawn hydra

inherit ROOM;

void spawn_hydra(object player);

void create()
{
	set("short", "林中水潭");
	set("long", @LONG
林中有一汪清澈的水潭﹐潭水碧綠﹐深不見底。潭邊長著幾叢蘆葦
﹐水面上浮著幾片落葉。幾隻不知名的水鳥在潭邊覓食﹐見到有人來便
撲楞楞地飛走了。潭水倒映著四周的樹影﹐環境十分清幽。
LONG
	);
	set("outdoors", "forest");
	set("detail", ([
		"水紋" : "潭水深處偶爾會泛起異常的漣漪﹐彷彿有某種巨大的水中生物潛伏其中。水面上隱約可見幾片大如手掌的鱗片漂浮。\n",
		"鱗片" : "青黑色的鱗片大如手掌﹐堅硬無比﹐看起來不像是普通魚類的鱗片。\n",
	]));
	set("objects", ([
		__DIR__"npc/qiyong" : 1,
	]));
	set("exits", ([
		"south" : __DIR__"clearing",
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
	object player;

	player = this_player();
	if( !player ) return 0;

	if( !arg || (strsrch(arg, "水") < 0 && strsrch(arg, "潭") < 0
	&&  strsrch(arg, "鱗") < 0 && strsrch(arg, "water") < 0
	&&  strsrch(arg, "pond") < 0 && strsrch(arg, "漣漪") < 0) )
		return notify_fail("你想搜尋什麼﹖\n");

	if( player->query("quest/manglin_hydra_done") ) {
		write("自從鮫蛟被除掉之後﹐這水潭又恢復了寧靜。\n");
		return 1;
	}

	if( !player->query_temp("pending/manglin_hydra") ) {
		write("你盯著水面看了一會兒﹐只見偶爾泛起幾圈漣漪﹐看不出什麼名堂。\n");
		return 1;
	}

	if( present("evil_hydra", environment(player)) ) {
		write("鮫蛟已經浮出水面了﹐你還是先對付牠吧！\n");
		return 1;
	}

	message_vision(
		"$N走到潭邊﹐俯身仔細觀察水面。\n"
		"水面上的鱗片突然劇烈晃動﹐潭水開始翻騰！\n",
		player);

	message("vision",
		"一股腥臭的水氣從潭底湧上﹐潭水瞬間變得渾濁﹗\n"
		"水面下隱約可見一條巨大的身影正在翻攪 ...\n",
		environment(player));

	call_out("spawn_hydra", 2, player);
	return 1;
}

void spawn_hydra(object player)
{
	object hydra, env;

	if( !player ) return;
	env = environment(player);
	if( !env || base_name(env) != __DIR__"pond" ) return;
	if( present("evil_hydra", env) ) return;

	hydra = new(__DIR__"npc/evil_hydra");
	if( !hydra ) return;
	hydra->move(env);

	message("vision",
		"一條身長數十丈的巨蛟猛然破水而出﹗\n"
		"鮫蛟的十二爪在空中張開﹐鱗甲上的水珠在陽光下閃爍﹐\n"
		"牠發出震耳欲聾的嘶吼﹐兇狠地掃視著四周！\n",
		env);
}
