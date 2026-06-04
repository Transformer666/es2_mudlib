// lingyunyu.c -- 凌筠語：來路不明、掛單於朱雀大街小樓客店的暗市異人，
//                以重金私換魔道至寶「闇之魔戒」(str+5 指環)的交易人。
//
// 來歷（承接 canon：docs 01-世界觀與劇情/05-主線任務與NPC.md L126
//   「凌筠語 — 換闇之魔戒 (str+5)」；docs 未明確指定位置，依任務指派置於京畿
//   一既有客棧——朱雀大街上的小樓客店(/d/capital/inn.c)）：
//   凌筠語生得清麗孤冷﹐一身玄衣﹐終日揀著小樓客店西廂臨窗一張清靜的桌子﹐
//   面前一壺殘茶﹐眼觀往來客商﹐似在等甚麼人。她隨身揣著一枚自魔道一脈輾轉
//   流出的古戒——『闇之魔戒』﹐戴之能教人筋骨暴張、氣力倍增(str+5)。然她從不
//   白送﹐只肯與識貨、且出得起重金的江湖客私下交易：銀貨兩訖﹐戒歸有緣。
//
// 交易機制（ask-path 為主、同步交付——照 content-town-questtemplate.md 鐵則 2）：
//   ask lingyunyu about 闇之魔戒   → do_ask：點明魔戒之能與換戒之資(一兩黃金)。
//   ask lingyunyu about 交易       → 同上(別名 topic)。
//   湊足換金後 ask lingyunyu about 換戒（GIVE TOPIC，需身懷 >=10000 文之錢）
//                                  → 於 handler 內驗資、同步扣款、同步 new+move 交付
//                                     闇之魔戒、隨即設旗標 quest/sq_lingyunyu=1。
//   accept_object：玩家亦可逕 give <N>兩 gold/coin to lingyunyu 成交(替代路徑)。
//
// 同步交付（本專案頭號 bug class 之防範）：發戒在 do_ask / accept_object handler 內
//   直接 new()+move(who)、且在設完成旗標之前；絕不放進延遲的 do_chat closure
//   （玩家中途離場會「戒沒了、旗標卻記完成」soft-lock）。move 回 1 落玩家身上﹐
//   move 失敗(極罕)才退落到地上(ob->move(environment()))。
//
// 防重領：以玩家身上旗標 quest/sq_lingyunyu 為憑——已成交(==1)者再 ask 換戒只給
//   純氣氛對白、不重發戒、不重扣款；present("dark ring", who) 為輔。
//
// 可測性：換戒之 gate 由 me->pay_money(10000) 把關(讀 coin/silver/gold)﹐wizard 可滿足——
//   clone /obj/money/coin ; call coin->set_amount(10000) ; call coin->move(me)
//   （或 give 1 兩 gold to lingyunyu 走 accept_object）。

#include <npc.h>

inherit F_VILLAGER;

// 換戒之資：一兩黃金 = 10000 文錢（魔道至寶﹐索價自然不菲）。
#define RING_PRICE  10000
#define DARK_RING   "/d/capital/npc/obj/dark_ring"

int do_ask(string arg);
private void hand_ring(object who);

