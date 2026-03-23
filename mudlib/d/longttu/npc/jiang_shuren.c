// vim: syntax=lpc
// jiang_shuren.c - 江述仁
// Quest: 江述仁的藥材債 (jiang_herb_debt)
// Flow: talk about debt/herbs -> search well in garden -> get purple_lingzhi
//       -> give lingzhi to jiang -> reward

#include <npc.h>

inherit F_VILLAGER;

void do_reward(object player);

void create()
{
	set_name("江述仁", ({"jiang_shuren", "jiang", "shuren"}));
	set_attr("str", 12);
	set_attr("dex", 16);
	set_attr("con", 14);
	set_attr("int", 24);
	set_attr("spi", 22);
	set_attr("wis", 20);
	set_race("human");
	set_class("commoner");
	set_level(25);

	set_skill("unarmed", 30);
	set_skill("dodge", 40);

	set("age", 45);
	set("gender", "male");
	set("long",
		"江述仁是龍圖丹派的醫師﹐擅長煉丹製藥。他看起來約四十五歲﹐\n"
		"一身青袍﹐神情略顯疲憊﹐似乎最近欠了不少藥材的債。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"江述仁嘆了口氣﹐說道﹕唉﹐我這次可是欠了不少啊 ...\n",
		"江述仁翻閱著手中的藥方﹐眉頭緊鎖。\n",
	}));
	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
}

int accept_object(object who, object ob)
{
	if( !ob->id("purple lingzhi") && !ob->id("purple_lingzhi") ) return 0;

	if( who->query("quest/jiang_herb_debt_done") ) {
		do_chat("江述仁搖搖頭﹐說道﹕你已經幫過我了﹐這株靈芝你自己留著吧。\n");
		return 0;
	}
	if( !who->query_temp("pending/jiang_herb_debt") ) {
		do_chat("江述仁看了一眼﹐說道﹕咦﹐紫靈芝﹖你從哪裡找到的﹖\n");
		return 0;
	}
	do_chat(({
		"江述仁接過紫靈芝﹐仔細端詳了一番﹐眼睛一亮。\n",
		"江述仁驚喜道﹕果然是紫靈芝﹗品相極佳﹐太好了﹗\n",
		"江述仁說道﹕有了這株紫靈芝﹐解毒丹的藥引便齊了。\n",
		"江述仁拱手道﹕多謝你了﹐請收下這些東西﹐算是我的一點心意。\n",
		(: do_reward, who :),
	}));
	return 1;
}

void do_reward(object player)
{
	if( !player || !present(player, environment()) ) return;
	if( player->query("quest/jiang_herb_debt_done") ) return;

	player->set("quest/jiang_herb_debt_done", 1);
	player->delete_temp("pending/jiang_herb_debt");
	player->gain_score("quest", 80);
	player->carry_money("silver", 2);

	message_vision(
		"江述仁從藥箱中取出幾錠碎銀﹐遞給$N。\n",
		player);
	tell_object(player, "( 你獲得了 2 兩銀子 )\n");
}

void relay_say(object ob, string msg)
{
	if( !userp(ob) ) return;
	if( is_fighting() || is_chatting() ) return;

	if( strsrch(msg, "藥材") >= 0 || strsrch(msg, "債") >= 0
	||  strsrch(msg, "幫忙") >= 0 || strsrch(msg, "忙") >= 0
	||  strsrch(msg, "欠") >= 0 || strsrch(msg, "煉丹") >= 0 ) {
		if( ob->query("quest/jiang_herb_debt_done") ) {
			do_chat("江述仁微笑道﹕多虧了你﹐解毒丹已經煉成了﹐債也還清了。\n");
			return;
		}
		if( ob->query_temp("pending/jiang_herb_debt") ) {
			do_chat(({
				"江述仁說道﹕紫靈芝長在藥草園的石井壁上﹐你去那裡找找看。\n",
				"江述仁說道﹕到了藥草園﹐仔細搜尋那口石井便是。\n",
			}));
			return;
		}
		do_chat(({
			"江述仁放下手中的藥方﹐嘆了口氣。\n",
			"江述仁說道﹕不瞞你說﹐前些日子收了一批藥材﹐還沒來得及付帳。\n",
			"江述仁說道﹕偏偏煉解毒丹還差一味藥引——紫靈芝。\n",
			"江述仁說道﹕這紫靈芝極為罕見﹐只在陰暗潮濕的地方才能生長。\n",
			"江述仁打量了你一番﹐說道﹕聽說咱們藥草園裡的石井壁上\n"
			"    偶爾會長出紫靈芝﹐但我身子骨不好﹐下不去。\n",
			"江述仁說道﹕你若願意幫忙﹐到藥草園去仔細搜尋那口石井﹐\n"
			"    說不定能找到。\n",
		}));
		ob->set_temp("pending/jiang_herb_debt", 1);
		return;
	}

	if( strsrch(msg, "靈芝") >= 0 || strsrch(msg, "紫靈芝") >= 0 ) {
		if( ob->query_temp("pending/jiang_herb_debt") )
			do_chat("江述仁說道﹕紫靈芝就在藥草園的石井壁上﹐你去找找看吧。\n");
		else
			do_chat("江述仁說道﹕紫靈芝啊﹐那可是煉解毒丹的珍貴藥引﹐極為難得。\n");
		return;
	}
}
