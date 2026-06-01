// monk.c -- 雲遊高僧，掛單於後海茶館、精通鎮邪之道的方外人，
//           主線任務七「鎮邪求聖」的委託人與印證（領賞）人
//
// 故事背景（承接主線六「摩雲蹤跡」）：
//   隱居雪亭鎮的老獵王與天靈山麓的獸語者已道破﹕獸王摩雲受天靈山那縷邪念
//   牽動﹐退往天靈山麓蓄勢﹐欲制牠須得「破障同道」與「制邪聖物」。這位雲
//   遊高僧本是精擅鎮邪、淨念之道的方外人﹐近日掛單後海茶館﹐亦循著天靈山
//   那縷邪念的牽動而來。他道破：三百年前那株被斷的聖木﹐其根脈所鍾的一縷
//   清正餘力至今猶蟄伏於京畿神社的聖木舊址﹐唯有自這縷餘力溫養、開光而成
//   的聖物﹐方能克制摩雲身上的邪念。高僧遂書一紙「淨木請帖」﹐遣這位循異
//   兆追來、已勘明摩雲去向的少俠﹐往神龕後的聖木淨室求取制邪聖物。
//
// 任務流程（旗標存在玩家身上：quest/main_omen7）：
//   入門條件     : 須先完成主線六（quest/main_omen6 >= 3）﹐否則只誦經﹐不開任務
//   未開始 (0)   : 玩家 ask monk about 聖物 -> 高僧交付「淨木請帖」﹐旗標設為 1
//   進行中 (1)   : 玩家持請帖往京畿神社神龕後的聖木淨室﹐交(give)給守木尊者
//                  (/d/capital/npc/sanctifier)﹐尊者驗帖後收下﹐自聖木餘力中
//                  賜給「淨邪聖木牌」(制邪聖物)﹐並把旗標推進為 2（推進在 sanctifier.c）
//   已取得 (2)   : 玩家持聖木牌回後海茶館 ask monk about 聖物 -> 高僧驗訖印證﹐
//                  領賞(give_reward)﹐旗標設為 3。聖物乃決戰之憑藉﹐留與玩家﹐
//                  不收回（以 present 驗其在身﹐不取走、不銷毀）
//   已完成 (3)   : 不再重複給賞﹐do_ask 給出朝向「破障同道／天靈山摩雲決戰」一段的
//                  純劇情伏筆（為主線八鋪路）
//
// 注意：step 3 以 present("holy relic", who) 驗玩家身上仍持聖物﹐確認後給賞並推進﹐
//       但「不」取走聖物——聖物是玩家留用至決戰的至寶。最終旗標處作防重複領獎。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("雲遊高僧", ({ "wandering monk", "monk", "gaoseng" }) );
	set("nickname", "雲遊高僧");
	set_attr("int", 24);
	set_attr("wis", 26);
	set_attr("con", 20);
	set_race("human");
	set_class("commoner");
	set_level(16);
	set_skill("unarmed", 30);
	set_skill("dodge", 30);
	set_skill("force", 38);
	set_skill("literate", 38);

	set("gender", "male");
	set("age", 63);
	set("long",
		"一位掛單在後海茶館的雲遊高僧﹐眉目慈和﹐寶相清臒﹐一襲洗得\n"
		"發白的灰布僧袍﹐肩上斜挎一隻舊得起了毛邊的褡褳﹐手裡一串溫\n"
		"潤的菩提念珠捻動不休。他不似茶館裡那些清談的雅客﹐只揀了臨\n"
		"窗一張清靜的桌子﹐時而闔目誦持﹐時而望著北面出神。聽茶博士\n"
		"說﹐這位高僧雲遊四海﹐專破天地間的邪祟魔障﹐這幾日總望著天\n"
		"靈山的方向蹙眉﹐似在為甚麼放不下的禍事憂心。\n"
		"你或許可以問問他﹕ask monk about 聖物。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"雲遊高僧捻動著手中念珠﹐闔目低誦了一段經文﹐眉宇間鎖著化不開的憂色。\n",
		"雲遊高僧喃喃道﹕邪念漫天﹐非血肉之軀所能擋 ... 須得制邪之聖物啊 ...\n",
	}));
	setup();
	carry_object("/obj/area/obj/cloth")->wear();
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player()) ) {
		int q = this_player()->query("quest/main_omen7");
		if( q == 1 || q == 2 )
			do_chat((: command,
				"say 少俠﹐京畿神社聖木淨室那一趟﹐那制邪聖物可求得了麼﹖" :));
		else if( !q && this_player()->query("quest/main_omen6") >= 3 )
			do_chat((: command,
				"say 少俠身上 ... 竟纏著一縷摩雲那一脈的邪念﹖看來你我憂的﹐是同一樁禍事。" :));
	}
}

