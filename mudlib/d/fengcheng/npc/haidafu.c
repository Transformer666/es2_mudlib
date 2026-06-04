// haidafu.c -- 海大富（Hai da fu），醇雨樓客棧「四廠」錦衣衛，
//              落腳於風城春風客棧前廳的一角當差。
//
// docs（docs/01-世界觀與劇情/05-主線任務與NPC.md）：
//   「重要任務 NPC」表：海大富 — 醇雨樓客棧四廠錦衣衛，
//        say 實戰經驗 / say 江湖歷練（消實戰經驗，最低 1000）。
//   「結仇陣營 → 官兵化解」段：仇恨深者 → 風城某客棧二樓 oldman 查
//        → 實戰經驗換海大富信任 → 他告知找【榮府老大】幫忙（500 gold）化解官兵仇恨。
//   故此海大富是「解官兵仇恨」鏈的一環：玩家以實戰經驗（score/combat）換取海大富的
//   信任，海大富再把下一步——去尋榮府老大（備 500 黃金）——指點給玩家。
//   （海大富本人「不」收金錢；那 500 gold 是日後付給榮府老大的，與本 NPC 無涉。）
//
// 故事背景：
//   海大富是內廷「四廠」當差的老錦衣衛，奉密令南下風城查探官兵與江湖人的恩怨。
//   錦衣衛最看重一個「能」字——你嘴上說與官兵的過節想了結，他偏不信口舌，只信
//   你刀頭舔血換來的真本事。你得把一身實戰閱歷攤給他看，他驗過了你的斤兩、認你
//   是條漢子，才肯透個門路：城裡榮府的老大與官面上有交情，備上 500 兩黃金的人情，
//   托他出面斡旋，這官兵的仇怨方有化解的指望。
//
// 機制（say-handler / relay_say 服務型 NPC；旗標存玩家身上：quest/haidafu_trust）：
//   玩家在同房 `say 實戰經驗`（或 `say 江湖歷練`）：
//     - 已得信任（quest/haidafu_trust >= 1）：double-grant 防呆——不再扣經驗、
//       不再重設旗標，改述「信任已得、去尋榮府老大」之言。
//     - 未得信任、score/combat >= 1000：同步扣 1000 點實戰經驗
//       （ob->add("score/combat", -1000)）、set quest/haidafu_trust = 1、
//       並 message 告知去尋【榮府老大】（備 500 黃金）化解官兵仇恨。
//     - 未得信任、score/combat < 1000：婉拒並說明最低門檻 1000。
//
// 鐵則遵循：
//   #10：本檔無 ::die()/destruct()——旗標/訊息逕在 relay_say handler 內順序寫就。
//   #11：本檔為 NPC（非房間），不涉 replace_program。
//   同步交付：扣經驗、設旗標、tell_object 全在 relay_say 內「直接」完成，
//             不丟進延遲的 do_chat closure 陣列（純氣氛對白才走 do_chat）。
//   say-handler 守衛：relay_say 開頭即 is_fighting()/is_chatting()/!userp(ob) 守衛。
//   範式來源（先 grep 既有檔模仿，未臆造 efun）：
//     - relay_say / is_fighting()/is_chatting() 守衛、do_chat 氣氛對白：
//         /d/snow/npc/foreman.c、/d/snow/npc/gammer.c
//     - quest 旗標 + 同步交付 + double-grant 防呆 + accept_fight：
//         /d/capital/npc/zhonghao.c
//     - score/combat 讀寫語意（實戰經驗）：/feature/char/score.c、
//         /d/tianling/npc/obj/rebirth_pill.c（僅讀以對齊語意，未改動該檔）

#include <ansi.h>
#include <npc.h>

inherit F_VILLAGER;

#define COMBAT_COST 1000        // 換取信任所需／所扣的實戰經驗門檻

