// gongsunzhi.c -- 道士派支線「公孫志贈符」之贈物人：符師公孫志。
//
// 落腳：百花村紅燈客棧(/d/flower/redinn) — 道士正陽符兌換點。NPC 檔仍存於本路徑
// (d/capital/npc/gongsunzhi.c，沿用既有檔免重複)，但由 redinn 的 objects mapping
// 載入；原誤置於 d/capital/inn.c(小樓客店)的載入已移除，全世界僅此一處。
//
// 來歷（承 docs/01-世界觀與劇情/05-主線任務與NPC.md「重要任務 NPC 一覽」+
//   docs/03-門派與武功/02-道士-天師與茅山.md「百花村 紅燈客棧 lv120」一列：
//   公孫志 @ 百花村紅燈客棧 → 書換正陽符 (Scroll of yang)。他寓居這座脂粉風月
//   的紅燈客棧客舍一隅，與滿堂紅塵喧鬧恰成一靜一鬧之對照，雲遊以符渡人）：
//   公孫志乃道門正陽一脈的符師，鬚眉清癯、道骨仙風，腰懸一只盛符的舊葫蘆，雲遊
//   四方，以符籙渡有緣之人。他精研道門三符——正陽(陽)、先天(和)、少陰(陰)，獨擅
//   正陽一脈那一道封了純陽真火、能驅陰護心的『正陽符』。原本他這符是要拿江湖奇
//   書相易的(docs「書換」)，然其人重的本是「符緣」二字——逢著肯虛心問道、與符投
//   緣的後生，便慨然將親筆書就的正陽符解贈，不拘一本書的有無。
//
// 交付（同步、ask-path、防重領 — 照本專案 content-town questtemplate 鐵則）：
//   * 玩家 `ask gongsunzhi about 符`（或 about 正陽符／about 正陽／about charm 等）即觸發。
//   * 「書換」之說只擺進對白作風味，不設硬性 gate——一句 ask 即得符（wizard 一步可測）。
//   * give_charm() 內直接 new()+move(who) 同步交付，絕不放進 do_chat 之延遲 closure
//     (玩家中途離場會「物沒了旗標卻記完成」soft-lock — 本專案頭號 bug class)。
//   * 防重領：旗標 quest/sq_gongsunzhi，並以 present("yang charm", who) 雙重把關。
//   * 補發：旗標已記但符不在身(玩家弄丟/賣失)→ give_charm 同步補發一道，不憑空卡關。
//   不 replace_program（NPC 需保有 do_ask / init 之 add_action）。

#include <ansi.h>
#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name(HIC "公孫志" NOR,
		({ "gongsunzhi", "gong sunzhi", "charm master", "taoist" }) );
	set_race("human");
	set_class("commoner");
	set_level(18);

	set("age", 57);
	set("gender", "male");
	set("long",
		"一位鬚眉清癯、道骨仙風的雲遊符師。他一身洗得發白的青布道\n"
		"袍，足踏芒鞋，頭挽道髻，三綹長鬚垂胸，面色卻紅潤如朱，雙\n"
		"目澄澈有神，行止間自有一股淡泊出塵之氣。腰間斜懸著一只磨\n"
		"得油亮的舊葫蘆，葫蘆口隱隱透出辰砂硃筆的氣味，想是盛符之\n"
		"用。他寓居這客舍一隅，時而就著燈火執筆書符，時而闔目參道，\n"
		"似在靜候一段與符有緣的後生來問道。\n");
	set("chat_chance", 6);
	set("chat_msg", ({
		"公孫志執起硃筆，於黃麻紙上盤虬走龍地落下一道符文，口中念念有詞。\n",
		"公孫志拈鬚微笑，望著你緩緩道﹕道門三符，分主陽、和、陰三氣，後生可知﹖\n",
		"公孫志輕拍腰間那只油亮的舊葫蘆，自語﹕符以渡人，渡的是個『緣』字啊……\n",
		"公孫志闔目盤坐，周身隱隱透出一縷溫煦的純陽之氣，似在參那正陽一脈的符理。\n",
		"公孫志睜開眼，朝你頷首﹕後生若與符有緣，何妨問我一問﹖(ask gongsunzhi about 符)\n",
	}));
	setup();
	carry_money("coin", 50);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

