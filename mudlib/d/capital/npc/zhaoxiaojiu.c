// zhaoxiaojiu.c -- 京畿支線「畫卷換符」之贈物人：賣卜畫符的老符師趙曉九。
//
// 來歷（承 docs/01-世界觀與劇情/05-主線任務與NPC.md L128：
//   「趙曉九 @ 巫山客棧 → 書換先天符 (Scroll of nature)」）：
//   原典裡趙曉九守在巫山客棧，以「一卷符經換一道先天符」的規矩與往來道客
//   結緣。京畿域眼下尚無巫山客棧，帝都唯一在營的客棧酒肆便是朱雀大街的「小
//   樓客店」(d/capital/inn.c)，這位雲遊的老符師遂掛單於此一隅、就著燈火為人
//   賣卜畫符。他本是茅山旁支「先天符」一脈的傳人，半生臨摹一卷《先天符經》，
//   早把那道蘊先天罡氣、三等符中至貴的「先天符」畫法爛熟於心。逢著有道緣、
//   肯與他論一論符經的後生，他一高興，便當場以雞冠血調辰砂、擇時運筆，畫成
//   一道先天符相贈——「符經之道，原該與有緣人共參，後生且收著」。
//
// 設計取捨（先天符乃 canon 既有之可疊加符紙，務必沿用、不另立 blueprint）：
//   先天符早有定本 /obj/talisman/xiantian_fu.c（COMBINED_ITEM 可疊加符紙，
//   施茅山五雷/幻術時 std/magic.c 以 present("xiantian fu", me) 為閘、按 base_name
//   合併同類）。COMBINED_ITEM 之合併以 base_name(blueprint 路徑) 為準，若另在
//   d/capital/npc/obj 立一個 xiantian_fu，與正本路徑不同→兩疊符無法合併、且憑空
//   多出一種「先天符」分身，壞了符紙經濟與施法閘。故此處比照 d/maoshan/npc/
//   laodao.c：直接 new("/obj/talisman/xiantian_fu") 同步交付正本，不另造 obj 檔。
//
// 交付（同步、ask-path、防重領 — 照 content-town-questtemplate.md 鐵則）：
//   * 玩家 `ask zhaoxiaojiu about 符經`（或 about 先天符／about 符／about scroll）即觸發。
//   * give_fu() 內直接 new()+move(who) 同步交付，絕不延入 do_chat 之 closure
//     (玩家中途離場會「物沒了旗標卻記完成」soft-lock — 本專案頭號 bug class)。
//   * 防重領：旗標 quest/sq_zhaoxiaojiu，並以 present("xiantian fu", who) 雙重把關；
//     旗標已記而符不在身（已用去）→ 同步補發一道，免「換過了卻空手」之窘。
//   * 「書換」(以符經換符)取作對白風味，不設硬性門禁——後生一問即得一道，符合
//     GIVE 鐵則「一次 ask 到手」。
//   不 replace_program（NPC 需保有 do_ask / init 之 add_action）。

#include <ansi.h>
#include <npc.h>

inherit F_VILLAGER;

#define XIANTIAN  "/obj/talisman/xiantian_fu"

int do_ask(string arg);

