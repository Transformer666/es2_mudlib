// beggar.c
// Quest: 老乞婆的往事 (beggar_past)
// Flow: give food -> she tells story about jade bracelet in temple
//       -> search temple -> find bracelet -> give bracelet to beggar -> reward

#include <npc.h>

inherit F_VILLAGER;

void tell_story(object player);
void set_pending(object player);
void give_reward(object player);
void receive_bracelet(object player);

void create()
{
	set_name("老乞婆", ({"beggar", "old_beggar"}));
	set_race("human");
	set_class("commoner");
	set_level(5);

	set("age", 70);
	set("gender", "female");
	set("long",
		"一個衣衫襤褸的老婆婆﹐滿頭白髮亂蓬蓬的﹐臉上佈滿皺紋﹐\n"
		"手裡拄著一根破竹杖﹐身旁放著一個缺了口的碗。雖然看起來落魄\n"
		"不堪﹐但她的眼神卻異常清亮﹐似乎藏著什麼秘密。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"老乞婆咳嗽了幾聲﹐喃喃道﹕行行好吧﹐給口飯吃。\n",
		"老乞婆抬頭看了你一眼﹐嘴角露出一絲神秘的微笑。\n",
		"老乞婆自言自語道﹕這世道﹐不比從前了……\n",
	}));
	setup();
	carry_money("coin", 5);
}

void init()
{
	::init();
	add_action("do_give_food", "give");
}

int do_give_food(string arg)
{
	object me, food;
	string *food_ids;

	me = this_player();
	if( !me ) return 0;
	if( !arg ) return 0;

	// Must target beggar
	if( strsrch(arg, "乞婆") < 0 && strsrch(arg, "beggar") < 0
	&&  strsrch(arg, "老婆婆") < 0 )
		return 0;

	if( me->query("quest/beggar_past_done") ) {
		do_chat("老乞婆微微一笑﹐說道﹕你的心意老身領了﹐留著自己吃吧。\n");
		return 1;
	}

	if( me->query_temp("pending/beggar_past") ) {
		do_chat("老乞婆說道﹕去城隍廟裡找找看吧﹐老身等你的好消息。\n");
		return 1;
	}

	// Check if player has food
	food_ids = ({ "dumpling", "manto", "mooncake", "pork", "meat_bun",
		"ricedough", "beef", "beef_dumpling" });
	foreach( string fid in food_ids ) {
		food = present(fid, me);
		if( food ) break;
	}

	if( !food ) {
		write("你身上沒有可以給她吃的食物。\n");
		return 1;
	}

	message_vision("$N將" + food->name() + "遞給老乞婆。\n", me);
	destruct(food);

	do_chat(({
		"老乞婆接過食物﹐狼吞虎嚥地吃了起來﹐吃完後抹了抹嘴。\n",
		"老乞婆嘆了口氣﹐說道﹕好久沒吃這麼飽了﹐多謝你啊。\n",
		"老乞婆說道﹕看你是個好人﹐老身跟你說件事吧。\n",
		(: tell_story, me :),
	}));
	return 1;
}

void tell_story(object player)
{
	if( !player || !present(player, environment()) ) return;
	if( player->query("quest/beggar_past_done") ) return;

	do_chat(({
		"老乞婆壓低聲音道﹕老身年輕時﹐也曾是江湖上的人物……\n",
		"老乞婆說道﹕那時候老身叫趙念慈﹐在喬陰也算小有名氣。\n",
		"老乞婆說道﹕後來家道中落﹐丈夫病死﹐老身什麼都沒了。\n",
		"老乞婆說道﹕只剩下一只祖傳的玉鐲﹐是老身最後的念想。\n",
		"老乞婆說道﹕可是前些年﹐有幾個小賊盯上了它﹐老身怕被搶﹐\n"
			"就偷偷藏到城隍廟的神像底下了。\n",
		"老乞婆說道﹕老身腿腳不便﹐去不了那裡……你若願意幫忙﹐\n"
			"到城隍廟的神像底下找找﹐把玉鐲帶回來給老身吧。\n",
		(: set_pending, player :),
	}));
}

void set_pending(object player)
{
	if( !player ) return;
	player->set_temp("pending/beggar_past", 1);
}

int receive_object(object ob, object from)
{
	if( !ob || !from ) return 0;

	if( base_name(ob) == __DIR__"obj/jade_bracelet" ) {
		if( from->query("quest/beggar_past_done") ) {
			do_chat("老乞婆搖搖頭﹐說道﹕這個你留著吧﹐老身不需要了。\n");
			return 0;
		}

		destruct(ob);
		call_out("receive_bracelet", 1, from);
		return 1;
	}
	return 0;
}

void receive_bracelet(object player)
{
	object reward;

	if( !player || !present(player, environment()) ) return;
	if( player->query("quest/beggar_past_done") ) return;

	do_chat(({
		"老乞婆接過玉鐲﹐顫抖的手指撫摸著上面的刻字﹐老淚縱橫。\n",
		"老乞婆說道﹕念慈……這是老身的名字啊。多少年了。\n",
		"老乞婆擦了擦眼淚﹐說道﹕多謝你﹐孩子。\n",
		"老乞婆說道﹕老身無以為報﹐這些銅板你拿著﹐另外……\n",
		"老乞婆從懷裡摸出一本破舊的小冊子﹐說道﹕\n"
			"這是老身年輕時練的一套吐納法訣﹐雖不是什麼了不起的功夫﹐\n"
			"但對修煉內功多少有些幫助﹐你收著吧。\n",
		(: give_reward, player :),
	}));
}

void give_reward(object player)
{
	object money;

	if( !player || !present(player, environment()) ) return;
	if( player->query("quest/beggar_past_done") ) return;

	player->set("quest/beggar_past_done", 1);
	player->gain_score("quest", 80);
	player->delete_temp("pending/beggar_past");

	money = new("/obj/money/silver");
	money->set_amount(2);
	if( !money->move(player) )
		money->move(environment());

	// Improve player's force skill slightly as reward
	player->improve_skill("force", 3 + random(5));

	message("vision",
		"老乞婆將小冊子和碎銀塞進了" + player->name() + "手裡。\n",
		environment());
}