void create()
{
	set_name("凌筠語", ({ "lingyunyu", "ling yunyu", "ling" }) );
	set("nickname", "暗市異人");
	set_attr("str", 22);
	set_attr("dex", 26);
	set_attr("int", 24);
	set_attr("wis", 22);
	set_attr("spi", 20);
	set_attr("con", 20);
	set_attr("cor", 16);
	set_race("human");
	set_class("fighter");
	set_level(18);
	set("gender", "female");
	set("age", 29);

	set_skill("unarmed", 60);
	set_skill("dodge", 80);
	set_skill("parry", 60);
	set_skill("force", 80);
	set_skill("sword", 60);

	set("long",
		"一個來路不明的玄衣女子。她生得清麗孤冷﹐眉宇間鎖著一縷化\n"
		"不開的幽寒﹐終日揀著小樓客店西廂臨窗一張清靜的桌子坐著﹐面\n"
		"前一壺早已涼透的殘茶﹐手指卻不住地摩挲著左手食指上一枚烏黑\n"
		"的古戒——那戒通體吞光噬影﹐似有縷縷幽暗的氣息在其上吞吐。她\n"
		"眼觀著往來的客商旅人﹐神色淡漠﹐似在等甚麼人、又似在掂量著\n"
		"甚麼。聽店裡的夥計悄聲說﹐這位姑娘揣著件魔道流出的寶貝﹐只\n"
		"肯與出得起重金的江湖客私下交易。\n"
		"你或許可以問問她﹕ask lingyunyu about 闇之魔戒。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"凌筠語指尖緩緩摩挲著那枚烏黑的古戒﹐戒面幽暗的光影隨之微微一顫﹐她眼神卻飄向遠處。\n",
		"凌筠語端起那壺涼透的殘茶呷了一口﹐淡淡道﹕識貨的人﹐總會來的。\n",
		"凌筠語斜睨了堂中往來的客商一眼﹐又垂下眼簾﹐似是無一個入得了她的眼。\n",
	}));
	setup();
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player()) && userp(this_player()) ) {
		if( !is_fighting() && !this_player()->query("quest/sq_lingyunyu") )
			do_chat((: command,
				"say 這位客官面生﹐眼力倒似不差——可是來尋我這枚戒子的﹖" :));
	}
}

// 同步交付闇之魔戒：直接 new + move(who)（玩家此刻必在場）。
// move 回 1 落玩家身上﹐move 失敗(極罕)才退落到地上。
private void hand_ring(object who)
{
	object ring = new(DARK_RING);
	message_vision(
		"凌筠語自指上褪下那枚烏黑的古戒﹐指尖一旋﹐將它輕輕擱到$N掌心﹐"
		"低聲道﹕此戒魔力暴烈﹐你可要拿捏得住。\n", who);
	if( !ring->move(who) ) ring->move(environment());
}