// 把一紙淨木請帖交到玩家手上（先複製到自己身上，再 give 出去）
private void give_token(object who)
{
	object token;

	if( !who || environment(who) != environment() ) {
		command("say 咦 ... 人呢﹖");
		return;
	}
	token = new("/d/capital/npc/obj/purify_token");
	token->move(this_object());
	command("give purify token to " + who->query("id"));
}

// 領賞：給一串銅錢、一帖傷藥﹐並授存活、俠義之舉、聲望與旅行見聞
// （注意：不取走聖物——聖物乃決戰之憑藉，留與玩家）
private void give_reward(object who)
{
	object coin, pill;

	if( !who || environment(who) != environment() ) return;

	coin = new("/obj/money/coin");
	coin->set_amount(500);
	if( !coin->move(who) ) coin->move(environment());

	pill = new("/obj/medication/alchemist/aquapill");
	if( !pill->move(who) ) pill->move(environment());

	who->gain_score("survive", 500);
	who->gain_score("emprise", 180);
	who->gain_score("reputation", 100);
	who->gain_score("explorer fame", 70);

	message_vision(
		"雲遊高僧將那面淨邪聖木牌捧在掌心﹐闔目誦了一段經文印證真偽﹐"
		"末了鄭重地將聖物奉還$N﹐又自褡褳裡取出一串銅錢與一帖金液丹相贈。\n",
		who);
}

