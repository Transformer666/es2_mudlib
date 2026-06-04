// zhonghao.c -- 鍾豪（鍾管家），史部尚書府的老管家，掌府中人情往來。
//
// docs（docs/01-世界觀與劇情/05-主線任務與NPC.md「重要任務 NPC」表）：
//   鍾豪 / 鍾管家：收禮金 10（兩黃金）→ 贈神農打穀鞭（鞭類兵器）。
//
// 故事背景：
//   鍾豪是史部尚書府當差數十年的老管家﹐人喚一聲「鍾管家」。府中迎來送往、
//   人情禮數一概由他打理。府裡老太爺早年自神農古祠求得一柄鎮宅的『神農打穀
//   鞭』﹐如今老太爺已不耍這鞭﹐便囑鍾豪﹕凡有識貨、又備得起 10 兩黃金禮金的
//   江湖客上門﹐便代他把這鞭轉贈出去﹐物盡其用、結個善緣。鍾豪遂日日候在府
//   門廊下﹐替老太爺料理這宗人情。
//
// 支線（旗標存玩家身上：quest/sq_zhonghao）：
//   未贈 (0)：玩家 ask zhonghao about 禮金 / 神農打穀鞭——
//             鍾豪驗玩家身上是否備齊 10 兩黃金的禮金（pay_money(100000)﹐
//             即 10 gold × 10000 文）﹐收下禮金後﹐同步 new+move 把神農打穀鞭
//             交到玩家手上﹐並把旗標設為 1。
//   已贈 (1)：不再重複收禮、不再重複贈鞭——只給一段純氣氛的寒暄。
//             （穩健性：若旗標已記、鞭卻不在玩家身上——當作老太爺另有人情﹐
//               不重發、僅道一句﹐避免「買食物換賞」式的重領漏洞。）
//
// 鐵則：同步交付（handler 內直接 new+move﹐不放延遲 do_chat closure）﹔
//       收禮在贈鞭與記旗標之前﹐pay_money 失敗則不收不贈﹔NO replace_program
//       （本檔有 do_ask）。

#include <ansi.h>
#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name(HIY "鍾豪" NOR, ({ "zhonghao", "zhong hao", "steward", "butler" }) );
	set("nickname", "鍾管家");
	set_attr("int", 22);
	set_attr("wis", 20);
	set_attr("con", 18);
	set_race("human");
	set_class("commoner");
	set_level(14);
	set_skill("unarmed", 24);
	set_skill("dodge", 24);
	set_skill("literate", 30);

	set("gender", "male");
	set("age", 58);
	set("long",
		"這位便是史部尚書府當差數十年的老管家鍾豪了﹐府裡府外都敬\n"
		"喚他一聲『鍾管家』。他生得清瘦﹐三綹花白的鬍鬚梳理得一絲\n"
		"不苟﹐一襲半舊卻漿洗得筆挺的青緞長衫﹐外罩玄色比甲﹐腰間\n"
		"懸著一串管著府門庫房的銅鑰。他立在門廊的廊柱旁﹐背手而\n"
		"立﹐目光在往來的人身上溫和卻不失精明地掠過——數十年的管家\n"
		"歷練﹐教他一眼便能看出來客的斤兩。聽府丁說﹐這位鍾管家替\n"
		"老太爺掌著一宗人情﹕府裡有件鎮宅的奇兵﹐凡備得起禮金的識\n"
		"貨人﹐他便代老太爺轉贈出去。\n"
		"你或許可以問問他﹕ask zhonghao about 禮金。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"鍾管家捋了捋花白的鬍鬚﹐不動聲色地打量著門前往來的江湖客。\n",
		"鍾管家低聲自語﹕老太爺那柄神農打穀鞭﹐也該尋個識貨的主了 ...\n",
	}));
	setup();
	carry_object("/obj/area/obj/cloth")->wear();
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