// 同步交付/補發正陽符：直接 new()+move(who)，不入延遲 closure。
// move 成功→符在玩家身上﹔失敗(滿載等)→落於現場(environment())，不掉地給 0。
private void give_charm(object who)
{
	object ob;

	if( !who || environment(who) != environment() ) {
		command("say 咦……後生何往﹖且站定了，貧道這就將這道正陽符付你。");
		return;
	}
	// 符已在身→不重發（補發只在「旗標已記、符卻不在」時才走到此函式）。
	if( present("yang charm", who) ) {
		command("say 那道正陽符既已在後生身上，便好生佩著罷，莫再求多。");
		return;
	}

	ob = new(__DIR__"obj/yang_charm");
	if( !ob->move(who) )			// move 回 1 為成功、0 為失敗(滿載等)
		ob->move(environment());	// 滿載→落於客舍地上，不憑空消失、不掉地給 0
	message_vision(
		HIR "$N自腰間舊葫蘆中取出一道辰砂硃筆書就的符籙，鄭重遞與$n，"
		"含笑道﹕正陽純火，封於此符，後生且收著，了卻你我一段符緣﹗\n" NOR,
		this_object(), who);
}

int do_ask(string arg)
{
	object me = this_player();

	if( !arg ||
		(arg != "gongsunzhi about 符"
		&& arg != "gongsunzhi about 正陽符"
		&& arg != "gongsunzhi about 正陽"
		&& arg != "gongsunzhi about 符籙"
		&& arg != "gongsunzhi about 道門三符"
		&& arg != "gongsunzhi about scroll"
		&& arg != "gongsunzhi about scroll of yang"
		&& arg != "gongsunzhi about charm"
		&& arg != "gong sunzhi about 符"
		&& arg != "charm master about 符"
		&& arg != "charm master about charm"
		&& arg != "taoist about 符") )
		return notify_fail("你想問這位符師甚麼﹖（試試 ask gongsunzhi about 符）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("公孫志正凝神執筆書著符，無暇理你。\n");

	// 已贈過：旗標已記。符在身→純氣氛﹔符不在身(弄丟/賣失)→同步補發一道。
	if( me->query("quest/sq_gongsunzhi") ) {
		if( present("yang charm", me) ) {
			do_chat((: command,
				"say 那道正陽符貧道既已付你，便好生佩著罷——符以護身，莫教這縷純陽斷了。" :));
			return 1;
		}
		// 旗標已記、符卻不在：補發（同步），對白只擺氣氛。
		give_charm(me);
		do_chat((: command,
			"say 咦﹖那道正陽符怎不見了﹖也罷，符既與你有緣，貧道便再書一道與你，仔細收著。" :));
		return 1;
	}

	// 首次：贈符。對白只擺氣氛（含「書換」之說作風味，不設硬性 gate），交付走同步 give_charm()。
	give_charm(me);
	me->set("quest/sq_gongsunzhi", 1);
	do_chat(({
		"公孫志擱下硃筆，拈鬚端詳了你半晌，眼底掠過一絲讚許。\n",
		(: command, "say 後生肯虛心問起這道符理，難得，難得。貧道雲遊四方，本是要拿一本江湖奇書，方換我這正陽符的——" :),
		(: command, "say ——可貧道以符渡人，重的本是個『緣』字。看你眉宇間正氣未失，與我這正陽一脈倒是投緣，書之有無，何足計較﹖" :),
		(: command, "say 此符以辰砂硃筆書就，內封一縷純陽真火，佩之於身能驅陰護心、暖體壯神。後生持去罷，他日闖蕩江湖，也好有道護身的符。" :),
	}));
	return 1;
}

int accept_fight(object player)
{
	do_chat("公孫志拂塵一擺，淡然道﹕後生何苦動粗﹖貧道一介書符的方外人，與你無爭。\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
