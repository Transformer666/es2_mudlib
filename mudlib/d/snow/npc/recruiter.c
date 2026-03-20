// NPC: /d/snow/npc/recruiter.c

#include <npc.h>

inherit F_SOLDIER;

void create()
{
	set_name("招兵官", ({"recruiter", "officer"}));
	set_attr("str", 20);
	set_attr("dex", 18);
	set_attr("con", 20);
	set_attr("int", 15);
	set_attr("wis", 14);
	set_attr("spi", 14);
	set_race("human");
	set_class("soldier");
	set_level(25);

	set_skill("blade", 60);
	set_skill("parry", 50);
	set_skill("dodge", 40);

	set("age", 40);
	set("gender", "male");
	set("long",
		"這位招兵官身穿一套半舊的軍甲﹐腰間佩著一把制式長刀﹐\n"
		"目光銳利地打量著每一個走進軍營的人。他的左臉頰上有一道\n"
		"長長的傷疤﹐為他增添了幾分威嚴。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"招兵官大聲喊道：鎮部招兵﹐有膽識的好漢前來報名﹗\n",
		"招兵官沉聲道：保家衛國﹐從軍光榮﹗\n",
	}));

	setup();
	carry_money("silver", 5);
	carry_object(STOCK_WEAPON("blade"))->wield();
	carry_object(STOCK_ARMOR("armor"))->wear();
}

void set_flag(object me)
{
	if( me && present(me, environment()) ) {
		if( me->query_class() != "commoner"
		||	me->query("title") )
			return;
		me->set_temp("pending/recruiter", 1);
	}
	else
		do_chat("招兵官搖了搖頭﹐說道﹕人都跑了﹐看來是個膽小鬼。\n");
}

int accept_apprentice(object me)
{
	if( is_chatting() ) return 0;
	if( me->query_temp("pending/recruiter") ) return 1;
	if( me->query("title") ) {
		do_chat("招兵官道﹕你已有師門﹐軍營不收有門派的人。\n");
		return 0;
	}
	do_chat(({
		"招兵官上下打量了你一番﹐說道﹕想當兵﹖\n",
		"招兵官說道﹕當兵可不是兒戲﹐要吃得了苦﹐受得了罪。\n",
		"招兵官說道﹕你若真心想入伍﹐再來找我報名。\n",
		(: set_flag, me :)
	}));
	return 0;
}

int init_apprentice(object me)
{
	if( me->query_class() != "commoner" ) {
		do_chat(({
			"招兵官說道﹕你已有所屬﹐不能再入軍營了。\n",
			"招兵官揮了揮手﹐說道﹕走吧。\n"
		}));
		return 1;
	}
	if( ::init_apprentice(me) ) {
		seteuid(getuid());
		me->set_class("soldier");
		me->set("title", "鎮部新兵");
		do_chat(({
			"招兵官點了點頭﹐說道﹕好﹐從今天起你就是鎮部的兵了。\n",
			"招兵官說道﹕先從基本的刀法和操練開始﹐不許偷懶。\n",
			"招兵官說道﹕去吧﹐好好鍛鍊﹐別給軍營丟臉。\n"
		}));
	}
}

int acquire_skill(object ob, string skill)
{
	if( is_chatting() )
		return notify_fail("你最好等長官的話說完再插嘴。\n");
	if( !ob->is_apprentice_of(this_object()) ) return 0;

	switch(skill) {
	case "blade":
		if( !ob->query_learn(skill) ) {
			say("招兵官點了點頭﹐說道﹕好﹐我來教你基本刀法。\n");
			message_vision("$N將軍營制式刀法傳授給$n。\n", this_object(), ob);
			ob->improve_skill(skill, random(ob->query_attr("str")) + 1);
		}
		break;
	case "parry":
		if( !ob->query_learn(skill)
		&&	ob->query_skill("blade") >= 30 ) {
			say("招兵官說道﹕刀法有些底子了﹐來﹐學學格擋。\n");
			message_vision("$N將格擋技巧傳授給$n。\n", this_object(), ob);
			ob->improve_skill(skill, random(ob->query_attr("dex")) + 1);
		}
		break;
	default:
		return 0;
	}

	do_chat(({
		"招兵官說道﹕當兵最重要的就是紀律和服從。\n",
		"招兵官說道﹕勤加練習﹐莫要懈怠。\n",
	}));

	return 1;
}

int accept_object(object player, object ob)
{
	object reply;

	if( !userp(player) ) return 0;
	if( !ob->id("arbao letter") && !ob->id("abao letter") ) return 0;
	if( !player->query_temp("pending/arbao_deliver") ) return 0;

	reply = new(__DIR__"obj/recruiter_reply");
	reply->move(player);
	player->delete_temp("pending/arbao_deliver");
	player->set_temp("pending/arbao_reply", 1);

	do_chat(({
		"招兵官接過信件﹐拆開看了看。\n",
		"招兵官皺了皺眉﹐說道﹕阿明﹖我記得這小子﹐年初隨著部隊調去南邊了。\n",
		"招兵官說道﹕他在軍中表現不錯﹐你放心﹐人好好的。\n",
		"招兵官提筆寫了幾行字﹐蓋上軍營的印鑑﹐遞給你。\n",
		"招兵官說道﹕這封回信你帶回去給那姑娘吧﹐省得她擔心。\n",
	}));
	return 1;
}