// 同步把神農打穀鞭交到玩家手上：先 clone 到自己身上，再直接 move 給玩家；
// 失敗（玩家負重不足等）則落到地上，絕不憑空消失。
private void give_whip(object who)
{
	object whip;

	if( !who || environment(who) != environment() ) return;

	whip = new(__DIR__"obj/shennong_whip");
	if( !whip->move(who) ) whip->move(environment());

	who->gain_score("emprise", 60);
	who->gain_score("reputation", 50);
	who->gain_score("explorer fame", 40);

	message_vision(
		"鍾管家自門房內捧出一柄九節相連的『神農打穀鞭』﹐鄭重地奉到$N手上﹐"
		"含笑道﹕老太爺的人情﹐還望客官好生使著。\n",
		who);
}

int do_ask(string arg)
{
	object me = this_player();
	int q;

	if( !arg || (arg != "zhonghao about 禮金"
		&&   arg != "zhonghao about 神農打穀鞭"
		&&   arg != "zhonghao about 打穀鞭"
		&&   arg != "zhonghao about 鞭"
		&&   arg != "zhong hao about 禮金"
		&&   arg != "steward about 禮金"
		&&   arg != "butler about 禮金"
		&&   arg != "zhonghao about whip"
		&&   arg != "zhonghao about gift") )
		return notify_fail("你想問這位鍾管家甚麼﹖（試試 ask zhonghao about 禮金）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("鍾管家正打理著府裡的庶務﹐一時沒空理你。\n");

	q = me->query("quest/sq_zhonghao");

	// 已贈過神農打穀鞭：不重複收禮、不重複贈鞭，只作寒暄。
	if( q >= 1 ) {
		do_chat((: command,
			"say 客官這便是老相識了。老太爺那柄神農打穀鞭既已奉與客官﹐鍾某這宗人情也就了了﹐客官好生使著便是。" :));
		return 1;
	}

	// 尚未贈鞭：先驗玩家備齊 10 兩黃金禮金（pay_money 失敗則不收不贈）。
	// pay_money(100000) == 10 gold × 10000 文／兩；成功時即時扣下禮金。
	if( !me->pay_money(100000) ) {
		do_chat(({
			(: command, "say 客官有所不知﹐老太爺那柄神農打穀鞭乃自神農古祠求得的鎮宅奇兵﹐豈是白送的﹖" :),
			(: command, "say 按府裡的規矩﹐客官須備上 10 兩黃金的禮金﹐鍾某方好代老太爺把這鞭轉贈與你。客官且去湊齊了禮金﹐再來尋鍾某不遲。" :),
		}));
		return 1;
	}

	// 同步交付：收下禮金後，立刻 new+move 把鞭交到玩家手上，再記旗標。
	// （不把給鞭放進延遲的 do_chat——免玩家於回呼前離場致禮金已收、鞭卻沒領而卡關。）
	give_whip(me);
	me->set("quest/sq_zhonghao", 1);
	do_chat(({
		(: command, "say 客官這 10 兩黃金的禮金﹐鍾某代老太爺收下了。識貨的人﹐果然爽快﹗" :),
		(: command, "say 這柄『神農打穀鞭』﹐原是老太爺早年遊歷河洛、自一座供奉神農氏的古祠裡求得的鎮宅之物。鞭身九節﹐仿著上古神農氏打穀脫粒的連枷所鑄﹐年深日久﹐竟染上幾分惠濟蒼生的沉穩地氣﹐揮舞起來剛中帶韌﹐是件難得的奇兵。" :),
		(: command, "say 客官既是識貨之人﹐這鞭到了客官手上﹐也算物盡其用、不負老太爺一番心意。鍾某這廂代老太爺﹐與客官結個善緣了﹗" :),
	}));
	return 1;
}

// 收禮以 do_ask（ask zhonghao about 禮金）內的 pay_money 為準；此處 accept_object
// 婉拒玩家直接遞來的物事，避免吞掉玩家物品，並提示改用 ask。
int accept_object(object who, object ob)
{
	do_chat((: command,
		"say 客官的東西鍾某不便收。客官若要老太爺那柄神農打穀鞭﹐備齊 10 兩黃金的禮金﹐ask zhonghao about 禮金 便是。" :));
	return 0;
}

int accept_fight(object ob)
{
	do_chat((: command,
		"say 客官息怒﹗鍾某一個料理庶務的老管家﹐當不起客官這般動手哪。" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