void create()
{
	set_name(HIY "海大富" NOR, ({ "hai da fu", "haidafu", "hai dafu", "embroidered guard" }) );
	set("nickname", "錦衣衛海大富");
	set_attr("str", 24);
	set_attr("con", 22);
	set_attr("dex", 23);
	set_attr("int", 20);
	set_race("human");
	set_class("soldier");
	set_level(36);
	set_skill("unarmed", 80);
	set_skill("dodge", 80);
	set_skill("force", 70);
	set_skill("blade", 70);
	set_skill("parry", 70);

	set("gender", "male");
	set("age", 51);
	set("long",
		"這是個身形魁梧、目光如電的中年漢子，一襲半舊的玄色勁裝，腰\n"
		"間懸著一面早已磨得發亮的飛魚紋銅牌——識貨的人一眼便認得，那\n"
		"是內廷「四廠」錦衣衛的腰牌。他喚作海大富，奉了密令南下到這風\n"
		"城來，名為投宿，實則暗查官兵與江湖人的種種恩怨。錦衣衛最看重\n"
		"一個『能』字，他端坐在炭火旁，一雙鷹隼似的眼睛在往來旅客身上\n"
		"掃過，誰是花架子、誰是真刀真槍闖過來的，瞞不過他的眼。\n"
		"聽說你若與官兵結過仇怨想了結，不妨在他面前\n"
		"say 實戰經驗——把你一身的閱歷攤給他驗一驗。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		"海大富呷了一口熱茶，一雙鷹眼不動聲色地掃過廳裡往來的旅客。\n",
		"海大富按了按腰間那面飛魚紋的銅牌，低聲自語：這風城裡的恩怨，水可深著哪 ...\n",
		"海大富冷哼一聲：江湖上盡是些只會耍嘴皮子的，真本事的能有幾個。\n",
	}));
	setup();
	carry_object("/obj/area/obj/cloth")->wear();
}

// 已得信任後的固定說辭（double-grant 防呆與通關提示共用）。
private void tell_seek_rongfu(object ob)
{
	if( !ob || environment(ob) != environment() ) return;

	tell_object(ob,
		HIY "海大富壓低了嗓子，對你說道：你既是條有真本事的漢子，海某便指你一條"
		"明路——這風城裡『榮府』的老大，與官面上素有交情。你備上 500 兩黃金，托他"
		"出面斡旋，這官兵的仇怨，方有化解的指望。去尋榮府老大罷。\n" NOR);
}

// say-handler：玩家在同房 say 實戰經驗 / say 江湖歷練 即觸發。
// ob 為說話者；arg 為話的內容。
void relay_say(object ob, string arg)
{
	int combat;

	// say-handler 守衛：戰鬥中／閒談動畫中／非玩家所言，一律不理。
	if( is_fighting() || is_chatting() ) return;
	if( !ob || !userp(ob) ) return;
	if( !arg ) return;

	// 只認「實戰經驗」或「江湖歷練」這兩句切口；旁人閒聊不誤觸。
	if( strsrch(arg, "實戰經驗") < 0 && strsrch(arg, "江湖歷練") < 0 )
		return;

	// double-grant 防呆：已得信任者，不再扣經驗、不再重設旗標，只重述去尋榮府老大之言。
	if( ob->query("quest/haidafu_trust") >= 1 ) {
		command("say 海某早已驗過你的本事，認你是條漢子了。");
		tell_seek_rongfu(ob);
		return;
	}

	combat = ob->query("score/combat");

	// 未達門檻：婉拒並說明最低門檻。
	if( combat < COMBAT_COST ) {
		command("say 就憑你這點微末的閱歷，也敢說與官兵的恩怨想了結？");
		tell_object(ob,
			HIR "海大富搖了搖頭：刀頭舔血換來的真本事，海某一眼便看得出深淺。你這"
			"一身實戰經驗還不足 " + COMBAT_COST + " 點，回去再多歷練歷練，再來尋海某罷。\n"
			NOR);
		return;
	}

	// 合格：同步扣經驗、設旗標、給通關提示（全在 handler 內直接完成，不走延遲 do_chat）。
	ob->add("score/combat", -COMBAT_COST);
	ob->set("quest/haidafu_trust", 1);

	command("say 好！一身的閱歷攤在眼前，瞞不過海某的眼——你是條有真本事的漢子。");
	tell_object(ob,
		HIY "海大富細細驗過你一身刀頭舔血換來的閱歷，眼中露出幾分讚許，緩緩頷首——"
		"你只覺那畢生闖蕩江湖的實戰經驗，被他這一驗，竟似消磨去了一截。海某已認下你"
		"這條漢子，肯指你門路了。\n" NOR);
	tell_seek_rongfu(ob);
}

// 不收金錢、不收物事：那 500 黃金是日後付給榮府老大的，與海大富無涉。
int accept_object(object who, object ob)
{
	command("say 海某不收你的東西。你若與官兵的恩怨想了結，在海某面前 say 實戰經驗 便是。");
	return 0;
}

int accept_fight(object ob)
{
	command("say 放肆！竟敢對內廷四廠的錦衣衛動手，活得不耐煩了麼？");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
