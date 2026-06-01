// keeper.c -- 廟祝，雪亭鎮土地公廟的守廟老人，主線任務「卯木之兆」的委託人
//
// 故事背景（呼應神話設定）：三百年前皇城聖木被斷﹐侮天鬼元神破土；如今鎮上
//   那株老榕（雪亭鎮人喚作「卯木」）入夜竟有異響﹐廟祝心生不祥之兆﹐又見土地
//   神像無故落淚﹐自忖事關重大﹐欲將親筆密報呈報官府﹐卻苦於腿腳不便﹐遂央
//   過路的少俠代為投遞。這是「卯木之兆」主線的開端﹐後續尚有更大的疑團。
//
// 任務流程（旗標存在玩家身上：quest/main_omen）：
//   未開始 (0)  : 玩家 ask keeper about 主線（或 任務）-> 廟祝交付「密報」﹐旗標設為 1
//   進行中 (1)  : 玩家把密報帶到鄉校﹐交(give)給「師爺」(/d/snow/npc/clerk)
//                 師爺收下後回給「批文」﹐並把玩家身上的旗標推進為 2（推進在 clerk.c）
//   已送達 (2)  : 玩家把批文帶回土地公廟交(give)給廟祝 -> 領賞﹐旗標設為 3
//   已完成 (3)  : 不再重複給賞（防止重複領獎）

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("廟祝", ({ "keeper", "temple keeper" }) );
	set_race("human");
	set_class("commoner");
	set_level(3);

	set("gender", "male");
	set("age", 71);
	set("long",
		"一個守著土地公廟的白髮老廟祝﹐穿一身洗得發白的灰布道袍﹐\n"
		"成日替神龕添香、替香爐撥灰。這幾日他眉頭深鎖﹐不時望著鎮\n"
		"中那株老榕的方向出神﹐嘴裡喃喃念著些聽不真切的話。\n"
		"你或許可以問問他﹕ask keeper about 主線。\n");
	setup();
	carry_object("/obj/area/obj/cloth")->wear();
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player()) ) {
		int q = this_player()->query("quest/main_omen");
		if( q == 1 || q == 2 )
			do_chat((: command,
				"say 這位少俠﹐老朽那封密報﹐可送到鄉校的師爺手上了麼﹖" :));
		else if( !q )
			do_chat((: command,
				"say 罪過罪過 ... 那卯木夜半啼哭﹐怕不是甚麼好兆頭啊 ..." :));
	}
}

// 把一封密報交到玩家手上（先複製到自己身上，再 give 出去）
private void give_report(object who)
{
	object report;

	if( !who || environment(who) != environment() ) {
		command("say 咦 ... 人呢﹖");
		return;
	}
	report = new(__DIR__"obj/omen_report");
	report->move(this_object());
	command("give sealed report to " + who->query("id"));
}

// 領賞：給銅錢、一個饅頭充飢、一顆山豬果提神﹐再加經驗、俠義之舉與旅行見聞
private void give_reward(object who)
{
	object coin, manto, berry;

	if( !who || environment(who) != environment() ) return;

	coin = new("/obj/money/coin");
	coin->set_amount(150);
	if( !coin->move(who) ) coin->move(environment());

	manto = new("/obj/food/manto");
	if( !manto->move(who) ) manto->move(environment());

	berry = new("/obj/medication/boar_berry");
	if( !berry->move(who) ) berry->move(environment());

	who->gain_score("survive", 200);
	who->gain_score("emprise", 50);
	who->gain_score("explorer fame", 50);

	message_vision(
		"廟祝合十謝過﹐自神案下取出香油錢湊了一串銅錢﹐又取了個饅頭"
		"與一顆山豬果﹐一併塞到$N手裡。\n",
		who);
}

