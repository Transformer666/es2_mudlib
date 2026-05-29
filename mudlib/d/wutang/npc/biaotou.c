// biaotou.c -- 鏢頭，鎮遠鏢局的總鏢頭，五堂鎮支線任務的委託人
//
// 任務流程（旗標存在玩家身上：quest/wutang_cargo）：
//   未開始 (0)  : 玩家 ask biaotou about 任務 -> 鏢頭託玩家去尋回失落的鏢物﹐
//                 旗標設為 1﹐並指引玩家到鎮東的僻靜小巷找浣衣婦
//   進行中 (1)  : 玩家到小巷 ask washerwoman about 鏢物﹐浣衣婦交出鏢物﹐
//                 並把玩家旗標推進為 2（推進在 washerwoman.c）
//   已取回 (2)  : 玩家把鏢物帶回鏢局交(give)給鏢頭 -> 領賞﹐旗標設為 3
//   已完成 (3)  : 不再重複給賞（防止重複領獎）

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("鏢頭", ({ "biaotou", "escort master", "master" }) );
	set_attr("str", 24);
	set_attr("con", 22);
	set_race("human");
	set_class("fighter");
	set_level(20);
	set_skill("blade", 70);
	set_skill("parry", 60);
	set_skill("dodge", 60);
	set_skill("unarmed", 50);

	set("gender", "male");
	set("age", 45);
	set("long",
		"鎮遠鏢局的總鏢頭﹐一身洗得發白的勁裝﹐太陽穴高高鼓起﹐一望\n"
		"便知是個內外兼修的好手。他端坐在太師椅上﹐手裡摩挲著一柄油\n"
		"亮的厚背鋼刀﹐眉頭微鎖﹐似有樁煩心事。你或許可以問問他﹕\n"
		"ask biaotou about 任務。\n");
	setup();
	carry_object("/obj/area/obj/cloth")->wear();
	carry_money("coin", 400);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player()) ) {
		int q = this_player()->query("quest/wutang_cargo");
		if( q == 1 || q == 2 )
			do_chat((: command,
				"say 這位朋友﹐那只失落的鏢物可尋著了麼﹖" :));
		else if( !q )
			do_chat((: command,
				"say 唉﹐走了大半輩子鏢﹐頭一回在自家門口栽了跟頭 ..." :));
	}
}

// 領賞：給銅錢、一把匕首（防身用）、一塊月餅（充飢），再加經驗與旅行見聞
private void give_reward(object who)
{
	object coin, dagger, cake;

	if( !who || environment(who) != environment() ) return;

	coin = new("/obj/money/coin");
	coin->set_amount(200);
	if( !coin->move(who) ) coin->move(environment());

	dagger = new("/obj/area/obj/dagger");
	if( !dagger->move(who) ) dagger->move(environment());

	cake = new("/obj/food/mooncake");
	if( !cake->move(who) ) cake->move(environment());

	who->gain_score("survive", 200);
	who->gain_score("explorer fame", 100);

	message_vision(
		"鏢頭哈哈大笑﹐自腰間解下一串銅錢﹐又取了把防身的匕首和一塊"
		"月餅﹐一併塞到$N手裡。\n",
		who);
}

int do_ask(string arg)
{
	object me = this_player();
	int q;

	if( !arg || (arg != "biaotou about 任務"
		&&   arg != "master about 任務"
		&&   arg != "biaotou about quest"
		&&   arg != "biaotou about task") )
		return notify_fail("你想問鏢頭甚麼﹖（試試 ask biaotou about 任務）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("鏢頭正忙著﹐沒空理你。\n");

	q = me->query("quest/wutang_cargo");

	// 已全部完成
	if( q >= 3 ) {
		do_chat((: command,
			"say 上回那只鏢物多虧朋友尋了回來﹐鎮遠鏢局上下都念著你的好﹐再謝過了﹗" :));
		return 1;
	}

	// 已取回，回來交鏢物（理應用 give 交付，這裡只作提示）
	if( q == 2 ) {
		if( present("escort cargo", me) )
			do_chat((: command,
				"say 鏢物尋回來啦﹖快把那只漆盒交(give)給老夫罷﹗" :));
		else
			do_chat((: command,
				"say 咦﹐那只鏢物呢﹖朋友莫不是把漆盒弄丟了﹖快回東邊小巷找浣衣婦再取一回。" :));
		return 1;
	}

	// 任務進行中（還沒取到貨）
	if( q == 1 ) {
		do_chat((: command,
			"say 朋友出鏢局往南到路口﹐再往東便是那條僻靜小巷﹐"
			"到了 ask washerwoman about 鏢物﹐取了漆盒(give)帶回來給老夫便是。" :));
		return 1;
	}

	// q == 0：尚未接任務，旗標設為 1
	me->set("quest/wutang_cargo", 1);
	do_chat(({
		(: command, "say 不瞞朋友﹐前日一趟近鏢﹐押的是只描金漆盒﹐是城裡張員外託運的要緊物事。" :),
		(: command, "say 偏生那看鏢的小子貪杯誤事﹐過鎮東小巷時竟把漆盒給顛丟了﹗" :),
		(: command, "say 聽說是教那井邊浣衣的婦人拾了去。朋友若肯替老夫跑一趟﹐尋回那漆盒﹐老夫必有重謝﹗" :),
		(: command, "say 出鏢局往南到路口﹐再往東便是那條小巷。到了 ask washerwoman about 鏢物﹐"
			"取了漆盒(give)帶回來給老夫。" :),
	}));
	return 1;
}

// 收下鏢物：確認是任務信物且玩家已取回(旗標 2)，推進旗標 2 -> 3 並領賞
int accept_object(object who, object ob)
{
	if( !ob->id("escort cargo") ) {
		do_chat((: command, "say 這個鏢局用不上﹐朋友還是自個兒留著罷。" :));
		return 0;
	}

	// 不是已取回的任務玩家（或已交過），仍收下避免卡物，但不重複給賞
	if( who->query("quest/wutang_cargo") != 2 ) {
		do_chat((: command, "say 多謝朋友﹗" :));
		return 1;
	}

	who->set("quest/wutang_cargo", 3);
	do_chat(({
		(: command, "say 封條完好﹐正是張員外那只漆盒﹗朋友辦事真是俐落﹗" :),
		(: give_reward, who :),
		(: command, "say 這點酬勞朋友拿著﹐匕首防身﹐月餅充飢。日後過五堂鎮﹐鏢局便是朋友的去處﹗" :),
	}));
	return 1;
}

int accept_fight(object ob)
{
	do_chat((: command, "say 放肆﹗也不打聽打聽﹐鎮遠鏢局的場子也是你撒野的地方﹖" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
