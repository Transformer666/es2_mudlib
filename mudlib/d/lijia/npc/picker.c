// picker.c -- 李家果園裡看園揀果的果農（純氣氛閒談）；
//             兼李家村非戰鬥支線「李家祭祖供果」的指路與授器人。
//
// 本檔原為李家果園看顧果木的氣氛 NPC。為支線「祭祖供果」加掛一段對白：
//   玩家須已自李氏祠堂族長接了任務（quest/lijia_offer==1），方
//   ask picker about 鮮果 -> 果農道出自家園裡供祖鮮果的好處﹐當場就園裡揀一籃形正
//   色勻的好果子、連竹籃一併交與玩家﹐記 quest/lijia_offer_fruit = 1。指引玩家持
//   供果籃到村南魚塘尋守塘漁戶配供盤。
//
// 信物採直接 new + move(who) 同步交付——對白由玩家 ask 觸發﹐玩家此刻必在場﹔
// move 回 1 為成功（落在玩家身上）﹐回 0（失敗）才退而落到地上。先交物、後記
// 旗標﹐不把交付放進延遲的 do_chat 回呼（與 d/kangping farmer、d/weiguo welltender 一致）。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("果農", ({ "picker", "orchard keeper", "guonong" }) );
	set("nickname", "果農");
	set_race("human");
	set_class("commoner");
	set_level(6);

	set("age", 58);
	set("gender", "male");
	set("long",
		"一位在李家果園裡看園揀果的果農﹐生得清癯硬朗﹐裹著件半\n"
		"舊的粗布短褐﹐腰間繫著個揀果的布兜﹐手裡拄著根打果的長竹\n"
		"竿。他打理這一園桃李梨棗打理了半輩子﹐哪株樹結什麼果、幾時\n"
		"熟、揀哪幾顆供祖宗最體面﹐沒有他不曉得的。得閒也可問問他﹕\n"
		"ask picker about 鮮果。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"果農拄著竹竿仰望著掛滿枝頭的鮮果﹐瞇眼盤算著哪幾株先熟、該先摘哪一園。\n",
		"果農伸手摘下一顆紅透的桃子﹐在布兜上揩了揩﹐看著掌心裡飽滿的果子﹐緩緩道﹕今年這果﹐成色好哇。\n",
		"果農把揀出的好果子單擱進一隻竹籃﹐口中道﹕這幾顆形正色勻﹐留著供祖宗最是體面。\n",
	}));
	setup();
	carry_money("coin", 30);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這果農甚麼﹖（試試 ask picker about 鮮果）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("果農正拄著竹竿打果揀果﹐一時沒理會你。\n");

	// 鮮果 / 供果 / 果子：支線「祭祖供果」——指路、授供果籃
	if( arg == "picker about 鮮果"
	||  arg == "picker about 供果"
	||  arg == "picker about 果"
	||  arg == "picker about 果子"
	||  arg == "picker about 祭祖"
	||  arg == "picker about 竹籃"
	||  arg == "picker about fruit"
	||  arg == "picker about basket" ) {
		object me = this_player();
		int q = me->query("quest/lijia_offer");

		// 已完成：純氣氛收尾
		if( q >= 2 ) {
			do_chat((: command,
				"say 那盤祭祖供品配齊了﹖那敢情好﹗難為客官替合族跑這一趟。咱這園裡新摘的果子﹐供奉先祖最是體面﹐也是咱李家祭祖待客的好東西哩。" :));
			return 1;
		}

		// 進行中（已自族長接任務）：道出供果好處、揀果授籃、記旗標
		if( q == 1 ) {
			// 已交付過（供果籃失落／誤毀）：補揀一籃﹐進度旗標不重置﹐免卡關
			if( me->query("quest/lijia_offer_fruit") ) {
				if( !present("lijiagongguo", me) && !present("lijiagongpan", me) ) {
					object c = new(__DIR__"obj/fruit_basket");
					if( !c->move(me) ) c->move(environment());
					do_chat((: command,
						"say 咦﹐先前與客官的那籃供果呢﹖莫不是失落了﹖罷罷罷﹐老朽這就再與客官揀一籃——快拿去村南魚塘尋守塘漁戶配供盤罷。" :));
				} else {
					do_chat((: command,
						"say 那籃供果不是早與客官了麼﹖快持去村心東南田埂下去的村南魚塘﹐尋那位守塘漁戶﹐請他撈尾活鯉、配齊這供盤（ask fisher about 鯉魚﹐或 give fruit basket to fisher），莫教祠堂的族長久等。" :));
				}
				return 1;
			}

			// 首次交付：先同步揀果交籃、後記旗標（玩家此刻必在場）
			{
				object c = new(__DIR__"obj/fruit_basket");
				if( !c->move(me) ) c->move(environment());
			}
			me->set("quest/lijia_offer_fruit", 1);
			message_vision(
				"果農拄著竹竿﹐挑園裡幾株先熟的果樹﹐揀那形正色勻、不疤不蟲的\n"
				"紅桃青李、黃梨紫棗摘了一捧﹐在桐葉上拭淨了﹐盛進一隻竹籃﹐\n"
				"遞到$N手裡。\n", me);
			do_chat(({
				(: command, "say 李氏祠堂的族長打發客官來備祭祖供果﹖嗯﹐這事老朽再熟不過了。要配那供盤﹐頭一樁便是這園裡新摘、揀過的鮮果——今年雨水勻、年成好﹐這果顆顆飽滿﹐形正色勻﹐供奉先祖最是體面﹐隔年的乾果可比不得。" :),
				(: command, "say 喏﹐這籃果子﹐是老朽剛在園裡揀的﹐最是新鮮體面﹐連盛果的竹籃一併與客官使罷。客官拿著它﹐到村心東南田埂下去的村南魚塘去﹐尋那位守塘的漁戶——他配祭祖牲禮的手藝是村裡一絕﹐請他撈尾活鯉、配齊這三牲鮮果的供盤（ask fisher about 鯉魚﹐或 give fruit basket to fisher）﹐再持回祠堂交與族長便是。" :),
			}));
			return 1;
		}

		// 未接任務：純風味帶過，不推進（祭祖供果的事先去問祠堂族長）
		do_chat((: command,
			"say 鮮果﹖客官說的是供奉先祖的供果罷﹖那是咱合族祭祖待客的好東西。客官若為這祭祖供果的事﹐還是先去李氏祠堂問問族長罷。" :));
		return 1;
	}

	// 純氣氛閒談：果園／果木／李家村
	if( arg == "picker about 果園"
	||  arg == "picker about 果木"
	||  arg == "picker about 李家村"
	||  arg == "picker about 李家"
	||  arg == "picker about lijia" ) {
		do_chat(({
			(: command, "say 這一園果木啊﹐是咱李家一輩輩接著栽的﹐最老的幾株李樹﹐據說還是開村的先祖手植﹐如今依舊年年掛果。合族都珍惜得很﹐打理果木﹐便如侍奉祖宗的恩澤一般。" :),
			(: command, "say 老朽在這園裡侍弄了一輩子果子﹐桃李梨棗哪株幾時熟、哪幾顆供祖宗體面﹐閉著眼也摸得著。莊稼人不求大富大貴﹐只求風調雨順、果木年年豐收﹐合族老小有口甜的嚐﹐便知足嘍。" :),
		}));
		return 1;
	}

	return notify_fail("果農拄著竹竿憨憨一笑﹕客官問這個做甚﹖園裡活計忙﹐閒話改日再嘮罷。\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎喲﹗客官這是做甚﹖老朽一個看園種果的山野之人﹐與你無冤無仇哪﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
