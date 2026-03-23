// Room: /d/baihua/garden.c
// Quest: melon_pest - search here to spawn wild boar

inherit ROOM;

void check_boar_killed(object player);

void create()
{
	set("short", "小花園");
	set("long", @LONG
一座精心打理的小花園﹐用竹籬笆圍成一圈。園中種植著各種名貴
花卉﹐按顏色和種類分成幾個花圃﹐中間有一條碎石小徑供人行走。園
中立著一座小巧的涼亭﹐亭中擺著一張石桌和幾個石凳。往南是一片
瓜田。
LONG
	);
	set("detail", ([
		"花圃" : "幾個花圃裡種著牡丹、菊花和蘭花﹐有幾株被踩倒了﹐\n"
			"泥土裡留著蹄印﹐看來是什麼動物闖進來過。\n",
		"竹籬笆" : "竹籬笆有一處被撞破了一個大洞﹐邊緣還掛著幾根粗硬的毛。\n",
	]));
	set("exits", ([
		"east" : __DIR__"street",
		"south" : __DIR__"melon_farm",
	]));

	setup();
}

void init()
{
	add_action("do_search", "search");
}

int do_search(string arg)
{
	object me, boar;

	me = this_player();
	if( !me ) return 0;

	if( !me->query_temp("pending/melon_pest_tracked") ) {
		write("你在花園裡看了看﹐花開得很漂亮。\n");
		return 1;
	}

	if( me->query("quest/melon_pest_done") ) {
		write("花園一片寧靜﹐野豬已經不會再來了。\n");
		return 1;
	}

	if( me->query_temp("pending/melon_pest_killed") ) {
		write("野豬已經被你打跑了﹐回去告訴瓜農吧。\n");
		return 1;
	}

	// Check if boar already spawned
	boar = present("wild_boar", this_object());
	if( boar ) {
		write("野豬就在這裡﹐先對付牠吧﹗\n");
		return 1;
	}

	write("你順著蹄印在花園裡搜索﹐發現竹籬笆上有個大洞﹐邊緣\n"
		"掛著幾撮粗硬的毛。你蹲下身子仔細查看……\n");
	say(me->query("name") + "在花園裡仔細搜索著什麼。\n");

	boar = new(__DIR__"npc/wild_boar");
	boar->move(this_object());

	message("vision",
		"忽然﹐竹籬笆後面傳來一陣窸窸窣窣的聲響﹐一頭灰黑色的\n"
		"野豬從破洞裡鑽了出來﹐看到有人擋在面前﹐立刻狂怒地嘶叫起來﹗\n",
		this_object());

	call_out("check_boar_killed", 30, me);
	return 1;
}

void check_boar_killed(object player)
{
	object boar;

	if( !player ) return;
	if( player->query("quest/melon_pest_done") ) return;

	boar = present("wild_boar", this_object());
	if( !boar ) {
		// Boar was killed
		if( present(player, this_object()) ) {
			message("vision",
				"花園重新恢復了平靜﹐被踩壞的花圃顯得有些狼藉。\n",
				this_object());
		}
		player->set_temp("pending/melon_pest_killed", 1);
	}
}
