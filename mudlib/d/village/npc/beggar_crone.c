// vim: syntax=lpc
// Quest: 老乞婆的秘密 (beggar_secret)
// Flow: give food -> she reveals past -> tells about pendant in well
//       -> player searches well -> returns pendant -> reward

#include <npc.h>

inherit F_VILLAGER;

void give_reward(object player);

void create()
{
	set_name("老乞婆", ({"beggar_crone", "beggar", "crone"}));
	set_attr("str", 8);
	set_attr("dex", 10);
	set_attr("con", 8);
	set_attr("int", 14);
	set_attr("spi", 16);
	set_race("human");
	set_class("commoner");
	set_level(5);

	set("age", 70);
	set("gender", "female");
	set("long",
		"一個衣衫襤褸的老婦人，臉上佈滿了歲月的皺紋，但眼神中卻透著\n"
		"一股不凡的靈氣。她蜷縮在路邊，向過路的人伸出枯瘦的手。\n");
	set("chat_chance", 5);
	set("chat_msg", ({
		"老乞婆說道﹕行行好吧﹐給點吃的 ...\n",
		"老乞婆咳嗽了幾聲﹐裹了裹身上破爛的衣服。\n",
	}));
	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
}

int accept_object(object player, object ob)
{
	if( !userp(player) ) return 0;

	if( player->query("quest/beggar_secret_done") ) {
		do_chat("老乞婆微微一笑﹐說道﹕不必了﹐你的恩情老身已經記在心裡了。\n");
		return 0;
	}

	// Accept food items
	if( !ob->id("dumpling") && !ob->id("dried_fish") && !ob->id("food")
	&&  !ob->id("manto") && !ob->id("mooncake") && !ob->id("ricedough")
	&&  !ob->id("pork") && !ob->id("rice") && !ob->id("watermelon")
	&&  !ob->id("bun") && !ob->id("herb") ) {
		do_chat("老乞婆看了看﹐搖了搖頭。\n");
		return 0;
	}

	if( player->query_temp("pending/beggar_secret") ) {
		do_chat("老乞婆感激地接過食物﹐說道﹕多謝你了﹐快去幫我找找那墜子吧。\n");
		return 1;
	}

	do_chat(({
		"老乞婆接過食物﹐顫抖的手捧著﹐眼眶紅了。\n",
		"老乞婆說道﹕多謝你 ... 好久沒吃過飽飯了 ...\n",
		"老乞婆吃完後﹐擦了擦嘴角﹐忽然嘆了口氣。\n",
		"老乞婆說道﹕看你是個好心人﹐老身就跟你說實話吧。\n",
		"老乞婆說道﹕我本姓柳﹐家住龍安城﹐夫家也算是書香門第。\n",
		"老乞婆說道﹕去年一場大火燒了宅子﹐家人也散了﹐我只好四處流浪。\n",
		"老乞婆說道﹕逃難時匆忙間把亡夫留給我的翠玉墜子弄丟了 ...\n",
		"老乞婆說道﹕記得經過這村子時﹐在井邊歇過腳﹐墜子大概是掉進井裡了。\n",
		"老乞婆說道﹕那是夫君的遺物﹐對我來說比什麼都珍貴。你若能幫我找回來 ...\n",
	}));
	player->set_temp("pending/beggar_secret", 1);
	return 1;
}

void relay_say(object ob, string msg)
{
	if( !userp(ob) ) return;
	if( is_fighting() || is_chatting() ) return;

	if( ob->query("quest/beggar_secret_done") ) return;

	// Player found the pendant and returned
	if( ob->query_temp("pending/beggar_secret") == 2 ) {
		if( strsrch(msg, "墜子") >= 0 || strsrch(msg, "找到") >= 0
		||  strsrch(msg, "pendant") >= 0 || strsrch(msg, "玉") >= 0 ) {
			object pendant;
			pendant = present("jade_pendant", ob);
			if( !pendant ) {
				do_chat("老乞婆說道﹕你找到了﹖在哪裡﹖\n");
				return;
			}
			destruct(pendant);
			do_chat(({
				"老乞婆接過墜子﹐雙手顫抖﹐淚流滿面。\n",
				"老乞婆說道﹕這 ... 這就是他留給我的 ... 老身終於又見到了 ...\n",
				"老乞婆將墜子緊緊貼在胸口﹐泣不成聲。\n",
				"老乞婆擦了擦眼淚﹐說道﹕恩人﹐老身無以為報 ...\n",
				"老乞婆說道﹕我身上只剩這點碎銀﹐你拿著吧﹐是老身的一片心意。\n",
				(: give_reward, ob :),
			}));
			return;
		}
	}

	if( ob->query_temp("pending/beggar_secret") == 1 ) {
		if( strsrch(msg, "井") >= 0 || strsrch(msg, "哪") >= 0
		||  strsrch(msg, "墜子") >= 0 ) {
			do_chat("老乞婆說道﹕就是村子東南邊的那口水井﹐我記得在井邊打過水 ... 也許掉進去了。\n");
			return;
		}
	}
}

void give_reward(object player)
{
	object money;

	if( !player || environment(player) != environment() ) return;

	player->set("quest/beggar_secret_done", 1);
	player->gain_score("quest", 100);
	player->delete_temp("pending/beggar_secret");

	money = new("/obj/money/silver");
	money->set_amount(2);
	if( money->move(player) )
		money->move(environment());
}