int do_ask(string arg)
{
	object me = this_player();
	int q;

	if( !arg || (arg != "monk about 聖物"
		&&   arg != "monk about 摩雲"
		&&   arg != "monk about 主線"
		&&   arg != "monk about 任務"
		&&   arg != "wandering monk about 聖物"
		&&   arg != "wandering monk about 摩雲"
		&&   arg != "monk about relic"
		&&   arg != "monk about quest"
		&&   arg != "monk about task") )
		return notify_fail("你想問這位高僧甚麼﹖（試試 ask monk about 聖物）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("雲遊高僧正闔目捻珠誦持著甚麼﹐沒空理你。\n");

	// 入門條件：須先完成主線六「摩雲蹤跡」
	if( me->query("quest/main_omen6") < 3 ) {
		do_chat(({
			(: command, "say 少俠面生 ... 也罷。天靈山那縷邪念漫天而下﹐勾得百獸發狂﹐其後的禍事﹐豈是三言兩語能與生人說清的。" :),
			(: command, "say 少俠若真覺出這邪念的牽動﹐倒不如先去尋那些追查獸亂的明白人——雪亭鎮飲風客棧那位隱居的老獵王﹐祖孫三代追的便是那獸王摩雲。待你勘明了摩雲的去向﹐再來尋老衲不遲。" :),
		}));
		return 1;
	}

	q = me->query("quest/main_omen7");

	// 主線七已全部完成：收尾、加深朝向「破障同道／天靈山摩雲決戰」的伏筆（純劇情，不開任務）
	if( q >= 3 ) {
		do_chat(({
			(: command, "say 多虧少俠走這一趟﹐那面淨邪聖木牌老衲已印證明白——確是自聖木根脈僅存的清正餘力溫養而成﹐專能克制摩雲身上那縷邪念。少俠把它收好﹐他日上天靈山﹐全仗它護持心神、破那重重邪障。" :),
			(: command, "say 然單憑一件聖物﹐尚不足以制摩雲。那山中邪障重重﹐獸語者早有言在先——少俠還須尋一位能與你並肩破障的同道﹐方有勝算。老衲雲遊四海﹐隱約聽聞江湖上自有那麼一位身負破障之能的奇人﹐少俠且留心訪查。" :),
			(: command, "say 制邪有聖物﹐破障待同道。待少俠湊齊了這兩樁﹐摩雲退守的天靈山麓﹐便是你了結這場禍事的去處了。摩雲一脈之後﹐尚有骨屍妖王、鬼王噬魂之輩﹐層層守著那混沌珠的下落——這條路還長﹐老衲在這茶館裡﹐替少俠誦經祈福。" :),
		}));
		return 1;
	}

	// 已取得聖物，回來印證領賞（step 3：以 present 驗其在身，不取走聖物）
	if( q == 2 ) {
		if( present("holy relic", me) ) {
			me->set("quest/main_omen7", 3);
			do_chat(({
				(: command, "say 少俠把那面淨邪聖木牌請出來﹐容老衲驗上一驗——嗯﹐這木牌觸手溫潤﹐青芒內斂﹐果是自聖木根脈那縷清正餘力溫養而成的真物﹗守木尊者好深的開光功夫。" :),
				(: give_reward, me :),
				(: command, "say 這聖物老衲驗訖﹐分毫無損﹐少俠仍收好——切記須一路帶在身邊﹐它日上天靈山制摩雲﹐全仗它護持。這點銅錢與丹藥﹐少俠帶著防身。少俠肯為這天下蒼生奔走求聖﹐老衲這方外之人﹐承你的情了﹗" :),
			}));
		} else
			do_chat((: command,
				"say 咦﹐那面淨邪聖木牌呢﹖少俠怎未帶在身上﹖那聖物干係重大﹐快回京畿神社聖木淨室﹐尋守木尊者問個明白﹐莫教這制邪的至寶失落了。" :));
		return 1;
	}

	// 任務進行中（已領請帖，還沒求得聖物）
	if( q == 1 ) {
		if( present("purify token", me) )
			do_chat((: command,
				"say 那紙淨木請帖少俠帶在身上了。出茶館往北回後海湖﹐自湖東行至皇城廣場﹐"
				"再往北拾級而上便是京畿神社﹐入得正殿﹐神龕之後另有一道側門﹐通往聖木淨室——"
				"尋著那位守木尊者﹐把請帖交(give)給他﹐自能求得那制邪聖物。" :));
		else
			// 萬一玩家把請帖弄丟了，補書一紙給他
			do_chat(({
				"雲遊高僧搖頭一笑﹐又自褡褳裡取出素箋朱砂﹐重新書就一紙淨木請帖。\n",
				(: command, "say 怎麼那帖子不見了﹖罷了﹐老衲再與少俠書一紙便是﹐這回可收好了。" :),
				(: give_token, me :),
			}));
		return 1;
	}

	// 尚未接任務：交付淨木請帖，旗標設為 1
	me->set("quest/main_omen7", 1);
	do_chat(({
		(: command, "say 少俠既已隨那老獵王勘明了摩雲的去向﹐想必也曉得——那獸王退往天靈山麓蓄勢﹐欲制牠﹐須得『破障同道』與『制邪聖物』兩樁。老衲雲遊四海﹐專破邪祟魔障﹐這制邪聖物的著落﹐倒略知一二。" :),
		(: command, "say 摩雲一脈之邪﹐皆源自天靈山那縷牽動百獸的邪念。要克制這邪念﹐尋常刀兵無用﹐須得一件至清至正的聖物。少俠可知﹖三百年前皇城那株鎮天地、封邪物的聖木雖遭攔腰斷去﹐其根脈所鍾的一縷清正餘力﹐至今猶蟄伏於京畿神社的聖木舊址——那縷餘力﹐最是克制邪念。" :),
		(: command, "say 京畿神社神龕之後有一方聖木淨室﹐守木一脈中有位精擅開光淨化的尊者﹐久已以那縷聖木餘力溫養著一面制邪聖物。老衲書一紙『淨木請帖』與少俠﹐少俠持帖往那淨室﹐把帖子交(give)給守木尊者﹐自能求得那聖物。" :),
		(: command, "say 切記﹕求得那聖物後﹐須一路妥善帶在身邊﹐切莫遺失——它是少俠他日上天靈山制摩雲、破邪障的唯一憑藉。求得之後﹐少俠回來尋老衲﹐老衲也好為你印證真偽、再作籌謀。此事干係天下安危﹐萬望少俠謹慎﹗" :),
		(: give_token, me :),
	}));
	return 1;
}

// 收下信物：本 NPC 只在 do_ask（ask monk about 聖物）以 present 驗聖物在身後印證領賞，
// 聖物留與玩家、不收回。此處 accept_object 僅作防呆——婉拒玩家遞來的物事，
// 尤其「不」收下淨邪聖木牌（聖物乃決戰之憑藉，須留在玩家身上）。
int accept_object(object who, object ob)
{
	// 防呆：玩家若誤把聖物 give 給高僧，婉拒退回，並提示改用 ask 印證
	if( ob->id("holy relic") ) {
		do_chat((: command,
			"say 少俠快收回﹗這淨邪聖木牌是留與少俠決戰護身的至寶﹐老衲怎能收你的﹖少俠若要老衲印證真偽﹐ask monk about 聖物 便是﹐自個兒捧著給老衲瞧一眼即可。" :));
		return 0;
	}

	// 其餘物事：婉拒﹐不收下（避免吞掉玩家的尋常物品）
	do_chat((: command, "say 老衲出家人﹐了無長物﹐這個受不起﹐少俠還是自個兒留著罷。" :));
	return 0;
}

int accept_fight(object ob)
{
	do_chat((: command, "say 少俠息怒﹗老衲一個雲遊誦經的出家人﹐與少俠無冤無仇哪。" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
