// gammer.c

// 「阿寶的心願」(quest/snow_abao) 情感向支線：
//   瞎眼老太婆的亡夫趙丰（她口中的「死鬼」）三年多前死於非命，她口口聲聲怪
//   柳東蘆害的；孫女阿寶卻仍蹲在廣場那株老榕樹上痴痴等著爺爺的消息。婆婆把
//   貼身的青布手帕(abao_keepsake)託玩家帶去給樹上的阿寶，要玩家好生勸勸她
//   ——婆婆已不再執著尋仇，只盼孫女回家。玩家把手帕(give)交給阿寶、傳達婆婆
//   的心意，阿寶這才肯下樹回家，支線收束（給聲望/見聞）。
//
//   設計守則：docs 只給「阿寶在榕樹上等誰」之疑團、未給解答，故做成情感向、
//   可完成的傳話支線（傳話＋信物＋旗標＋小獎勵），【不】把「殺柳東蘆復仇」
//   硬綁進本支線（柳東蘆是 d/fonxan boss，玩家自行去殺與否與本支線無涉，僅在
//   對白裡呼應）。本支線旗標 quest/snow_abao 與既有 try/fon 封山入派鏈互不相干，
//   ask-path 與物件 id 皆獨立，不污染舊鏈。
//
//   鐵則遵循：#10 本檔信物交付／設旗標逕在 handler 內順序寫就，無 ::die()/
//   destruct；#11 本檔為 NPC（非房間），不涉 replace_program；#14 do_ask
//   handler 開頭已守衛 is_fighting()/is_chatting()。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);     // 主線伏筆 lore：預言式口吻(純劇情，不給物)

void create()
{
	set_name("瞎眼老太婆", ({ "blind gammer", "gammer", "__ID_GAMMER__" }) );
	set_attr("dex", 29);
	set_attr("con", 21);
	set_attr("cor", 22);
	set_attr("str", 19);
	set_race("human");
	set_class("commoner");
	set_level(44);

	set_skill("staff", 40);
	set_skill("stealing", 70);
	set_skill("dodge", 90);
	set_skill("blade", 30);
	set_skill("sword", 30);
	set_skill("unarmed", 50);
	set_skill("dagger", 70);
	set_skill("secondhand dagger", 70);
	set_skill("killerhood", 60);
	set_skill("force", 90);
	set_skill("regular force", 100);
    map_skill("force", "regular force");

	advance_stat("gin", 270);
	advance_stat("kee", 180);
	advance_stat("sen", 90);

	set("gender", "female");
	set("age", 66);
	set("long",
		"一個瞎了眼睛的老太婆﹐滿臉皺紋﹐但是卻給人一種親切的感覺。\n");

	set("chat_chance", 8);
	set("chat_msg", ({
		"瞎眼老太婆喃喃地說道﹕阿寶﹖是你嗎﹖\n",
		"瞎眼老太婆側著耳朵似乎在傾聽什麼。\n",
		(: random_move :)
	}) );

	set("chat_chance_combat", 10);
	set("chat_msg_combat", ({
		"瞎眼老太婆叫道﹕阿寶﹗有惡人在欺負婆婆哪﹗快出來啊﹗\n",
		(: random_move :),
	}) );
	set_stat_notify("kee", 40);

	setup();
	carry_object("/obj/area/obj/cloth")->wear();
	carry_object(__DIR__"obj/cane")->wield();
	carry_object(__DIR__"obj/syndicator")->wield("secondhand dagger");
}

private void give_coin(object who)
{
	object ob;

	if( environment(who) != environment() ) return;
	ob = new(__DIR__"obj/coin");
	if( !ob->move(who) )
		ob->move(environment());
}