int do_ask(string arg)
{
	object me = this_player();

	if( !arg )
		return notify_fail("你想問這位玄衣女子甚麼﹖（試試 ask lingyunyu about 闇之魔戒）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("凌筠語正自摩挲著那枚古戒出神﹐一時沒理會你。\n");

	// 問魔戒 / 交易：點明魔戒之能與換戒之資（純氣氛 + 指路）
	if( arg == "lingyunyu about 闇之魔戒"
	||  arg == "lingyunyu about 魔戒"
	||  arg == "lingyunyu about 交易"
	||  arg == "lingyunyu about 戒指"
	||  arg == "lingyunyu about 戒子"
	||  arg == "ling yunyu about 闇之魔戒"
	||  arg == "ling about 闇之魔戒"
	||  arg == "lingyunyu about ring"
	||  arg == "lingyunyu about dark ring"
	||  arg == "lingyunyu about trade" ) {
		// 已成交者：純氣氛、不再開口賣戒（防重領的指路層防呆）
		if( me->query("quest/sq_lingyunyu") ) {
			do_chat((: command,
				"say 客官手上那枚闇之魔戒﹐戴穩了麼﹖此戒只此一枚相付﹐我已了卻一樁心事﹐莫再來尋了。" :));
			return 1;
		}
		do_chat(({
			(: command, "say 客官好眼力。我這枚『闇之魔戒』﹐乃魔道一脈輾轉流出的古物——戴之能教人筋骨暴張、氣力倍增﹐臨敵時力沉招猛﹐遠勝尋常。" :),
			(: command, "say 只是這魔戒魔力暴烈、反噬亦烈﹐尋常人駕馭不住﹐我也不肯白送了去害人。客官若真要﹐須出得起價——一兩黃金﹐銀貨兩訖﹐戒歸有緣。" :),
			(: command, "say 湊足了換金﹐便對我說一聲『換戒』(ask lingyunyu about 換戒)﹐或逕將黃金交與我(give 1 兩 gold to lingyunyu)﹐這枚戒子﹐自當奉上。" :),
		}));
		return 1;
	}

	// 換戒（GIVE TOPIC）：驗旗標(防重領) → 驗資(可測 gate) → 同步扣款 → 同步發戒 → 設旗標
	if( arg == "lingyunyu about 換戒"
	||  arg == "lingyunyu about 換魔戒"
	||  arg == "ling about 換戒"
	||  arg == "lingyunyu about exchange"
	||  arg == "lingyunyu about buy" ) {
		// 防重領：已成交（或戒已在身）→ 純氣氛、不重發戒、不重扣款
		if( me->query("quest/sq_lingyunyu") || present("dark ring", me) ) {
			do_chat((: command,
				"say 此戒只此一枚﹐已付與客官了﹐莫再貪多。戴穩了﹐莫教那魔力反噬了自家。" :));
			return 1;
		}
		// gate（可測）：須身懷足額換金。pay_money 同步扣款、足額(回 1)方發戒﹔
		// 不足(回 0)或有值卻零錢不齊(回 2)皆不收不發（鏡 zhonghao.c 之 pay_money 模型）。
		if( me->pay_money(RING_PRICE) != 1 ) {
			do_chat((: command,
				"say 客官這點散碎銀錢﹐還換不得我這枚魔戒——換金是一兩黃金(一萬文錢)﹐湊足了再來罷。" :));
			return 1;
		}
		// 銀貨兩訖：同步發戒、即記旗標（發戒為直接 new+move﹐玩家此刻必在場）。
		// 不把發戒放進延遲的 do_chat——免玩家於回呼前離場致戒沒領、旗標卻記成交而卡關。
		hand_ring(me);
		me->set("quest/sq_lingyunyu", 1);
		do_chat((: command,
			"say 痛快。銀貨兩訖﹐這枚闇之魔戒﹐自今日起便歸客官了。它日若駕馭得住這身魔力﹐莫忘了凌筠語這一場交易。" :));
		return 1;
	}

	return notify_fail("凌筠語斜睨你一眼﹐淡淡道﹕問這個作甚﹖（試試 ask lingyunyu about 闇之魔戒）\n");
}

// 收款換戒（替代路徑）：玩家逕 give <N>兩 gold/coin to lingyunyu 成交。
//   ob 為錢(money_id)且足額(>= RING_PRICE 文)→ 同步發戒、設旗標、回 1
//   （give 指令於回 1 後自行 destruct 有值的錢——銀貨兩訖、足額換戒）。
//   已成交者收下的錢退還（回 0）；不足額退還（回 0）；非錢之物婉拒（回 0﹐不吞物）。
int accept_object(object who, object ob)
{
	if( ob->query("money_id") ) {
		// 防重領：已成交 → 退還﹐不再賣戒
		if( who->query("quest/sq_lingyunyu") || present("dark ring", who) ) {
			do_chat((: command,
				"say 客官的好意我心領了﹐只是這戒只此一枚、已付與你﹐這錢還是收回罷。" :));
			return 0;
		}
		if( (int)ob->value() < RING_PRICE ) {
			do_chat((: command,
				"say 客官這點錢﹐還換不得我這枚魔戒——換金是一兩黃金(一萬文錢)﹐湊足了再來罷。" :));
			return 0;       // 退還﹐不收
		}
		// 足額：同步發戒、即記旗標（回 1 後 give 自行銷毀足值的錢﹐多給不找零）
		hand_ring(who);
		who->set("quest/sq_lingyunyu", 1);
		do_chat((: command,
			"say 痛快。銀貨兩訖﹐這枚闇之魔戒﹐自今日起便歸客官了。" :));
		return 1;
	}

	// 其餘物事：婉拒﹐不收下（避免吞掉玩家的尋常物品）
	do_chat((: command, "say 這個我用不上﹐客官還是自個兒留著罷。" :));
	return 0;
}

int accept_fight(object ob)
{
	do_chat((: command, "say 客官這是作甚﹖我不過是個做點小買賣的過客﹐犯不著動手。" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
