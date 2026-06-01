// fisher.c -- 村南魚塘守塘撈魚的漁戶（純氣氛閒談）；
//             兼李家村非戰鬥支線「李家祭祖供果」的配供人。
//
// 本檔原為村南魚塘守塘理網的氣氛 NPC。為支線「祭祖供果」加掛配供一段：
//   玩家自果園果農揀得供果籃後﹐持供果籃 ask fisher about 鯉魚（或
//   give fruit basket to fisher）-> 漁戶接過供果籃﹐自塘裡撈尾頂精神的活鯉、
//   添上自家的牲禮﹐拿果子在紅漆木盤上配齊三牲鮮果、交還玩家﹐記 quest/lijia_offer_fish = 1。
//   交付「祭祖供盤」實物的同時銷除手中的「供果籃」。指引玩家持供盤回李氏祠堂。
//   （driver give 指令不認中文「給」﹐故持供果籃 ask 即視同送件配供：同步配供、
//     交付供盤、記旗標、並銷除供果籃﹐與經 give 指令觸發 accept_object 等效。）
// 不動其原有的閒談 chat_msg 與 accept_fight。
//
// 祭祖供盤採直接 new + move(who) 同步交付——give／ask 皆由玩家觸發﹐玩家此刻必在場﹔
// move 回 1 為成功（落在玩家身上）﹐回 0（失敗）才退而落到地上。先交物、後記旗標
// （與 d/kangping cook、d/weiguo roaster、d/ziyan incenseman 一致）。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);
private void make_tray(object me);

void create()
{
	set_name("漁戶", ({ "fisher", "fisherman", "yuhu" }) );
	set("nickname", "漁戶");
	set_race("human");
	set_class("commoner");
	set_level(6);

	set("age", 41);
	set("gender", "male");
	set("long",
		"一個守著村南魚塘撈魚養魚的漁戶﹐生得黧黑精壯﹐褲腳捲到\n"
		"膝上﹐沾著塘泥﹐一雙手撈魚理網最是利落。他守著這塘魚守了多\n"
		"年﹐撈魚、養魚、配祭祖待客的牲禮﹐都是一把好手﹐合族紅白大\n"
		"事、祭祖待客要用塘裡的活魚﹐都來尋他。得閒也可問問他﹕\n"
		"ask fisher about 鯉魚。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"漁戶蹲在塘沿﹐把手裡的漁網理順了﹐瞇眼瞧著塘面游弋的紅鯉﹐盤算著哪一尾最肥壯。\n",
		"漁戶撒下一把魚食﹐塘裡的紅鯉登時擁過來爭食﹐攪碎一塘雲影﹐他看著咧嘴笑了。\n",
		"漁戶往塘裡探了探水溫﹐緩緩道﹕這塘水活﹐養出來的鯉魚鮮蹦﹐祭祖供奉、待客燒湯﹐都是頂好的。\n",
	}));
	setup();
	carry_money("coin", 30);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

