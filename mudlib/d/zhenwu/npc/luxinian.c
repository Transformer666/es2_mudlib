// vim: syntax=lpc

#include <npc.h>

inherit F_SOLDIER;

void create()
{
	set_name("魯熙年", ({"luxinian", "lu xinian", "lu"}));
	set_attr("str", 24);
	set_attr("dex", 22);
	set_attr("con", 26);
	set_attr("int", 20);
	set_attr("spi", 18);
	set_attr("wis", 22);
	set_race("human");
	set_class("soldier");
	set_level(55);

	set_skill("pike", 100);
	set_skill("tactic", 90);
	set_skill("dodge", 75);
	set_skill("parry", 80);
	set_skill("unarmed", 60);

	set("age", 48);
	set("gender", "male");
	set("long",
		"魯熙年是振武軍營的教頭﹐曾經是邊疆戰場上赫赫有名的猛將﹐\n"
		"因傷退居二線後﹐便在軍營中負責訓練新兵。他身材魁梧﹐面容剛\n"
		"毅﹐一雙銳利的眼睛透著百戰沙場的殺氣。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"魯熙年說道：戰場之上﹐一招不慎便是送命﹐不可不慎。\n",
		"魯熙年巡視著練武場﹐不時指點幾句。\n",
	}));
	setup();
	carry_object(STOCK_WEAPON("pike"))->wield();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	carry_money("coin", 200);
	set_temp("apply/vision_of_ghost", 1);
}

void set_flag(object me)
{
	if( me && present(me, environment()) ) {
		if( me->query_class() != "commoner"
		||	me->query("title") )
			return;
		me->set_temp("pending/luxinian", 1);
	}
	else
		do_chat("魯熙年哼了一聲﹐說道﹕人都跑了﹐沒出息。\n");
}

int accept_apprentice(object me)
{
	if( is_chatting() ) return 0;
	if( me->query_temp("pending/luxinian") ) return 1;
	if( me->query("title") ) {
		do_chat("魯熙年說道﹕你已有師門﹐軍營不收二心之人。\n");
		return 0;
	}
	do_chat(({
		"魯熙年上下打量了你一番﹐說道﹕想入軍營﹖\n",
		"魯熙年說道﹕軍人以服從命令為天職﹐以保家衛國為己任。\n",
		"魯熙年說道﹕你若受得了苦﹐明日再來報到。\n",
		(: set_flag, me :)
	}));
	return 0;
}

int init_apprentice(object me)
{
	if( me->query_class() != "commoner" ) {
		do_chat(({
			"魯熙年說道﹕你既已入別門﹐便不宜再從軍了。\n",
			"魯熙年揮了揮手﹐說道﹕去吧。\n"
		}));
		return 1;
	}
	if( ::init_apprentice(me) ) {
		seteuid(getuid());
		me->set_class("soldier");
		me->set("title", "振武軍營新兵");
		do_chat(({
			"魯熙年點了點頭﹐說道﹕好﹐從今日起你便是振武軍營的人了。\n",
			"魯熙年說道﹕先從基本功練起﹐不許偷懶。\n",
			"魯熙年說道﹕下去吧﹐明日卯時操練。\n"
		}));
	}
}

int acquire_skill(object ob, string skill)
{
	if( is_chatting() )
		return notify_fail("你最好等教頭的話說完再插嘴。\n");
	if( !ob->is_apprentice_of(this_object()) ) return 0;

	switch(skill) {
	case "tactic":
		if( !ob->query_learn(skill) ) {
			say("魯熙年點了點頭，說道：好，我傳你戰術兵法。\n");
			message_vision("$N將振武軍營的戰術兵法傳授給$n。\n", this_object(), ob);
			ob->improve_skill(skill, random(ob->query_attr("int")) + 1);
		}
		break;
	case "pike":
		if( !ob->query_learn(skill) ) {
			say("魯熙年取過長槍，說道：看好了。\n");
			message_vision("$N將振武軍營的槍法傳授給$n。\n", this_object(), ob);
			ob->improve_skill(skill, random(ob->query_attr("str")) + 1);
		}
		break;
	default:
		return 0;
	}

	do_chat(({
		"魯熙年說道：軍中無戲言﹐練功亦是如此。\n",
		"魯熙年說道：好好練﹐莫讓老夫失望。\n",
	}));

	return 1;
}
