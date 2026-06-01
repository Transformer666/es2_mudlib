// teamaster.c -- 後海茶館資深的茶博士，既是賣茶點的攤商，
//                亦是京畿支線任務「後海茶香」的委託人與領賞人
//
// 任務流程（旗標存在玩家身上：quest/houhai_tea，與主線、巡院差事各自獨立）：
//   未開始 (0)  : 玩家 ask teamaster about 茶 -> 茶博士訴說頂尖的雨前龍井運茶時
//                 翻簍散落後海湖岸﹐託玩家去湖邊尋回﹐旗標設為 1
//   進行中 (1)  : 玩家往北到後海湖﹐ask commoner about 茶葉 -> 拾得茶葉的京城百姓
//                 把那包龍井茶葉交還﹐並把旗標推進為 2（推進在 commoner.c）
//   已尋回 (2)  : 玩家持龍井茶葉回茶館﹐交(give)給茶博士 -> 領賞﹐旗標設為 3
//   已完成 (3)  : 不再重複給賞（防止重複領獎）

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

int do_ask(string arg);

void create()
{
	set_name("茶博士", ({ "teamaster", "vendor" }) );
	set_race("human");
	set_class("commoner");
	set_level(4);

	set("age", 45);
	set("gender", "male");
	set("long",
		"後海茶館裡資深的茶博士﹐手腳俐落﹐提著一柄長嘴的紫銅大\n"
		"壺﹐高沖低斟皆是一手好功夫。他見客人進門便堆起笑臉招呼。\n"
		"你可以用 list 看他供些什麼茶點﹐用 buy 向他點。只是這會兒\n"
		"他眉間鎖著一絲愁色﹐似有甚麼煩心的事——你或許可以問問他﹕\n"
		"ask teamaster about 茶。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"茶博士提著長嘴銅壺﹐手腕一抖﹐一道水線不偏不倚地注滿了茶碗﹐滴水不灑。\n",
		"茶博士笑著招呼道﹕客官裡邊請﹐嚐嚐咱們後海茶館的新茶﹖\n",
		"茶博士一面斟茶一面閒話道﹕咱這後海湖的水﹐烹起茶來最是清甜﹐別處可比不得。\n",
	}));
	// 後海茶館供應茶點﹐暫沿用既有的乾糧吃食物件。
	// TODO: 日後可新建龍井、香片等茶飲 obj﹐及點心糕餅。
	set("merchandise", ([
		"/obj/food/mooncake" : 40,
		"/obj/food/manto" : 50,
		"/obj/food/dumpling" : 50,
	]));

	setup();
	carry_money("coin", 200);
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player()) ) {
		int q = this_player()->query("quest/houhai_tea");
		if( q == 1 || q == 2 )
			do_chat((: command,
				"say 客官﹐我那包散落湖岸的雨前龍井﹐可有著落了麼﹖" :));
		else if( !q )
			do_chat((: command,
				"say 唉 ... 好端端一簍頂尖的龍井﹐竟教我給糟蹋了 ..." :));
	}
}

// 領賞：給一串銅錢、一塊月餅﹐並授江湖歷練與旅行見聞
private void give_reward(object who)
{
	object coin, cake;

	if( !who || environment(who) != environment() ) return;

	coin = new("/obj/money/coin");
	coin->set_amount(200);
	if( !coin->move(who) ) coin->move(environment());

	cake = new("/obj/food/mooncake");
	if( !cake->move(who) ) cake->move(environment());

	who->gain_score("survive", 150);
	who->gain_score("explorer fame", 60);

	message_vision(
		"茶博士眉開眼笑﹐取一只青瓷蓋碗﹐撮一撮那龍井下去﹐提壺一個"
		"「鳳凰三點頭」沖了碗釅茶奉與$N﹐又取了一塊月餅相贈。\n",
		who);
}

