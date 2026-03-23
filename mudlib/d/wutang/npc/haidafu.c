// haidafu.c
// Quest: 陰沉男子的委託 (haidafu_herb)
// Flow: talk -> learn about poisoned brother -> find golden_herb on wushan
//       -> give herb to haidafu -> reward

#include <npc.h>

inherit F_FIGHTER;

void do_reward(object player);

void create()
{
    set_name("陰沉男子", ({"haidafu", "man"}));
    set_attr("str", 22);
    set_attr("con", 20);
    set_attr("dex", 20);
    set_attr("int", 18);
    set_attr("wis", 18);
    set_race("human");
    set_class("fighter");
    set_level(40);

    set_skill("sword", 90);
    set_skill("dodge", 80);
    set_skill("parry", 70);
    set_skill("unarmed", 60);

    set("age", 45);
    set("attitude", "peaceful");
    set("long",
	"一個面色陰沉的中年男子﹐穿著一件灰色長袍﹐坐在角落裡默默\n"
	"地喝著茶﹐看起來不像是普通人。\n");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_object( STOCK_WEAPON("longsword") )->wield();
    carry_money("coin", 500);
}

void do_reward(object player)
{
    if( !player || !present(player, environment()) ) return;
    if( player->query("quest/haidafu_herb_done") ) return;

    player->set("quest/haidafu_herb_done", 1);
    player->delete_temp("pending/haidafu_herb");
    player->gain_score("quest", 80);

    message_vision("$N從懷中取出一錠銀子遞給$n。\n", this_object(), player);
    player->carry_money("silver", 2);
    tell_object(player, "( 你獲得了二兩銀子 )\n");
}

int accept_object(object who, object ob)
{
    if( !ob->id("golden herb") ) return 0;

    if( who->query("quest/haidafu_herb_done") ) {
	do_chat("陰沉男子搖了搖頭﹐說道﹕不必了﹐已經夠了。\n");
	return 0;
    }
    if( !who->query_temp("pending/haidafu_herb") ) {
	do_chat("陰沉男子疑惑地看著你﹐說道﹕這是什麼﹖\n");
	return 0;
    }

    do_chat(({
	"陰沉男子接過金線蓮﹐仔細端詳了一番。\n",
	"陰沉男子臉上浮現一絲感激之色﹐說道﹕就是這個﹐多謝你了。\n",
	"陰沉男子說道﹕有了這株金線蓮﹐我兄弟的毒傷就有救了。\n",
	"陰沉男子沉吟片刻﹐說道﹕你幫了我一個大忙﹐這點銀子算是我的一點心意。\n",
	(: do_reward, who :),
    }));
    return 1;
}

void relay_say(object ob, string msg)
{
    if( !userp(ob) ) return;
    if( is_fighting() || is_chatting() ) return;

    if( strsrch(msg, "心事") >= 0 || strsrch(msg, "煩惱") >= 0
    ||  strsrch(msg, "怎麼了") >= 0 || strsrch(msg, "幫忙") >= 0 ) {
	if( ob->query("quest/haidafu_herb_done") ) {
	    do_chat("陰沉男子微微點頭﹐說道﹕多虧了你﹐我兄弟已經好多了。\n");
	    return;
	}
	if( ob->query_temp("pending/haidafu_herb") >= 2 ) {
	    do_chat("陰沉男子說道﹕金線蓮只長在武山的山路上﹐你替我找找看吧。\n");
	    return;
	}
	if( ob->query_temp("pending/haidafu_herb") == 1 ) {
	    do_chat(({
		"陰沉男子嘆了口氣﹐說道﹕我一個兄弟中了毒﹐需要一株金線蓮來解毒。\n",
		"陰沉男子說道﹕可是這種藥草極為罕見﹐我在鎮上的藥鋪打聽過﹐都沒有貨。\n",
		"陰沉男子說道﹕聽說武山的山路上偶爾能找到野生的金線蓮﹐可惜我脫不開身。\n",
		"陰沉男子看了你一眼﹐說道﹕你若是有空上山的話﹐幫我留意一下。\n",
	    }));
	    ob->set_temp("pending/haidafu_herb", 2);
	    return;
	}
	do_chat(({
	    "陰沉男子警覺地看了你一眼﹐但隨即放鬆下來。\n",
	    "陰沉男子淡淡地說道﹕我在等一個人 ... 不過等了好幾天了也沒消息。\n",
	    "陰沉男子嘆了口氣﹐沒有再說下去。\n",
	}));
	ob->set_temp("pending/haidafu_herb", 1);
	return;
    }

    if( strsrch(msg, "金線蓮") >= 0 || strsrch(msg, "藥草") >= 0
    ||  strsrch(msg, "兄弟") >= 0 || strsrch(msg, "中毒") >= 0 ) {
	if( ob->query("quest/haidafu_herb_done") ) {
	    do_chat("陰沉男子說道﹕藥已經配好了﹐不需要了。\n");
	    return;
	}
	if( !ob->query_temp("pending/haidafu_herb") )
	    ob->set_temp("pending/haidafu_herb", 1);
	if( ob->query_temp("pending/haidafu_herb") < 2 ) {
	    do_chat(({
		"陰沉男子說道﹕我兄弟中了一種奇毒﹐普通的草藥根本無效。\n",
		"陰沉男子說道﹕只有金線蓮才能解這種毒﹐聽說武山上偶爾能找到。\n",
		"陰沉男子說道﹕你要是願意幫忙﹐去武山的山路上找找看吧。\n",
	    }));
	    ob->set_temp("pending/haidafu_herb", 2);
	    return;
	}
	do_chat("陰沉男子說道﹕金線蓮應該長在武山的山路上﹐你去找找看吧。\n");
	return;
    }
}