void relay_say(object ob, string arg)
{
	int tmp = ob->query_temp("try/fon");
	// communicate with arbao
	if( !userp(ob) ){
		if( ob->id("__ID_ARBAO__") ){
			this_object()->delete("chat_msg");	// stop chat_msg
			this_object()->delete("chat_chance");
			if( strsrch(arg,"那太好了")>= 0 ) {
				do_chat((:command(
"say 胳臂外彎啊阿寶, 妳是喜歡上柳淳風那小子了吧."):));
				return;
			}
			if( strsrch(arg,"是")>= 0 ){
				do_chat(({
(:command("say 他想娶妳, 可以, 但條件是他父子要先幫你爺爺報了仇.
這樣他家與咱們的恩怨才算一筆勾消."):),
				}));
				call_out((:message_vision("瞎眼老太婆說完, 轉過身走了.\n",this_player()):),4);
				call_out((:destruct(this_object()):),6);
				return;
			}
		}
	}
	if( !tmp || tmp==0 ){
		if( arg=="祖奶奶" && ob->query_temp("thief_qualified") ) {
			command("giggle");
			command("pat " + ob->query("id"));
			if( (string)ob->query_class() != "commoner" ) return;
			ob->set_class("thief");
			tell_object(ob, "你正式成為一名盜賊了。\n");
			ob->improve_skill("sneak", 20);
			ob->improve_skill("stealing", 20);
			do_chat(({
				"瞎眼老太婆說道：對了，這個給你。",
				(: give_coin, ob :),
				"瞎眼老太婆說道：如果你想學本事，拿這東西給對方看。\n",
			}));
			return;
		}
		if( strsrch(arg, "阿寶") >= 0 )
			do_chat((: command, "say 阿寶﹖你說阿寶在哪裡﹖" :));
		else switch(random(10)) {
			case 0: do_chat((: command, "shake" :));
			case 1: do_chat((: command, "?" :));
			case 2: do_chat((: command, "steal coin from " + ob->query("id") :));
		}
		return;
	}
	switch(tmp) {
		case 8:
			if( strsrch(arg,"柳")>=0 ) {
				do_chat(({
"瞎眼老太婆怒不可遏, 喝道: 滾, 滾, 滾, 我不想聽到這個姓.\n",
"瞎眼老太婆喃喃自語著離開了, 你隱隱約約聽到甚麼死鬼, 阿寶, 甚麼仇的.\n",
"你想到也許老太婆的孫女兒知道死鬼的意思.\n",
				}));
				ob->set_temp("try/fon",10);
			}
			break;
		case 16:
			if( strsrch(arg,"趙丰")>=0 ) {
				do_chat(({
"瞎眼老太婆說道: 我那死鬼早在三年多前被柳東蘆給害死了, 你問他做啥?\n",
"瞎眼老太婆又喋喋不休的說道: 他要不是被柳東蘆傷了, 憑他天下第一的輕功絕不會
被人殺死, 這不是柳東蘆那廝害的嗎.\n",
"問了半天還是不清不楚, 你不禁疑惑, 不知柳東蘆跟這件事有何瓜葛.\n"
				}));
				ob->set_temp("try/fon",18);
			}
			break;
		case 45:
			if( strsrch(arg,"小豬豬")>=0 ) {
				do_chat(({
"瞎眼老太婆驚道: 這..這.. 好久沒有人這樣叫我了.. 看來這真的是老頭子寫的了.\n",
"你詳細的說明趙丰的死因.\n", 
"瞎眼老太婆沉吟了一下.\n",
(:command("say 小子, 幫老婆子一個忙, 去告訴姓柳的, 老婆子不會再去找他尋仇
了, 但緝兇之事, 他可別想脫得了責任."):),
				}));
				ob->set_temp("try/fon",48);
			}
			break;
		default:        break;
	}
}

int accept_fight()
{
	do_chat((: command, "?" :));
	return notify_fail("瞎眼老太婆對你視若無睹 ...。\n");
}

void init()
{
    add_action("do_ask", "ask");        // 主線伏筆 lore；務必在下方任何早退之前註冊
    if( environment(this_object())->query("connect-p") ) {
	command("say 口渴了, 來喝口水...\n");
        message_vision("$N緩緩走回大水缸邊。\n", this_object());
        this_object()->move("/d/snow/square");
        return;
    }
	// Dont call original init() to check autofight.
	if( !is_chatting() && this_player()->query_temp("try/fon")==43 ){
		do_chat(({
			"你見到了老太婆, 提出破布一事.\n",
			"老太婆喝道: 甚麼破布, 拿來.\n",
		}));
	}
}

private void ask_join(object player)
{
	if( !player || environment(player)!=environment() ) return;

	if( player->query_class() != "commoner" )
		command("say 唉 ... 人老了﹐連隨身的梳子都常常丟掉。\n");
	else {
		command("whisper " + player->query("id") + 
			" 好傢伙﹐竟然給你偷去了﹖想成為小偷是不是﹖叫聲「祖奶奶」我就讓你入這行 ...");
		player->set_temp("thief_qualified", 1);
	}
}

int accept_object(object player, object ob)
{
	if( player->query_temp("try/fon")!=43 ){
		if( !ob->id("annatto comb") ) return 0;
		command("say 咦﹖這 ... 這是 ... 我的梳子﹗");
		do_chat((: ask_join, player :));
		return 1;
	}
	if( ob->id("__ID_CHALLIE__") )	{
		do_chat(({
			"瞎眼老太婆怒道: 你這是欺我眼瞎看不見, 想來騙我嗎?\n",
			"你想到老太婆的暱稱, 也許可以使她相信那件破布.\n"
		}));
		player->set_temp("try/fon", 45);
		return 1;
	}
}

// 「阿寶的心願」支線：把青布手帕(abao_keepsake)交到玩家手上。
//   採同步交付（先 new 到自己身上再 give 給玩家），不走會因玩家離場而落空的
//   延遲回呼。回傳 1＝手帕確實落在玩家身上，0＝沒交成（玩家離場/負荷過重）。
//   弄丟了可再 ask gammer about 信物 討一方，杜絕 give-turn-in 軟鎖。
private int give_keepsake(object who)
{
	object kp;

	if( !who || environment(who) != environment() ) return 0;
	kp = new(__DIR__"obj/abao_keepsake");
	kp->move(this_object());
	command("give keepsake to " + who->query("id"));
	// 確認手帕真的到了玩家身上（give 失敗則手帕仍在婆婆身上，視為沒交成）。
	return present("abao keepsake", who) ? 1 : 0;
}

// 主線伏筆 lore(純劇情，不給物)：瞎眼老太婆雖目不能視，卻聽得見常人聽不見的東西。
//   她以一種半瘋半癲的預言口吻，零星吐露侮天鬼破封、十三靈、三百年災變的徵兆，
//   替主線埋下隱晦伏筆。採 do_ask(ask gammer about <topic>)，與既有 relay_say
//   (try/fon 趙丰/柳東蘆任務鏈)互不相干。handler 守衛 is_fighting()/is_chatting()。
//
// 另含「阿寶的心願」(quest/snow_abao) 情感支線之 ask-path（阿寶/心願/死鬼/趙丰/
//   信物 等 topic）：與上述主線 lore、既有 try/fon 鏈互不相干，旗標獨立。
int do_ask(string arg)
{
	if( !arg ) return notify_fail("你想問瞎眼老太婆甚麼？(試試 ask gammer about 侮天鬼)\n");
	if( is_fighting() || is_chatting() )
		return notify_fail("瞎眼老太婆側著耳朵似在傾聽甚麼，恍若未聞。\n");

	if( arg == "gammer about 侮天鬼" || arg == "gammer about 鬼"
	 || arg == "gammer about wutiangui" ) {
		do_chat(({
			"瞎眼老太婆渾濁的盲眼忽地睜大，壓低嗓子道：噓 ... 你也聞著那股子腥氣了麼？三百年前破土而出的那東西，從沒真個被封死過 ...\n",
			(: command, "say 老婆子我眼瞎了，心卻亮著哪。夜深人靜時，我聽得見地底下有甚麼在喘氣、在等 ... 等著把這天下又拖回那不見天日的濁世裡去。" :),
		}));
		return 1;
	}
	if( arg == "gammer about 十三靈" || arg == "gammer about 靈"
	 || arg == "gammer about shisanling" ) {
		do_chat(({
			"瞎眼老太婆掐著指頭喃喃低語，像在數著甚麼看不見的數目。\n",
			(: command, "say 十三盞燈 ... 滅了多少了？老婆子數不清嘍。當年是十三位靈護著這人間的，如今散的散、隱的隱 ... 燈火若都熄了，這天，可就要塌嘍。" :),
			(: command, "say 百年一輪迴，輪到了，自有那命中註定的人來把燈重新點上 ... 那人是誰呢？老婆子瞧不見，瞧不見哪。" :),
		}));
		return 1;
	}
	if( arg == "gammer about 災變" || arg == "gammer about 三百年"
	 || arg == "gammer about 預言" || arg == "gammer about 天命" ) {
		do_chat(({
			"瞎眼老太婆仰起臉，那雙看不見的眼睛卻彷彿望進了極遠的地方。\n",
			(: command, "say 三百年前聖木一斷，這天下的氣數便跟著斷了一截 ... 老婆子小時候就聽人說，惡鬼六百年要與天賭一回，輸贏都在人心的善惡之間。" :),
			(: command, "say 你身上 ... 嗯？有點意思。罷了罷了，老婆子多嘴。記著老婆子一句：刀光劍影都是小事，真正要當心的，是那藏在人心底、連自己都瞧不見的那點惡。去罷。" :),
		}));
		return 1;
	}

	// ── 「阿寶的心願」情感支線 ask-path ──────────────────────────────
	// 問阿寶／死鬼／趙丰／心願：婆婆訴說亡夫趙丰之死與孫女阿寶痴等的苦楚，
	//   把這樁心願託付給玩家（設 quest/snow_abao=1，指引玩家上樹勸阿寶回家）。
	if( arg == "gammer about 阿寶" || arg == "gammer about arbao"
	 || arg == "gammer about 心願" || arg == "gammer about 死鬼"
	 || arg == "gammer about 趙丰" || arg == "gammer about 老頭子"
	 || arg == "gammer about 孫女" ) {
		object me = this_player();
		int q;

		if( !me || !interactive(me) )
			return notify_fail("這裡沒人問你的話。\n");
		q = me->query("quest/snow_abao");

		// 已圓滿（旗標 2）：阿寶已下樹回家，婆婆只剩感念
		if( q >= 2 ) {
			do_chat(({
				(: command, "say 多虧了你這好心的後生 ... 阿寶那孩子總算肯下樹回家了﹐這些日子﹐婆婆心裡踏實多嘍。" :),
				(: command, "say 死鬼若泉下有知﹐見孫女平平安安的﹐也該瞑目了。" :),
			}));
			return 1;
		}

		// 已託付（旗標 1）：催玩家上樹去勸阿寶，弄丟手帕可再討
		if( q == 1 ) {
			if( present("abao keepsake", me) )
				do_chat((: command,
					"say 後生﹐手帕婆婆給你了﹐你且爬上廣場那株老榕樹﹐把這手帕拿給阿寶瞧瞧﹐"
					"再好生勸勸她回家罷。" :));
			else
				do_chat(({
					(: command, "say 咦﹖那方青布手帕呢﹖你莫不是給弄丟了﹖" :),
					(: command, "say 罷了罷了﹐婆婆再尋一方給你——ask gammer about 信物 便是。" :),
				}));
			return 1;
		}

		// q==0：首次託付，設旗標 1，並當場把手帕交給玩家
		me->set("quest/snow_abao", 1);
		do_chat(({
			"瞎眼老太婆渾濁的盲眼一下子紅了﹐枯瘦的手在懷裡摸索了半晌。\n",
			(: command, "say 你問我那死鬼麼 ... 唉﹐他叫趙丰﹐江湖上喚他一聲丰爺﹐一身輕功本是天下無雙。三年多前﹐他不知教甚麼人暗算了﹐死在天邪國外郊 ..." :),
			(: command, "say 婆婆嘴上罵他死鬼、罵那姓柳的害人﹐心裡頭其實 ... 哪一天不念著他。可仇恨這東西﹐越攥越苦﹐婆婆老啦﹐攥不動嘍。" :),
			(: command, "say 真正放不下的﹐是我那苦命的孫女阿寶。那孩子打她爺爺沒了﹐就成天蹲在廣場那株老榕樹上﹐說是 ... 說是等爺爺回來。她不肯信丰爺已經不在了呀。" :),
			(: give_keepsake, me :),
			(: command, "say 這方青布手帕﹐是婆婆當年替阿寶縫的﹐角上那個歪歪的「寶」字﹐就是我繡的。後生﹐你替婆婆爬上樹去﹐把手帕拿給阿寶﹐告訴她﹕婆婆不尋仇了﹐只盼她下樹回家。" :),
			(: command, "say 上了樹﹐你 ask arbao about 婆婆 ﹐再把手帕(give)交給她﹐這事便成了。婆婆 ... 多謝你了。" :),
		}));
		return 1;
	}

	// 問信物：補發青布手帕（旗標 1 且玩家手上沒手帕時）。防 give-turn-in 軟鎖。
	if( arg == "gammer about 信物" || arg == "gammer about 手帕"
	 || arg == "gammer about keepsake" ) {
		object me = this_player();
		int q;

		if( !me || !interactive(me) )
			return notify_fail("這裡沒人問你的話。\n");
		q = me->query("quest/snow_abao");

		if( q < 1 ) {
			do_chat((: command,
				"say 甚麼手帕﹖後生﹐你先 ask gammer about 阿寶 ﹐婆婆有樁心願要託你。" :));
			return 1;
		}
		if( q >= 2 ) {
			do_chat((: command,
				"say 那手帕阿寶已收下了﹐這樁事早了啦﹐後生你不必再記掛。" :));
			return 1;
		}
		if( present("abao keepsake", me) ) {
			do_chat((: command,
				"say 手帕不就在你身上麼﹖快上樹拿給阿寶瞧去罷。" :));
			return 1;
		}
		// 旗標 1、手上無手帕：補發一方
		do_chat(({
			"瞎眼老太婆又自懷裡摸出一方一模一樣的青布手帕來。\n",
			(: give_keepsake, me :),
			(: command, "say 拿好嘍﹐這回可別再丟啦。拿給阿寶瞧﹐記得勸她下樹回家。" :),
		}));
		return 1;
	}

	return notify_fail("瞎眼老太婆側著耳朵：你問的是 ... 侮天鬼？十三靈？三百年前那場災變？還是 ... 阿寶那孩子的事？\n");
}

// vim: set ts=4 sw=4 syntax=lpc
