// saintwood_node.c -- 正史主線第四章「蜈蚣war」的關卡機關：聖木節（saintwood-node）。
//
// 設定（承接 summit.c 絕巔古碑：「聖木有節﹐節節通連天下地脈﹔巨蜈蝕節盤根﹐
//   借地脈之氣以自肥」）：
//   聖木深蟠京畿地脈之下的殘節﹐節節暴突如虬龍之骨﹐為巨蜈纏蝕盤踞、借以自肥。
//   聖木之節堅逾精鐵、凡刀不能傷——唯守木一脈密藏的聖劍『穿靈』(chuanling.c)方能
//   斫斷。聖木殘節密室(d/capital/saintroot.c)中布著數節﹐玩家須先 wield 穿靈﹐再
//   逐節『砍』(砍 / kan / hack)斷之。
//
// 機制（聖木節 = 砍-counter ＋ 蜈穴之門）：
//   * 每節須持穿靈(wield 之)方斫得斷。砍斷一節﹐玩家身上 quest/main_canon4_nodes
//     計數 +1﹐本節 destruct。
//   * 三節盡斷(計數達 SAINTWOOD_NODE_TOTAL)時﹕把玩家 quest/main_canon4 推進 1->2
//     （蝕節盤踞的巨蜈為斷節所驚﹐自殘節深處的蜈穴竄出迎敵）﹐並 message 高潮敘事。
//     聖木殘節密室往深處(in)的蜈穴(d/capital/wuxue.c)之門禁﹐即就 main_canon4 >= 2
//     把關(見 saintroot.c::valid_leave)。
//   * 防越界：計數封頂於 SAINTWOOD_NODE_TOTAL﹔旗標非 1 者砍節不推進(僅作斫斷風味)。
//
// 注意：本物 set("no_get",1)(節深嵌地脈﹐取不走)。密室於 reset/重載時依房間
//   set("objects") 補足三節（見 saintroot.c）。每節為獨立 clone﹐各自 add_action﹐
//   砍 handler 內就 arg 比對本節(present 解析)﹐故三節並存亦不誤觸。

#include <ansi.h>

inherit ITEM;

#define SAINTWOOD_NODE_TOTAL   3      // 密室中聖木節總數（砍斷此數即開蜈穴）。

int do_kan(string arg);

void create()
{
	set_name("聖木節", ({ "saintwood node", "node", "聖木節" }) );
	set_weight(500000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "節");
		set("value", 0);
		set("no_get", 1);
		set("no_sell", 1);
		set("long",
			"一節聖木深蟠京畿地脈之下的殘節﹐自岩壁間暴突而出﹐節身\n"
			"虬結嶙峋﹐宛若一截虬龍暴起的脊骨﹐通體炭黑泛玄、堅逾精\n"
			"鐵﹐叩之錚錚作金石之鳴。節上密密纏蝕著一圈圈巨蜈啃噬留\n"
			"下的齒痕與灼亮的涎毒——那盤蟠地脈的巨蜈﹐三百年來便是借\n"
			"著纏蝕這聖木之節、攫食其根脈靈氣以自肥。節木最深處猶幽\n"
			"幽透著一線將熄未熄的青芒﹐正一分一分為那涎毒所侵。凡刀\n"
			"斫在這聖木節上﹐唯火星四濺、難傷分毫——古碑有云﹐須得那\n"
			"柄以聖木心節為胎的聖劍『穿靈』﹐方能斫斷此節、斷巨蜈借\n"
			"以自肥的地脈之養。(持穿靈﹐砍 聖木節)\n");
	}
	setup();
}

// 每節 clone 各自綁定『砍』動作；handler 內就 arg 比對本節﹐故密室三節並存不誤觸。
void init()
{
	add_action("do_kan", ({ "砍", "kan", "hack" }) );
}

// 砍聖木節：須持穿靈(wield 之)方斫得斷。斷一節 -> 計數 +1、本節 destruct﹔三節盡
// 斷 -> 推進 quest/main_canon4 1->2、開蜈穴。who=this_player()。
int do_kan(string arg)
{
	object me = this_player();
	object weapon, node;
	string eq;
	int n;

	if( !me ) return 0;
	if( !arg )
		return notify_fail("你要砍甚麼﹖（試試﹕砍 聖木節）\n");

	// 就 arg 解析玩家所指之節﹔須正是本節(this_object())﹐方由本節 handler 回應，
	// 否則回 0﹐交由密室中另一節的 handler 處理（避免三節並存時誤觸／重覆觸發）。
	node = present(arg, environment(me));
	if( node != this_object() ) return 0;

	// 須持聖劍穿靈、且已 wield 之——聖木之節堅逾精鐵﹐凡刀不能傷。
	// 兵器一經 wield﹐其 query("equipped") 即為 "weapon/<skill>"(見 feature/equip.c)；
	// 故「穿靈在身且 equipped 以 weapon/ 起首」即為已執穿靈。
	weapon = present("chuanling", me);
	eq = objectp(weapon) ? weapon->query("equipped") : 0;
	if( !objectp(weapon) || !stringp(eq) || eq[0..6] != "weapon/" )
		return notify_fail(
			HIY "你提刀朝那聖木節重重斫落﹐『噹』地一聲火星四濺﹐虎口"
			"震得生疼﹐那堅逾精鐵的聖木節上﹐卻連半分痕跡也不曾留下——古"
			"碑分明說過﹕唯那柄以聖木心節為胎的聖劍『穿靈』﹐方能斫斷此"
			"節。你還是先尋出穿靈、握在手中(wield chuanling)再來罷。\n" NOR);

	// 斫斷本節。
	message_vision(
		HIC "$N雙手握定聖劍穿靈﹐凝起一身真力﹐朝那虬結暴突的聖木節當頭斫"
		"落﹗只聽『錚——』然一聲清越的金石長鳴﹐穿靈劍脊的青芒與聖木節最深"
		"處將熄的青芒驟然相激﹐那纏蝕節身的巨蜈涎毒滋滋退散——這一劍﹐竟硬"
		"生生將這堅逾精鐵的聖木殘節斫斷了一節﹗\n" NOR, me);

	// 計數 +1（封頂於總數﹐防越界）。
	n = me->query("quest/main_canon4_nodes");
	if( n < SAINTWOOD_NODE_TOTAL ) {
		n++;
		me->set("quest/main_canon4_nodes", n);
	}

	// 本節既斷，destruct。
	destruct(this_object());

	// 三節盡斷﹕推進旗標 1->2、開蜈穴（須身負第四章旗標==1 之真實玩家方推進；
	// 旗標非 1 者僅作斫斷風味，不推進——防越界與重覆）。
	if( n >= SAINTWOOD_NODE_TOTAL
	&&	userp(me)
	&&	me->query("quest/main_canon4") == 1 ) {
		me->set("quest/main_canon4", 2);
		tell_object(me,
			HIR "三節聖木殘節盡數斫斷的剎那﹐那截深蟠地脈的聖木殘根猛地一"
			"震﹐自岩壁深處傳來一陣令人牙酸的窸窣巨響——那盤蟠地脈、蝕節自肥"
			"的巨蜈﹐分明是為這斷節之痛所驚﹗只見密室深處那道為聖木殘根盤結"
			"封死的甬道轟然崩開﹐一股腥膻刺鼻的腐臭自洞中噴湧而出﹐無數細碎"
			"的爪足摩挲之聲自黑暗深處潮水般捲來——那啃噬聖木三百年的巨蜈﹐就"
			"要自牠的蜈穴中竄出來了﹗(往深處 in 可入蜈穴)\n" NOR);
	}

	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
