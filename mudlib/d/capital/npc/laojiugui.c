// laojiugui.c -- 京畿支線「醉贈寶袋」之委託人：老酒鬼。
//
// 來歷（承 docs/01-世界觀與劇情/05-主線任務與NPC.md「重要任務 NPC 一覽」一列：
//   老酒鬼 @ 百里香客棧 → 醉中贈混元一氣袋(可儲真氣的寶袋)。京畿域現以「小樓
//   客店」(d/capital/inn.c)為帝都唯一在營的客棧酒肆，這位終日泡在酒肆裡的老
//   酒鬼便掛單於此）：
//   他是當年一位散盡功名、遁入市井的內家高人——早歲以一身渾厚內力名動江湖，
//   後因故心灰，自此終日醺醺然地泡在帝都的酒肆裡，唯餘一只隨身溫養了半世的
//   舊皮囊「混元一氣袋」。他看似潦倒糊塗，醉眼朦朧，卻是個眼力毒辣的明白人；
//   逢著投緣、又肯陪他喝兩盅的後生，一高興，便將這伴了他半世、能儲真氣養內
//   息的寶袋解下相贈——「混元一氣，盡在此囊，後生且收著」。
//
// 交付（同步、ask-path、防重領 — 照 content-town-questtemplate.md 鐵則）：
//   * 玩家 `ask laojiugui about 酒`（或 about 混元一氣袋／about wine）即觸發。
//   * give_pouch() 內直接 new()+move(who) 同步交付，絕不延入 do_chat 之 closure
//     (玩家中途離場會「物沒了旗標卻記完成」soft-lock — 本專案頭號 bug class)。
//   * 防重領：旗標 quest/sq_laojiugui，並以 present("hunyuan pouch", who) 雙重把關。
//   不 replace_program（NPC 需保有 do_ask / init 之 add_action）。

#include <ansi.h>
#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name(HIM "老酒鬼" NOR, ({ "laojiugui", "old drunkard", "drunkard" }) );
	set_race("human");
	set_class("commoner");
	set_level(15);

	set("age", 63);
	set("gender", "male");
	set("long",
		"一個蜷在牆角酒桌旁、醺醺然的邋遢老者。他鬚髮花白糾結，一\n"
		"身打了補丁的舊葛袍上盡是經年的酒漬，懷裡死死摟著一只油黑\n"
		"發亮的舊皮囊，醉眼惺忪，口中含混地哼著不成調的小曲。乍看\n"
		"是個落魄潦倒的酒鬼，可你若凝神看去，卻覺他渾濁的眼底偶爾\n"
		"精光一閃——那一身蜷起的筋骨間，竟隱隱透著一縷深不可測、收\n"
		"束得極好的渾厚內息，分明是位深藏不露的內家高人。他自顧自\n"
		"地舉著酒葫蘆灌酒，似是巴望著有個投緣的後生能陪他喝上兩盅。\n");
	set("chat_chance", 6);
	set("chat_msg", ({
		"老酒鬼仰脖灌了一大口酒，咂咂嘴，含混地嘟囔﹕好酒……好酒哇……\n",
		"老酒鬼醉眼朦朧地打量著你，嘿嘿一笑﹕後生，看你骨相不錯，可是個練家子﹖\n",
		"老酒鬼拍著懷裡那只油黑的舊皮囊，自言自語﹕混元一氣，盡在此囊……可惜，可惜啊……\n",
		"老酒鬼搖頭晃腦地嘆道﹕想老夫當年……唉，不提了，不提了，喝酒喝酒﹗\n",
		"老酒鬼壓低了嗓子﹕後生，肯陪老夫喝兩盅麼﹖(ask laojiugui about 酒)\n",
	}));
	setup();
	carry_money("coin", 30);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

// 同步交付混元一氣袋：直接 new()+move(who)，不入延遲 closure。
// move 成功→物在玩家身上；失敗(滿載等)→落於現場(environment())，不掉地給 0。
private void give_pouch(object who)
{
	object ob;

	if( !who || environment(who) != environment() ) {
		command("say 咦……人呢﹖後生且站定了，老夫這就把這寶貝與你。");
		return;
	}
	// 防重領：旗標已記、或袋已在身，皆不重發。
	if( who->query("quest/sq_laojiugui") || present("hunyuan pouch", who) ) {
		command("say 那只一氣袋老夫不是早與你了麼﹖收好了，莫弄丟嘍﹗");
		return;
	}

	ob = new("/d/capital/npc/obj/hunyuan_pouch");
	if( !ob->move(who) )			// move 回 1 為成功、0 為失敗(滿載等)
		ob->move(environment());	// 滿載→落於酒肆地上，不憑空消失、不掉地給 0
	message_vision(
		HIM "$N將懷裡那只油黑的舊皮囊解下，鄭重塞進$n手中，含淚道﹕"
		"混元一氣，盡在此囊，後生且收著，莫教這口真氣斷了傳承﹗\n" NOR,
		this_object(), who);
	// 旗標於袋確實交付後才記，避免「旗標走了袋沒到」卡關。
	who->set("quest/sq_laojiugui", 1);
}

int do_ask(string arg)
{
	object me = this_player();

	if( !arg ||
		(arg != "laojiugui about 酒"
		&& arg != "laojiugui about 喝酒"
		&& arg != "laojiugui about 混元一氣袋"
		&& arg != "laojiugui about 寶袋"
		&& arg != "laojiugui about wine"
		&& arg != "laojiugui about pouch"
		&& arg != "old drunkard about 酒"
		&& arg != "drunkard about 酒"
		&& arg != "drunkard about wine") )
		return notify_fail("你想問這位老酒鬼甚麼﹖（試試 ask laojiugui about 酒）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("老酒鬼正自顧自地灌著酒，醉得理不清你的話。\n");

	// 已贈過：純氣氛，不重發（防重領）。
	if( me->query("quest/sq_laojiugui") || present("hunyuan pouch", me) ) {
		do_chat((: command,
			"say 哈哈，那只一氣袋老夫早與你了，後生好生收著便是，再陪老夫喝兩盅﹗" :));
		return 1;
	}

	// 首次：醉中相贈。對白只擺氣氛，交付走同步的 give_pouch()。
	do_chat(({
		(: command, "say 哈哈﹗難得有後生肯陪老夫這糟老頭子說話……來來來，先敬你一口﹗" :),
		(: command, "say 老夫看你骨相不凡、內息也還算純正，是個練家子的好苗子……投緣，投緣﹗" :),
		(: command, "say 也罷﹗老夫這身功名都散了，這只伴了半世的混元一氣袋，便贈與你這後生罷﹗" :),
		(: give_pouch, me :),
	}));
	return 1;
}

int accept_fight(object player)
{
	do_chat("老酒鬼醉醺醺地擺手﹕哎喲喲，後生莫動粗，老夫一把老骨頭，經不起摔打哇……\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
