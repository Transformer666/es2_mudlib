// patrolman.c -- 巡檢，大內巡院的緝事官員，京畿支線任務的委託人
//
// 任務流程（旗標存在玩家身上：quest/capital_errand）：
//   未開始 (0)  : 玩家 ask patrolman about 任務 -> 巡檢交付「密函」﹐旗標設為 1
//   進行中 (1)  : 玩家把密函帶到史部尚書府前﹐交(give)給「門房」(/d/capital/npc/gateman)
//                 門房收下後回給「回執」﹐並把玩家身上的旗標推進為 2（推進在 gateman.c）
//   已送達 (2)  : 玩家把回執帶回後海茶館交(give)給巡檢 -> 領賞﹐旗標設為 3
//   已完成 (3)  : 不再重複給賞（防止重複領獎）

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("巡檢", ({ "patrolman", "xunjian", "officer" }) );
	set_attr("str", 22);
	set_attr("con", 20);
	set_race("human");
	set_class("fighter");
	set_level(12);
	set_skill("unarmed", 30);
	set_skill("sword", 30);
	set_skill("dodge", 30);
	set_skill("parry", 30);

	set("gender", "male");
	set("age", 38);
	set("long",
		"一位大內巡院的緝事官員﹐身著玄色勁裝﹐腰懸一柄三尺長劍﹐\n"
		"眉宇間透著一股精悍幹練的氣度。他坐在臨湖的雅座裡﹐看似品\n"
		"茗閒坐﹐一雙利眼卻不住地往湖面上掃視﹐似有公務在身。你或\n"
		"許可以問問他﹕ask patrolman about 任務。\n");
	setup();
	carry_object("/obj/area/obj/cloth")->wear();
	carry_money("coin", 500);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player()) ) {
		int q = this_player()->query("quest/capital_errand");
		if( q == 1 || q == 2 )
			do_chat((: command,
				"say 這位壯士﹐我那封密函可送到尚書府門房手上了麼﹖" :));
		else if( !q )
			do_chat((: command,
				"say 唉﹐巡院公務纏身﹐眼下倒有樁差事想央個信得過的人去辦 ..." :));
	}
}

// 把一封密函交到玩家手上（先複製到自己身上，再 give 出去）
private void give_dispatch(object who)
{
	object dispatch;

	if( !who || environment(who) != environment() ) {
		command("say 咦 ... 人呢﹖");
		return;
	}
	dispatch = new(__DIR__"obj/dispatch");
	dispatch->move(this_object());
	command("give sealed dispatch to " + who->query("id"));
}

// 領賞：給銅錢、一顆山豬果（提神）、一塊月餅（充飢），再加經驗與旅行見聞
private void give_reward(object who)
{
	object coin, berry, cake;

	if( !who || environment(who) != environment() ) return;

	coin = new("/obj/money/coin");
	coin->set_amount(300);
	if( !coin->move(who) ) coin->move(environment());

	berry = new("/obj/medication/boar_berry");
	if( !berry->move(who) ) berry->move(environment());

	cake = new("/obj/food/mooncake");
	if( !cake->move(who) ) cake->move(environment());

	who->gain_score("survive", 300);
	who->gain_score("explorer fame", 150);

	message_vision(
		"巡檢頷首讚許﹐自袖中取出一錠銀錢﹐又叫茶博士備了山豬果與"
		"月餅﹐一併送到$N手裡。\n",
		who);
}

int do_ask(string arg)
{
	object me = this_player();
	int q;

	if( !arg || (arg != "patrolman about 任務"
		&&   arg != "xunjian about 任務"
		&&   arg != "patrolman about quest"
		&&   arg != "patrolman about task") )
		return notify_fail("你想問巡檢甚麼﹖（試試 ask patrolman about 任務）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("巡檢正忙著﹐沒空理你。\n");

	q = me->query("quest/capital_errand");

	// 已全部完成
	if( q >= 3 ) {
		do_chat((: command,
			"say 上回那趟差事多虧壯士幫襯﹐巡院上下都記著你的人情﹐再謝過了﹗" :));
		return 1;
	}

	// 已送達，回來交回執（理應用 give 交付，這裡只作提示）
	if( q == 2 ) {
		if( present("signed receipt", me) )
			do_chat((: command,
				"say 回執取回來啦﹖快把那紙回執交(give)給我罷﹗" :));
		else
			do_chat((: command,
				"say 咦﹐門房的回執呢﹖你莫不是把回執弄丟了﹖快回尚書府門前找門房補一紙。" :));
		return 1;
	}

	// 任務進行中（還沒送到）
	if( q == 1 ) {
		if( present("sealed dispatch", me) )
			do_chat((: command,
				"say 那密函你帶在身上了﹐出茶館往北到後海湖﹐轉東過皇城廣場﹐"
				"再往東便是史部尚書府前﹐把密函交(give)給門房﹐取了回執回來。" :));
		else
			// 萬一玩家把密函弄丟了，補一封給他
			do_chat(({
				"巡檢皺了皺眉﹐又自公文匣裡取出一封備用的密函重新封緘。\n",
				(: command, "say 怎麼東西不見了﹖罷了﹐我這裡尚有副本﹐再給你一封。" :),
				(: give_dispatch, me :),
			}));
		return 1;
	}

	// 尚未接任務：交付密函，旗標設為 1
	me->set("quest/capital_errand", 1);
	do_chat(({
		(: command, "say 近來這後海湖夜半屢有異響﹐巡院疑心湖底別有蹊蹺﹐須得知會尚書府一聲。" :),
		(: command, "say 我這裡有封要緊的密函﹐勞煩壯士替我送(give)到史部尚書府前﹐交給那邊的門房。" :),
		(: command, "say 出茶館往北﹐到後海湖轉東過皇城廣場﹐再往東即是尚書府前。"
			"取了門房的回執帶回來給我﹐我重重有賞﹗" :),
		(: give_dispatch, me :),
	}));
	return 1;
}

// 收下回執：確認是任務信物且玩家已送達(旗標 2)，推進旗標 2 -> 3 並領賞
int accept_object(object who, object ob)
{
	if( !ob->id("signed receipt") ) {
		do_chat((: command, "say 這個我用不上﹐壯士還是自個兒留著罷。" :));
		return 0;
	}

	// 不是已送達的任務玩家（或已交過），仍收下避免卡物，但不重複給賞
	if( who->query("quest/capital_errand") != 2 ) {
		do_chat((: command, "say 多謝壯士﹗" :));
		return 1;
	}

	who->set("quest/capital_errand", 3);
	do_chat(({
		(: command, "say 正是尚書府門房的回執﹗密函既已送到﹐這趟差事壯士辦得漂亮﹗" :),
		(: give_reward, who :),
		(: command, "say 這點酬勞壯士拿著﹐山豬果提神﹐月餅充飢。日後巡院有事﹐還要請壯士多多幫襯﹗" :),
	}));
	return 1;
}

int accept_fight(object ob)
{
	do_chat((: command, "say 放肆﹗竟敢在天子腳下對巡院的人動粗﹐你是活得不耐煩了﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
