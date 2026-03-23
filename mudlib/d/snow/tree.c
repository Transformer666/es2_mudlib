// Room: /d/snow/tree.c
// Quest: 靈狙現身 (ritual_monkey_encounter)
// Flow: climb tree -> see scratch marks -> place food -> monkey appears
//       -> wait (don't attack) -> monkey gives spirit fruit reward

inherit ROOM;

void summon_monkey(object player);
void monkey_gift(object player);

void create()
{
	set("short", "榕樹上");
	set("long", @LONG
你現在正在一株巨大的榕樹上﹐茂密的枝葉搔得你有些發癢﹐前面
一根粗大的樹枝上有人放著一塊墊子。樹幹上有一些奇怪的爪痕﹐
似乎是什麼動物留下的。
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
		"down" : __DIR__"square",
	]));
	set("objects", ([
		__DIR__"npc/child": 1,
	]));
	set("detail", ([
		"爪痕" : "樹幹上有幾道細長的爪痕﹐看起來是某種靈活的小動物留下的﹐"
			"痕跡還算新鮮。也許放些食物在這裡﹐能引出這隻神秘的動物。\n",
		"墊子" : "一塊破舊的墊子﹐不知道是哪個孩子放在這裡的。\n",
	]));

	setup();
}

void init()
{
	add_action("do_place_food", "place");
	add_action("do_place_food", "put");
}

int do_place_food(string arg)
{
	object ob, player;
	string *food_ids;

	player = this_player();
	if( !player ) return 0;

	if( !arg || (strsrch(arg, "食物") < 0 && strsrch(arg, "food") < 0
	&&  strsrch(arg, "包子") < 0 && strsrch(arg, "dumpling") < 0
	&&  strsrch(arg, "饅頭") < 0 && strsrch(arg, "manto") < 0
	&&  strsrch(arg, "月餅") < 0 && strsrch(arg, "mooncake") < 0
	&&  strsrch(arg, "肉") < 0 && strsrch(arg, "pork") < 0
	&&  strsrch(arg, "麻糬") < 0 && strsrch(arg, "ricedough") < 0) )
		return notify_fail("你想放什麼東西？\n");

	if( player->query("quest/ritual_monkey_encounter_done") ) {
		write("你已經和靈狙交過朋友了﹐不需要再放食物。\n");
		return 1;
	}

	if( player->query_temp("pending/ritual_monkey") ) {
		write("你已經放了食物了﹐耐心等一等吧。\n");
		return 1;
	}

	// Check if player has any food item
	food_ids = ({ "dumpling", "manto", "mooncake", "pork", "ricedough" });
	foreach( string fid in food_ids ) {
		ob = present(fid, player);
		if( ob ) break;
	}

	if( !ob ) {
		write("你身上沒有可以放的食物。\n");
		return 1;
	}

	message_vision("$N小心翼翼地將" + ob->name() + "放在樹枝上。\n", player);
	destruct(ob);

	player->set_temp("pending/ritual_monkey", 1);
	message("vision",
		"樹葉沙沙作響﹐似乎有什麼東西在枝葉間窺視。\n",
		environment(player));

	call_out("summon_monkey", 4, player);
	return 1;
}

void summon_monkey(object player)
{
	object monkey, env;

	if( !player ) return;
	env = environment(player);
	if( !env || base_name(env) != __DIR__"tree" ) return;

	// Clone the monkey into the room
	monkey = new(__DIR__"npc/ritual_monkey");
	if( !monkey ) return;
	monkey->move(env);

	message("vision",
		"一隻通體金毛的小猴子從茂密的枝葉間探出頭來﹐好奇地看了看四周﹐"
		"然後輕巧地跳到樹枝上﹐撿起食物吃了起來。\n",
		env);

	call_out("monkey_gift", 6, player);
}

void monkey_gift(object player)
{
	object monkey, fruit, env;

	if( !player ) return;
	env = environment(player);
	if( !env || base_name(env) != __DIR__"tree" ) return;

	monkey = present("ritual_monkey", env);
	if( !monkey ) {
		// Monkey was killed or left
		player->delete_temp("pending/ritual_monkey");
		return;
	}

	if( player->query("quest/ritual_monkey_encounter_done") ) {
		player->delete_temp("pending/ritual_monkey");
		destruct(monkey);
		return;
	}

	message("vision",
		"靈狙吃完食物﹐滿足地拍了拍肚皮。牠歪著頭端詳了"
		+ player->name() + "一會兒﹐忽然轉身跳進茂密的枝葉中。\n",
		env);

	message("vision",
		"過了一會兒﹐靈狙抱著幾顆金色的果實跳了回來﹐將果實塞進了"
		+ player->name() + "的手裡﹐嘰嘰叫了幾聲﹐似乎在表示友好。\n",
		env);

	fruit = new(__DIR__"npc/obj/wild_fruit");
	fruit->set_amount(3);
	if( !fruit->move(player) )
		fruit->move(env);

	player->set("quest/ritual_monkey_encounter_done", 1);
	player->gain_score("quest", 80);
	player->delete_temp("pending/ritual_monkey");

	message("vision",
		"靈狙對" + player->name() + "眨了眨眼睛﹐然後一個翻身消失在枝葉之中。\n",
		env);

	destruct(monkey);
}
