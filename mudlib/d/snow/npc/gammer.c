// gammer.c

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

// 主線伏筆 lore(純劇情，不給物)：瞎眼老太婆雖目不能視，卻聽得見常人聽不見的東西。
//   她以一種半瘋半癲的預言口吻，零星吐露侮天鬼破封、十三靈、三百年災變的徵兆，
//   替主線埋下隱晦伏筆。採 do_ask(ask gammer about <topic>)，與既有 relay_say
//   (try/fon 趙丰/柳東蘆任務鏈)互不相干。handler 守衛 is_fighting()/is_chatting()。
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
	return notify_fail("瞎眼老太婆側著耳朵：你問的是 ... 侮天鬼？十三靈？還是三百年前那場災變？\n");
}

// vim: set ts=4 sw=4 syntax=lpc