void create()
{
	set_name(HIC "趙曉九" NOR, ({ "zhaoxiaojiu", "zhao xiaojiu", "fu master", "fortune teller" }) );
	set("nickname", "老符師");
	set_attr("str", 16);
	set_attr("dex", 18);
	set_attr("int", 24);
	set_attr("wis", 24);
	set_attr("spi", 22);
	set_attr("con", 18);
	set_race("human");
	set_class("taoist");
	set_level(15);
	set("sect", "茅山派");
	set("rank", "先天符傳人");

	set_skill("unarmed", 30);
	set_skill("dodge", 45);
	set_skill("parry", 40);
	set_skill("force", 70);
	set_skill("dao force", 70);
	map_skill("force", "dao force");
	set_skill("magic", 90);
	set_skill("make_scroll", 95);
	set_skill("literate", 60);

	set("age", 67);
	set("gender", "male");
	set("long",
		"這是一位雲遊掛單在客店一隅、賣卜畫符的老符師趙曉九。他鬚眉\n"
		"花白、面皮枯瘦﹐一身洗得發白的青布道袍上沾著經年的點點硃砂\n"
		"紅﹐袖口磨得起了毛邊。他面前一張矮几﹐几上鋪開半卷已被摩挲\n"
		"得卷邊發黃的《先天符經》﹐一方端硯、一碟調好的辰砂、一管禿了\n"
		"鋒的狼毫﹐還壓著幾道畫成晾乾的黃符。他半瞇著眼﹐就著昏黃的\n"
		"燈火﹐一筆一畫地臨著符經上的符文﹐周身竟隱隱透著一縷收束得\n"
		"極好的先天罡氣——分明是茅山「先天符」一脈深藏不露的傳人。聽\n"
		"他自言自語﹐這卷符經之道﹐他半生只巴望著尋個有道緣的後生﹐\n"
		"好歹有個共參的人。你或許可以問問他﹕ask zhaoxiaojiu about 符經。\n");
	set("chat_chance", 5);
	set("chat_msg", ({
		"趙曉九蘸飽了辰砂﹐就著燈火凝神運筆﹐一道符文勾連如周天星斗﹐一氣呵成。\n",
		"趙曉九拈起一道畫成的黃符﹐對著燈光看了看符膽走勢﹐微微頷首﹐擱到一旁晾著。\n",
		"趙曉九撫著那卷發黃的《先天符經》﹐喟然自語﹕先天之道﹐至貴至罕……可惜難覓有緣人哪。\n",
		"趙曉九半瞇著眼打量你﹐捻鬚一笑﹕後生骨相清正﹐莫非與我這符經有些道緣﹖(ask zhaoxiaojiu about 符經)\n",
	}));
	setup();
	carry_object("/obj/area/obj/robe")->wear();
	carry_money("coin", 30);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

// 同步交付一道先天符：直接 new()+move(who)，不入延遲 closure。
// 沿用 canon 正本 /obj/talisman/xiantian_fu(可疊加符紙)，move 成功則落玩家身上、
// 自動與同類先天符合併﹔失敗(滿載等)才退落到地上，不憑空消失。
private void give_fu(object who)
{
	object fu;

	if( !who || environment(who) != environment() ) {
		command("say 咦……人呢﹖後生且站定了﹐老夫這道符纔好遞與你。");
		return;
	}
	// 防重領：旗標已記、且符仍在身→不重發（純氣氛由 do_ask 處理）。

	fu = new(XIANTIAN);
	if( !fu->move(who) )			// move 回 1 為成功、0 為失敗(滿載等)
		fu->move(environment());	// 滿載→落於客店地上，不憑空消失
	message_vision(
		HIC "$N就著燈火、以雞冠血調辰砂凝神運筆﹐一道蘊著先天罡氣的『先天符』"
		"一氣呵成﹐口中念念有詞﹐指尖一彈﹐將那道朱光隱隱的黃符鄭重遞到$n手中﹕"
		"先天之道﹐原該與有緣人共參﹐後生且收著﹗\n" NOR,
		this_object(), who);
	// 旗標於符確實交付後才記，避免「旗標走了符沒到」卡關。
	who->set("quest/sq_zhaoxiaojiu", 1);
}

int do_ask(string arg)
{
	object me = this_player();

	if( !arg ||
		(arg != "zhaoxiaojiu about 符經"
		&& arg != "zhaoxiaojiu about 先天符"
		&& arg != "zhaoxiaojiu about 符"
		&& arg != "zhaoxiaojiu about 書"
		&& arg != "zhaoxiaojiu about 先天符經"
		&& arg != "zhaoxiaojiu about scroll"
		&& arg != "zhaoxiaojiu about fu"
		&& arg != "zhao xiaojiu about 符經"
		&& arg != "fu master about 符經"
		&& arg != "fortune teller about 符經") )
		return notify_fail("你想問這位老符師甚麼﹖（試試 ask zhaoxiaojiu about 符經）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("趙曉九正伏在矮几前凝神畫符﹐一時沒理會你。\n");

	// 已贈過、且符仍在身：純氣氛，不重發（防重領）。
	if( me->query("quest/sq_zhaoxiaojiu") && present("xiantian fu", me) ) {
		do_chat((: command,
			"say 哈哈﹐那道先天符老夫不是早與你了麼﹖後生好生收著﹐這符經之道﹐你我日後再慢慢參詳。" :));
		return 1;
	}

	// 旗標已記、符卻不在身（已焚去施法）：同步補發一道，只道一句寒暄。
	if( me->query("quest/sq_zhaoxiaojiu") && !present("xiantian fu", me) ) {
		do_chat((: command,
			"say 怎麼﹖那道先天符焚去了﹖也罷﹐你我既有道緣﹐老夫再與你補上一道便是。" :));
		give_fu(me);
		return 1;
	}

	// 首次：論符經而相贈。對白(do_chat)只擺「書換」之 say 風味；交付一律走同步的
	// give_fu(me) 直接呼叫——絕不把 give 塞進 do_chat closure(那會延後約三個心跳，
	// 玩家中途離場即「旗標走了符沒到」soft-lock，本專案頭號 bug class、batch-1 jieyan 教訓)。
	do_chat(({
		(: command, "say 難得有後生肯與老夫論這符經……來來來，且坐下說話。" :),
		(: command, "say 老夫這半卷《先天符經》﹐臨了大半輩子。先天符蘊先天罡氣﹐須擇先天之時、以雞冠血調辰砂﹐凝神一筆而成﹐半點差池便前功盡棄——是三等符中至貴至罕的一道。" :),
		(: command, "say 原本的規矩﹐是要以一卷符經來換的﹔可老夫看你骨相清正、與這符經有道緣﹐這卷經、這道符之理﹐合該與有緣人共參。也罷﹗老夫這就當場與你畫成一道先天符﹐贈與你這後生﹗" :),
	}));
	give_fu(me);
	return 1;
}

// 收物換符以 do_ask（ask zhaoxiaojiu about 符經）為準；此處 accept_object 婉拒
// 玩家直接遞來的物事，避免吞掉玩家物品，並提示改用 ask。
int accept_object(object who, object ob)
{
	do_chat((: command,
		"say 後生的東西老夫不便收。你若要這先天符﹐ask zhaoxiaojiu about 符經 便是﹐你我論一論符經﹐老夫自當場與你畫成一道相贈。" :));
	return 0;
}

int accept_fight(object ob)
{
	do_chat((: command,
		"say 哎呀﹗後生莫動粗﹗老夫一個賣卜畫符的糟老頭﹐當不起你這般動手哪﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