// 配供：漁戶撈活鯉、添牲禮、拿供果在紅漆木盤上配齊﹐交付祭祖供盤、記旗標﹐
// 同時銷除玩家手中的供果籃。直接 new + move(me) 同步交付（玩家此刻必在場）﹐
// 先交供盤、銷供果籃、後記旗標。
private void make_tray(object me)
{
	object basket = present("lijiagongguo", me);
	object tray = new(__DIR__"obj/offer_tray");
	if( !tray->move(me) ) tray->move(environment());
	if( basket ) destruct(basket);
	me->set("quest/lijia_offer_fish", 1);
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這漁戶甚麼﹖（試試 ask fisher about 鯉魚）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("漁戶正蹲在塘沿撈魚理網﹐一時沒理會你。\n");

	// 鯉魚 / 配供 / 供盤：支線「祭祖供果」——持供果籃來配供盤
	if( arg == "fisher about 鯉魚"
	||  arg == "fisher about 魚"
	||  arg == "fisher about 活鯉"
	||  arg == "fisher about 供盤"
	||  arg == "fisher about 配供"
	||  arg == "fisher about 祭祖"
	||  arg == "fisher about fish"
	||  arg == "fisher about carp" ) {
		object me = this_player();
		int q = me->query("quest/lijia_offer");

		// 已完成或已配齊供盤：純氣氛收尾
		if( q >= 2 || me->query("quest/lijia_offer_fish") ) {
			do_chat((: command,
				"say 那盤祭祖供品﹐我已替客官配齊了。客官快持回李氏祠堂交與族長罷﹐莫教那尾活鯉擱蔫了、誤了合族祭祖的吉時。" :));
			return 1;
		}

		// 進行中、持供果籃：ask 即當作配供處理——配供、交供盤、銷供果籃、記旗標
		// （此路不經 give 指令﹐故由 make_tray 自行銷除玩家手裡的供果籃﹐
		//   與 accept_object 經 give 指令回 1 後自動銷除供果籃等效﹐免玩家
		//   留著供果籃重複觸發。）
		if( q == 1 && present("lijiagongguo", me) ) {
			message_vision(
				"漁戶接過$N手裡的供果籃﹐自塘裡撈起一尾紅鬚紅尾、鮮蹦亂跳的\n"
				"活鯉﹐又取來自家備的牲禮﹐拿果子一併在一方紅漆木盤上擺得齊整體面。\n", me);
			// 先同步配供、交付供盤、銷供果籃、記旗標﹐再以 do_chat 收尾（供盤已先到玩家手裡）。
			make_tray(me);
			do_chat(({
				(: command, "say 客官是李氏祠堂族長打發來備祭祖供品的罷﹖果農揀的這籃鮮果﹐果然形正色勻——配上我這塘裡的活鯉﹐最體面不過。" :),
				(: command, "say 我這就撈尾頂精神的活鯉﹐添上牲禮﹐拿這鮮果在紅漆木盤上配齊三牲鮮果。喏﹐這活鯉是塘裡現撈的﹐取個鯉躍龍門、子孫騰達的彩頭﹐是咱李家祭祖頂要緊的一味。" :),
				(: command, "say 喏﹐這盤祭祖供品﹐方纔已奉到客官手裡了﹐快持回李氏祠堂交與族長（ask elder about 祭祖﹐或 give offer tray to elder）﹐也好教合族趁吉時上香叩拜先祖﹐了卻一樁大事。" :),
			}));
			return 1;
		}

		// 進行中、未持供果籃：提示先去果園向果農揀果
		if( q == 1 ) {
			do_chat((: command,
				"say 客官要配祭祖的供盤﹖總得有籃供奉的鮮果配著罷。客官且去村心南面的李家果園﹐尋那位看園果農揀一籃供祖的鮮果來（ask picker about 鮮果）﹐我纔好替客官配齊供盤。" :));
			return 1;
		}

		// 未接任務：純風味帶過
		do_chat((: command,
			"say 祭祖供盤﹖客官說的是擺活鯉鮮果供奉先祖的供盤罷。那是咱合族祭祖頂要緊的東西﹐客官若為這供盤的事﹐還是先去李氏祠堂問問族長罷。" :));
		return 1;
	}

	// 純氣氛閒談：魚塘／養魚／李家村
	if( arg == "fisher about 魚塘"
	||  arg == "fisher about 塘"
	||  arg == "fisher about 養魚"
	||  arg == "fisher about 李家村"
	||  arg == "fisher about lijia" ) {
		do_chat(({
			(: command, "say 這守塘養魚的工夫啊﹐看著清閒﹐做著精細。塘水要活、魚食要勻、撈魚要揀肥壯的下網﹐養出來的鯉魚纔鮮蹦。我守了這塘多年﹐方敢說摸著了門道。" :),
			(: command, "say 咱這魚塘的水自村外溪澗引來﹐清而不竭﹐是合村李姓共養的。逢年過節、祭祖待客﹐塘裡的活魚便派上大用場。拿這活鯉供奉先祖﹐取個鯉躍龍門的彩頭﹐合族都歡喜。" :),
		}));
		return 1;
	}

	return notify_fail("漁戶抹了把臉爽利一笑﹕客官問這個做甚﹖坐下歇歇﹐瞧瞧這塘裡的紅鯉游得多歡罷。\n");
}

// 收下信物：
//   供果籃(fruit basket) -- 支線「祭祖供果」配供﹐持供果籃且任務進行中時
//   收下、配供、交付祭祖供盤、記旗標 lijia_offer_fish。
// 不在此 move／destruct 供果籃——give 指令於本函回 1 後會自行 destruct 有值的
// 供果籃（與 d/kangping cook、d/weiguo roaster、d/ziyan incenseman 一致）﹔非送件玩家／時機不符
// 則回 0 婉拒，不吞物。
int accept_object(object who, object ob)
{
	if( ob->id("fruit basket") ) {
		int q = who->query("quest/lijia_offer");

		// 未接任務／已完成：婉拒，不收下（避免吞掉供果籃）
		if( q != 1 ) {
			do_chat((: command,
				"say 這籃供果 ... 客官還是自個兒收著罷，我一時也用不上。" :));
			return 0;
		}

		// 已配過供盤（供盤已交）：婉拒，提示徑去回報祠堂
		if( who->query("quest/lijia_offer_fish") ) {
			do_chat((: command,
				"say 客官的供盤方纔已配齊了﹐這籃就煩客官留著罷。快持那盤祭祖供品回李氏祠堂交與族長便是（ask elder about 祭祖﹐或 give offer tray to elder）。" :));
			return 0;
		}

		// 進行中、持供果籃配供：配供、交付供盤、記旗標（供果籃由 give 指令於回 1 後自行銷除）
		message_vision(
			"漁戶接過$N遞來的供果籃﹐自塘裡撈起一尾紅鬚紅尾、鮮蹦亂跳的\n"
			"活鯉﹐又取來自家備的牲禮﹐拿果子一併在一方紅漆木盤上擺得齊整體面。\n", who);
		// give 指令會於本函回 1 後自行 destruct 供果籃﹐故此處 make_tray 只交供盤、記旗標﹔
		// 為穩妥﹐make_tray 內仍會嘗試銷除手中供果籃（present 取到的即將被 give 銷除的同一個）。
		make_tray(who);
		do_chat(({
			(: command, "say 客官是李氏祠堂族長打發來備祭祖供品的罷﹖果農揀的這籃鮮果﹐果然形正色勻——配上我這塘裡的活鯉﹐最體面不過。" :),
			(: command, "say 我撈尾活鯉、添上牲禮﹐拿這鮮果在紅漆木盤上配齊了。喏﹐這盤祭祖供品﹐方纔已奉到客官手裡了﹐快持回李氏祠堂交與族長（ask elder about 祭祖﹐或 give offer tray to elder）。" :),
		}));
		return 1;
	}

	// 其餘物事：婉拒，不收下（避免吞掉玩家的尋常物品）
	do_chat((: command, "say 這個我用不上﹐客官還是自個兒留著罷。" :));
	return 0;
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎呀﹗客官好沒道理﹗欺負我一個守塘撈魚的莊稼人做甚﹖" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
