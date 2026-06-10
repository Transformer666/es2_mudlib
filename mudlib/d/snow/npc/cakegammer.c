// cakegammer.c -- 張婆婆，雪亭鎮新手任務 1 的委託人
//
// 任務流程（旗標存在玩家身上：quest/snow_newbie）：
//   未開始 (0)  : 玩家 ask grandma about 任務  -> 婆婆給「油紙包」，旗標設為 1
//   進行中 (1)  : 玩家把油紙包帶到廣場中央交給孫兒「阿福」(/d/snow/npc/afu)
//                 阿福收下後把玩家身上的旗標設為 2
//   已送達 (2)  : 玩家回來 ask grandma about 任務 -> 領賞，旗標設為 3
//   已完成 (3)  : 不再重複給賞（防止重複領獎）

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("張婆婆", ({ "grandma", "zhang grandma", "zhang" }) );
	set_race("human");
	set_class("commoner");
	set_level(2);

	// FIX(2026-06-10, npc-physique): 明定八項屬性，蓋掉 set_level 觸發的
	// 隨機屬性——否則 dex 滾到最高時，體格句會與「手腳雖然慢了」矛盾。
	// str 最高：搭配年齡分級後顯示「雖然上了年紀，身子骨卻依然硬朗結實」。
	set_attr("str", 15);
	set_attr("con", 14);
	set_attr("cps", 14);
	set_attr("wis", 14);
	set_attr("int", 13);
	set_attr("spi", 13);
	set_attr("cor", 12);
	set_attr("dex", 10);

	set("gender", "female");
	set("age", 68);
	set("long",
		"一個慈眉善目的老婆婆﹐守著客棧角落一個賣點心的小攤子﹐手腳\n"
		"雖然慢了﹐卻收拾得乾乾淨淨。她不時往門外張望﹐似乎有甚麼心\n"
		"事。你或許可以問問她﹕ask grandma about 任務。\n");
	setup();
	carry_object("/obj/area/obj/cloth")->wear();
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player()) ) {
		int q = this_player()->query("quest/snow_newbie");
		if( q == 1 )
			do_chat((: command,
				"say 這位小哥﹐我那油紙包可送到我孫兒阿福手上了麼﹖" :));
		else if( !q )
			do_chat((: command,
				"say 唉﹐人老了腿腳不便﹐倒有件小事想央人幫忙 ..." :));
	}
}

// 把一個油紙包交到玩家手上（先複製到自己身上，再 give 出去）
private void give_parcel(object who)
{
	object parcel;

	if( !who || environment(who) != environment() ) {
		command("say 咦 ... 人呢﹖");
		return;
	}
	parcel = new(__DIR__"obj/pastry_parcel");
	parcel->move(this_object());
	command("give pastry parcel to " + who->query("id"));
}

// 領賞：給少許銅錢、一個饅頭、再加一點點經驗
private void give_reward(object who)
{
	object coin, manto;

	if( !who || environment(who) != environment() ) return;

	coin = new("/obj/money/coin");
	coin->set_amount(50);
	if( !coin->move(who) ) coin->move(environment());

	manto = new("/obj/food/manto");
	if( !manto->move(who) ) manto->move(environment());

	who->gain_score("survive", 100);

	message_vision(
		"張婆婆從攤子上取了一個熱騰騰的饅頭﹐連同一串銅錢一起塞進$N手裡。\n",
		who);
}

int do_ask(string arg)
{
	object me = this_player();
	int q;

	if( !arg || (arg != "grandma about 任務"
		&&   arg != "zhang about 任務"
		&&   arg != "grandma about quest"
		&&   arg != "grandma about task") )
		return notify_fail("你想問張婆婆甚麼﹖（試試 ask grandma about 任務）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("張婆婆正忙著﹐沒空理你。\n");

	q = me->query("quest/snow_newbie");

	// 已全部完成
	if( q >= 3 ) {
		do_chat((: command,
			"say 多虧了你﹐阿福那孩子可開心了﹐婆婆再謝謝你啦﹗" :));
		return 1;
	}

	// 已送達，回來領賞
	if( q == 2 ) {
		// 同步給賞、即記旗標（give_reward 為直接 new+move﹐玩家此刻必在場）。
		// 不把給賞放進延遲的 do_chat——免玩家於回呼前離場致賞沒領、旗標卻記完成而卡關。
		give_reward(me);
		me->set("quest/snow_newbie", 3);
		do_chat(({
			"張婆婆聽說阿福收到了點心﹐笑得合不攏嘴。\n",
			(: command, "say 真是個熱心腸的好孩子﹐這點東西你拿著﹐別嫌少﹗" :),
		}));
		return 1;
	}

	// 任務進行中（還沒送到）
	if( q == 1 ) {
		if( present("pastry parcel", me) )
			do_chat((: command,
				"say 那油紙包你帶在身上了﹐快到廣場中央的大榕樹下﹐"
				"找我孫兒阿福﹐把東西交(give)給他罷。" :));
		else
			// 萬一玩家把油紙包弄丟了，補一個給他
			do_chat(({
				"張婆婆嘆了口氣﹐又包了一份點心。\n",
				(: command, "say 怎麼東西不見了﹖罷了罷了﹐婆婆再給你包一份。" :),
				(: give_parcel, me :),
			}));
		return 1;
	}

	// 尚未接任務：交付油紙包，旗標設為 1
	me->set("quest/snow_newbie", 1);
	do_chat(({
		(: command, "say 我那孫兒阿福﹐這時候多半又爬到廣場中央的大榕樹上玩去了。" :),
		(: command, "say 婆婆給他包了份點心﹐勞煩你替我送(give)到他手上﹐好麼﹖" :),
		(: give_parcel, me :),
	}));
	return 1;
}

int accept_fight()
{
	do_chat((: command, "say 哎喲﹐老婆子可不會打架﹐你饒了我罷﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
