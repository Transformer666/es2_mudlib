// elder.c
// Quest: 李老伯的傳家寶 (quest/lee_heirloom_done)
// 李老伯的傳家玉牌被小賊偷走﹐玩家在村後小路搜尋小賊﹐
// 擊敗後取回玉牌交還李老伯﹐獲得獎勵。

#include <npc.h>

inherit F_VILLAGER;

void give_reward(object player);

void create()
{
	set_name("李老伯", ({"elder", "li_elder"}));
	set_race("human");
	set_class("commoner");
	set_level(10);

	set("age", 70);
	set("gender", "male");
	set("long",
		"一個精神矍鑠的老人﹐鬚髮皆白﹐穿著一件整潔的青布長衫。\n"
		"他拄著一根龍頭拐杖﹐在村裡慢悠悠地踱步﹐遇到人便和藹地點\n"
		"頭微笑。他是李家村的族長﹐在村裡德高望重。不過最近他似乎有\n"
		"些心事﹐眉宇間透著一絲憂愁。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"李老伯捋著白鬍子﹐笑道﹕客人遠道而來﹐歡迎歡迎。\n",
		"李老伯嘆道﹕我李家在此居住已有百年了﹐見過的事多了去啦。\n",
		"李老伯說道﹕嚐嚐我們李家的豆腐﹐那可是祖傳的手藝。\n",
		"李老伯拄著拐杖﹐慢悠悠地走著﹐不時跟路過的村民寒暄。\n",
	}));
	setup();
	carry_money("coin", 40);
}

void init()
{
	::init();
	if( is_fighting() || is_chatting() ) return;
	if( !userp(this_player()) ) return;

	if( this_player()->query("quest/lee_heirloom_done") ) {
		do_chat("李老伯笑呵呵地向你打招呼﹕又來了﹖坐坐﹐喝杯茶。\n");
		return;
	}

	if( this_player()->query_temp("pending/lee_heirloom") ) {
		do_chat("李老伯焦急地問﹕找到那個小賊了嗎﹖我的傳家玉牌可不能丟啊 ...\n");
		return;
	}
}

int accept_object(object player, object ob)
{
	if( !userp(player) ) return 0;
	if( player->query("quest/lee_heirloom_done") ) {
		do_chat("李老伯笑道﹕你已經幫過老夫了﹐這份恩情我李家記住了。\n");
		return 0;
	}

	if( !player->query_temp("pending/lee_heirloom") ) return 0;

	if( ob->id("jade tablet") || ob->id("tablet") ) {
		do_chat(({
			"李老伯接過玉牌﹐仔細端詳了一番﹐激動地連連點頭。\n",
			"李老伯說道﹕沒錯﹗這就是我李家的傳家玉牌﹗你看﹐背面的家訓還在。\n",
			"李老伯老淚縱橫﹕多謝恩人啊﹐這塊玉牌傳了五代了﹐差點就斷在我手上。\n",
			"李老伯說道﹕老夫無以為報﹐這塊玉牌就送給你吧﹐你是它的有緣人。\n",
			(: give_reward, player :),
		}));
		return 1;
	}

	do_chat("李老伯搖搖頭﹕這 ... 這不是我要找的東西。我要的是傳家玉牌。\n");
	return 0;
}

void give_reward(object player)
{
	object tablet;

	if( !player || environment(player) != environment() ) return;

	tablet = new(__DIR__"obj/jade_tablet");
	if( !tablet->move(player) )
		tablet->move(environment());

	player->set("quest/lee_heirloom_done", 1);
	player->gain_score("quest", 100);
}

void relay_say(object ob, string msg)
{
	if( !userp(ob) ) return;
	if( is_fighting() || is_chatting() ) return;
	if( ob->query("quest/lee_heirloom_done") ) return;

	if( !ob->query_temp("pending/lee_heirloom") ) {
		if( strsrch(msg, "幫") >= 0 || strsrch(msg, "煩惱") >= 0
		||  strsrch(msg, "怎麼了") >= 0 || strsrch(msg, "什麼事") >= 0
		||  strsrch(msg, "心事") >= 0 ) {
			do_chat(({
				"李老伯嘆了口氣﹐說道﹕唉﹐不瞞你說﹐前幾天有個小賊溜進祠堂﹐把我李家的傳家玉牌偷走了。\n",
				"李老伯說道﹕那塊玉牌傳了五代人了﹐是我們李家的根本啊。\n",
				"李老伯說道﹕聽村民說﹐那小賊好像還躲在村後的小路附近﹐你能不能幫老夫去看看﹖\n",
			}));
			ob->set_temp("pending/lee_heirloom", 1);
			return;
		}
	}

	if( ob->query_temp("pending/lee_heirloom") ) {
		if( strsrch(msg, "小賊") >= 0 || strsrch(msg, "賊") >= 0
		||  strsrch(msg, "玉牌") >= 0 ) {
			do_chat("李老伯說道﹕村後小路那邊有幾間柴房﹐那小賊可能躲在那附近﹐你小心些。\n");
			return;
		}
	}
}