int do_ask(string arg)
{
	object me = this_player();
	int q;

	if( !arg || (arg != "teamaster about 茶"
		&&   arg != "teamaster about 茶葉"
		&&   arg != "teamaster about 龍井"
		&&   arg != "teamaster about 後海"
		&&   arg != "teamaster about 任務"
		&&   arg != "vendor about 茶"
		&&   arg != "teamaster about tea"
		&&   arg != "teamaster about quest"
		&&   arg != "teamaster about task") )
		return notify_fail("你想問茶博士甚麼﹖（試試 ask teamaster about 茶）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("茶博士正忙著斟茶﹐沒空理你。\n");

	q = me->query("quest/houhai_tea");

	// 已全部完成
	if( q >= 3 ) {
		do_chat((: command,
			"say 上回多虧客官替我尋回那包好龍井﹐往後常來坐坐﹐茶錢算我的﹗" :));
		return 1;
	}

	// 已尋回茶葉，回來交還（理應用 give 交付，這裡只作提示）
	if( q == 2 ) {
		if( present("longjing leaf", me) )
			do_chat((: command,
				"say 哎喲﹗客官果真尋著啦﹖快把那包龍井交(give)給我瞧瞧﹗" :));
		else
			do_chat((: command,
				"say 咦﹖客官那包龍井呢﹖莫不是路上又給弄丟了﹖"
				"快回後海湖邊﹐再尋那拾著茶葉的百姓問問。" :));
		return 1;
	}

	// 任務進行中（還沒尋回茶葉）
	if( q == 1 ) {
		do_chat((: command,
			"say 那包龍井就散在後海湖岸邊。客官出茶館往北便是後海湖﹐"
			"湖邊常有京城百姓走動﹐問問他們（ask commoner about 茶葉）"
			"﹐興許有人拾著了。" :));
		return 1;
	}

	// 尚未接任務：訴說遺失茶葉的原委，旗標設為 1
	me->set("quest/houhai_tea", 1);
	do_chat(({
		(: command, "say 不瞞客官﹐今早我去後海湖邊接運新到的一簍雨前龍井——那可是清明前採的頭茬嫩芽﹐千金難求的好茶啊﹗" :),
		(: command, "say 偏生湖邊風大﹐我一個沒留神﹐茶簍翻了﹐好大一包龍井全教湖風捲到岸邊去了。我這提壺斟茶離不得身﹐又抹不開臉去湖邊滿地撿那茶葉 ..." :),
		(: command, "say 客官若得閒﹐勞煩往北到後海湖邊﹐替我尋回那包龍井。湖邊走動的京城百姓眼尖﹐保不準有人順手拾了去——客官 ask commoner about 茶葉 問問便知。尋回來交還給我﹐我必有酬謝﹗" :),
	}));
	return 1;
}

// 收下信物：確認是任務信物且玩家已尋回(旗標 2)，推進旗標 2 -> 3 並領賞
int accept_object(object who, object ob)
{
	if( !ob->id("longjing leaf") ) {
		do_chat((: command, "say 這個我可用不上﹐客官還是自個兒留著罷。" :));
		return 0;
	}

	// 不是已尋回的任務玩家（或已交過），仍收下避免卡物，但不重複給賞
	if( who->query("quest/houhai_tea") != 2 ) {
		do_chat((: command, "say 多謝客官﹗" :));
		return 1;
	}

	// 同步給賞、即記旗標（give_reward 為直接 new+move﹐玩家此刻必在場）。
	// 不把給賞放進延遲的 do_chat——免玩家於回呼前離場致賞沒領、旗標卻記完成而卡關。
	give_reward(who);
	who->set("quest/houhai_tea", 3);
	do_chat(({
		(: command, "say 正是我那包雨前龍井﹗油紙都還裹得好好的﹐茶葉一星半點沒糟蹋——客官真是我的恩人哪﹗" :),
		(: command, "say 客官嚐嚐這頭茬的龍井﹐配著月餅最是相宜。對了﹐這幾日後海湖夜半屢有異響﹐連畫舫都不敢往湖心去﹐西岸那座巡院的官爺們也進進出出的﹐不知又在查辦甚麼大案子哩——客官在京畿走動﹐自個兒留神著些。" :),
	}));
	return 1;
}

int accept_fight(object ob)
{
	do_chat("茶博士連忙護住銅壺﹐賠笑道﹕客官息怒﹐這可是文雅之地﹐有話好說呀﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