// 收下批文：玩家把師爺的批文(official reply)帶回交(give)給廟祝﹐確認任務已送達
// (quest/main_omen==2)﹐即同步領賞並把旗標推進為 3（完成）。
// 注意：原本只在 do_ask q==2 提示「把批文交給廟祝」﹐卻從未定義 accept_object﹐
//   give_reward 成了孤函永不被呼叫——主線「卯木之兆」卡死在旗標 2、領不到賞、
//   且 main_omen 永遠到不了 3﹐連帶 elder.c(main_omen2 gate main_omen>=3) 以後
//   整條主線都進不去。此函補上收件、給賞、推進旗標的缺口。
// 採同步給賞（非延遲 do_chat）﹐免玩家於回呼前離場致批文已被 give 銷除、賞卻沒領、
//   旗標卻記完成而卡關（與 d/fancheng boatman 一致的修法）。
int accept_object(object who, object ob)
{
	if( ob->id("official reply") ) {
		// 未送達 / 已完成：婉拒，不收下（避免吞批文、不重複給賞）
		if( who->query("quest/main_omen") != 2 ) {
			do_chat((: command,
				"say 這紙批文 ... 少俠且自個兒收著罷，時候未到。" :));
			return 0;
		}
		// 已送達：同步領賞、推進旗標為 3（批文由 give 指令於本函回 1 後自行銷除）
		give_reward(who);
		who->set("quest/main_omen", 3);
		do_chat(({
			(: command, "say 啊﹐這正是師爺的批文﹗少俠果然不負所託﹐將密報送到了官府﹐老朽這顆懸著的心總算落了地。" :),
			(: command, "say 卯木之事既已上達官府﹐想必會差人來查。少俠這趟辛苦﹐區區薄酬方纔已奉上﹐萬望笑納。日後若再聽見甚麼風聲﹐還望多留個心。" :),
		}));
		return 1;
	}

	// 其餘物事：婉拒，不收下（避免吞掉玩家的尋常物品）
	do_chat((: command, "say 這個老朽用不上﹐少俠還是自個兒留著罷。" :));
	return 0;
}

int do_ask(string arg)
{
	object me = this_player();
	int q;

	if( !arg || (arg != "keeper about 主線"
		&&   arg != "keeper about 任務"
		&&   arg != "temple keeper about 主線"
		&&   arg != "temple keeper about 任務"
		&&   arg != "keeper about quest"
		&&   arg != "keeper about task") )
		return notify_fail("你想問廟祝甚麼﹖（試試 ask keeper about 主線）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("廟祝正忙著﹐沒空理你。\n");

	q = me->query("quest/main_omen");

	// 已全部完成
	if( q >= 3 ) {
		do_chat(({
			(: command, "say 那封密報多虧少俠送到了官府﹐老朽這顆心總算放下些。" :),
			(: command, "say 只是 ... 卯木之事怕還沒完。少俠日後若再聽見甚麼風聲﹐還望多留個心。" :),
		}));
		return 1;
	}

	// 已送達，回來交批文（理應用 give 交付，這裡只作提示）
	if( q == 2 ) {
		if( present("official reply", me) )
			do_chat((: command,
				"say 師爺的批文取回來啦﹖快把那紙批文交(give)給老朽過目﹗" :));
		else
			do_chat((: command,
				"say 咦﹐師爺的批文呢﹖少俠莫不是弄丟了﹖快回鄉校找師爺補一紙。" :));
		return 1;
	}

	// 任務進行中（還沒送到）
	if( q == 1 ) {
		if( present("sealed report", me) )
			do_chat((: command,
				"say 那密報少俠帶在身上了﹐出廟往西到街道﹐一路往南到廣場﹐"
				"再往鎮西尋著鄉校﹐把密報交(give)給斷事的師爺﹐取了批文回來。" :));
		else
			// 萬一玩家把密報弄丟了，補一封給他
			do_chat(({
				"廟祝嘆了口氣﹐又自神案下取出素箋﹐就著燭火重新封了一封。\n",
				(: command, "say 怎麼東西不見了﹖罷了﹐老朽再寫一封﹐少俠這回可仔細些。" :),
				(: give_report, me :),
			}));
		return 1;
	}

	// 尚未接任務：交付密報，旗標設為 1
	me->set("quest/main_omen", 1);
	do_chat(({
		(: command, "say 少俠有所不知。鎮中那株老榕﹐鎮上人都喚作卯木﹐少說有兩三百歲了。" :),
		(: command, "say 這幾日入夜﹐那卯木底下竟傳出嗚嗚的哭聲﹐連這土地公神像也無故落了淚 ..." :),
		(: command, "say 老朽翻過古籍﹐三百年前皇城的聖木被斷﹐才放出了那不該放的東西。如今卯木有異﹐豈是小事﹖" :),
		(: command, "say 老朽寫了封密報﹐欲呈報官府﹐怎奈腿腳不便。煩請少俠替我送(give)到鄉校﹐交給斷事的師爺﹐取了批文回來﹐老朽必有酬謝﹗" :),
		(: give_report, me :),
	}));
	return 1;
}

int accept_fight()
{
	do_chat((: command, "say 阿彌陀佛﹐出家人不與人爭﹐少俠請自重﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
