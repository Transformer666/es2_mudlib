// ouyang_wuji.c - 歐陽無極 茅山掌門（隱風觀）

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("歐陽無極", ({"ouyang wuji", "ouyang", "wuji"}));
	set("nickname", "茅山掌門");
	set_attr("str", 20);
	set_attr("dex", 22);
	set_attr("con", 20);
	set_attr("int", 26);
	set_attr("wis", 28);
	set_attr("spi", 30);
	set_attr("cps", 22);
	set_race("human");
	set_class("taoist");
	set_level(65);

	set_skill("sword", 90);
	set_skill("maoshan sword", 100);
	set_skill("maoshan neigong", 95);
	set_skill("dodge", 80);
	set_skill("parry", 75);
	set_skill("force", 90);

	advance_stat("gin", 250);
	advance_stat("kee", 250);
	advance_stat("sen", 200);

	set("age", 62);
	set("gender", "male");
	set("attitude", "peaceful");
	set("long",
		"歐陽無極是茅山派現任掌門﹐身穿一件月白色道袍﹐頭挽道髻﹐\n"
		"手持一柄古樸的拂塵。他面容清瞿﹐雙目深邃如潭﹐隱隱透著一\n"
		"股出塵脫俗的仙氣。他在隱風觀中修行數十年﹐精通茅山劍法與\n"
		"內功心法﹐是茅山派當世最高的修為者。\n");

	set("chat_chance", 1);
	set("chat_msg", ({
		"歐陽無極撫鬚道﹕道可道﹐非常道﹐修道之人﹐貴在悟性。\n",
		"歐陽無極閉目養神﹐拂塵輕搖﹐一副仙風道骨的模樣。\n",
	}));

	setup();
	carry_object(STOCK_WEAPON("longsword"))->wield();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	carry_money("silver", 50);
	set_temp("apply/vision_of_ghost", 1);
}

void set_flag(object me)
{
	if( me && present(me, environment()) ) {
		if( me->query_class() != "commoner"
		||	me->query("title") )
			return;
		me->set_temp("pending/ouyang_wuji", 1);
	}
	else
		do_chat("歐陽無極微微搖頭﹐自語道﹕緣來緣去﹐不可強求。\n");
}

int accept_apprentice(object me)
{
	if( is_chatting() ) return 0;
	if( me->query_temp("pending/ouyang_wuji") ) return 1;
	if( me->query("title") ) {
		do_chat("歐陽無極搖了搖頭﹐說道﹕你已有師承﹐貧道不宜再收。\n");
		return 0;
	}
	do_chat(({
		"歐陽無極上下打量了你一番﹐說道﹕想入茅山門下？\n",
		"歐陽無極說道﹕茅山道術﹐非有道緣者不傳﹐你可想清楚了？\n",
		"歐陽無極撫鬚微笑﹐說道﹕罷了﹐老道觀你倒有幾分道骨﹐你若誠心﹐便再來找我。\n",
		(: set_flag, me :)
	}));
	return 0;
}

int init_apprentice(object me)
{
	if( me->query_class() != "commoner" ) {
		do_chat(({
			"歐陽無極搖了搖頭﹐說道﹕你既已入別派﹐豈宜再習道術？\n",
			"歐陽無極揮了揮拂塵﹐說道﹕去吧。\n"
		}));
		return 1;
	}
	if( ::init_apprentice(me) ) {
		seteuid(getuid());
		me->set_class("taoist");
		me->set("title", "茅山派弟子");
		do_chat(({
			"歐陽無極點了點頭﹐說道﹕好﹐從今日起你便是茅山弟子了。\n",
			"歐陽無極說道﹕茅山道術博大精深﹐你先修煉靜心之功﹐切莫急躁。\n",
			"歐陽無極揮了揮拂塵﹐說道﹕去吧﹐好生修行﹐莫墮了茅山的名頭。\n"
		}));
	}
}

int acquire_skill(object ob, string skill)
{
	if( is_chatting() )
		return notify_fail("你最好等掌門的話說完再插嘴。\n");
	if( !ob->is_apprentice_of(this_object()) ) return 0;

	switch(skill) {
	case "maoshan sword":
		if( !ob->query_learn(skill) ) {
			say("歐陽無極點了點頭﹐說道﹕好﹐貧道這就傳你茅山劍法。\n");
			message_vision("$N將茅山劍法的入門心要傳授給$n。\n", this_object(), ob);
			ob->improve_skill(skill, random(ob->query_attr("spi")) + 1);
		}
		break;
	case "maoshan neigong":
		if( !ob->query_learn(skill)
		&&	ob->query_skill("maoshan sword") >= 30 ) {
			say("歐陽無極說道﹕你劍法已有小成﹐可以修習內功心法了。\n");
			message_vision("$N將茅山內功的入門口訣傳授給$n。\n", this_object(), ob);
			ob->improve_skill(skill, random(ob->query_attr("wis")) + 1);
		}
		break;
	default:
		return 0;
	}

	do_chat(({
		"歐陽無極說道﹕道法自然﹐萬物歸一﹐修煉之道在於領悟天地之理。\n",
		"歐陽無極說道﹕你好自修行﹐切莫辜負了這番道緣。\n",
	}));

	return 1;
}
