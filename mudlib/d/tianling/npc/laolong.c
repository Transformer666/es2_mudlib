// laolong.c -- 老龍，摩雲麾下動物war殘部為首的孽畜之一，正史序章「逐念入山」
//             獸塚(youhe→beastgrave)中的第一頭 boss。
//
// 故事背景（承接前傳 beat 8 摩雲伏誅 + canon 動物war 群獸名錄）：
//   獸王摩雲既為這場動物war的獸王總頭目﹐牠麾下那群受邪念驅策的孽畜——白
//   猴、老虎、魔象、猴王、大鱷、母豬、吞風獅、老龍之屬——本聽其號令。摩雲
//   一死﹐群龍無首﹐這群孽畜便潰散在天靈山深處的幽壑獸塚之間。其中這頭蟄
//   伏獸塚的老龍﹐乃一條修煉了不知幾百年的孽蟒所化﹐通體覆著青黑的鱗甲﹐
//   雖未成真龍﹐其兇威已遠勝尋常山獸。牠盤踞獸塚枯骨之間﹐受那縷遁來的邪
//   念溫養﹐戾氣愈熾——卻終究只是摩雲的爪牙﹐戰力較那獸王總頭目低了一籌。
//
// 設計（underling-tier：較 lvl50 獸王摩雲低一檔的孽畜 boss）：
//   * level 42（摩雲 lvl50）﹔unarmed 135 / parry 125 / dodge 115 / force 130
//     （摩雲 unarmed180/parry160/dodge150/force170）——血厚力沉﹐然不及那獸王
//     總頭目﹐有相當火候的玩家方能克之。
//   * 三圍真氣 advance_stat gin/kee/sen 280/300/280（摩雲 360/400/360）。
//   * 孽蟒以軀體鱗爪搏殺﹐不持兵器（unarmed 主戰）。
//   * accept_fight 回傳 1——盤踞獸塚、奉陪到底﹐然不主動撲噬（無 aggressive
//     attitude﹐由玩家自行 kill 起釁﹔幽壑 youhe.c 設 no_fight 已把關委託在前）。
//
// 任務推進（die()）：
//   老龍伏誅時﹐若下手者(last_damage_giver)是身負序章旗標(quest/main_canon1
//   == 1)的真實玩家(userp)﹕把其 quest/main_canon1 推進為 2﹐並 message 一段
//   敘事（潰散殘部第一頭已除﹐邪念去向更明﹐指向北邊吞風獅穴）。防重複：旗
//   標非 1 則僅作尋常死亡、不推進。末了恒呼 ::die()（屍體/bounty 善後依之）。
//   另設 bounty（尋常戰鬥經驗）﹐由 ::die() 一併結算給下手者。

#include <npc.h>
#include <ansi.h>

inherit F_VILLAGER;

void create()
{
	set_name("老龍", ({ "old dragon", "laolong", "dragon" }) );
	set("nickname", "孽蟒");
	set_attr("str", 30);
	set_attr("dex", 27);
	set_attr("int", 18);
	set_attr("con", 31);
	set_attr("cor", 24);
	set_race("human");
	set_class("fighter");
	set("sect", "天靈山");
	set("rank", "孽蟒");

	// underling-tier：較摩雲(unarmed180/parry160/dodge150/force170)低一檔。
	set_skill("unarmed", 135);
	set_skill("parry", 125);
	set_skill("dodge", 115);
	set_skill("force", 130);

	// 真氣厚﹐然不及摩雲(gin/kee/sen 360/400/360)。
	advance_stat("gin", 280);
	advance_stat("kee", 300);
	advance_stat("sen", 280);

	set("gender", "male");
	set("age", 400);
	set("long",
		"一條盤踞在獸塚枯骨之間、修煉了不知幾百年的孽蟒所化的老\n"
		"龍。牠身軀長逾數丈﹐通體覆著青黑的厚鱗﹐鱗下隱隱透出化不\n"
		"開的戾氣﹐項下生著一圈倒豎的硬刺﹐頭頂兩道肉角初成﹐雖未\n"
		"化得真龍﹐那睥睨之態已自不凡。牠那雙豎瞳幽幽燃著青芒﹐昂\n"
		"首吐信之間﹐腥風撲面﹐枯骨為之簌簌震顫。自獸王摩雲伏誅、\n"
		"那縷邪念遁來這幽壑深處﹐這頭老龍便受其溫養﹐戾氣日熾——牠\n"
		"原是摩雲麾下為首的孽畜﹐如今群龍無首﹐反倒愈發兇悖難制。\n");
	set("chat_chance_combat", 3);
	set("chat_msg_combat", ({
		"老龍昂首一聲長嘶﹐項下硬刺盡張﹐青黑戾氣自鱗縫間暴湧而出。\n",
		"老龍巨軀一捲﹐挾著漫天枯骨橫掃而來﹐腥風所及﹐令人幾乎窒息。\n",
		"老龍豎瞳青芒大盛﹐張口噴出一道腥臭的黑霧﹐直撲人面門。\n",
	}));
	setup();

	// 尋常戰鬥經驗（由 ::die() 結算給下手者）。
	set("bounty", ([
		"survive"         : 420,
		"unarmed mastery" : 90,
		"martial art"     : 55,
		"martial mastery" : 40,
		"combat"          : 45,
	]));
}

// 盤踞獸塚、奉陪到底﹐然不主動撲噬。
int accept_fight(object ob)
{
	do_chat((: command, "say 老龍受了犯境者的驚擾﹐昂首發出一聲震得枯骨亂顫的怒嘶﹗" :));
	return 1;
}

// 死亡：序章「逐念入山」旗標推進(1->2) + 敘事﹐末了恒呼 ::die()。
void die()
{
	object killer;

	killer = last_damage_giver();

	// 下手者須為身負序章旗標(==1)的真實玩家﹐方推進旗標（防重複推進）。
	if( objectp(killer)
	&&	killer != this_object()
	&&	userp(killer)
	&&	killer->query("quest/main_canon1") == 1 )
	{
		killer->set("quest/main_canon1", 2);
		message_vision(
			HIR "老龍發出一聲淒厲的長嘶﹐數丈長的巨軀在枯骨間劇烈翻騰﹐"
			"終於頹然委地﹐青黑的鱗甲一片片黯淡下去。$N降伏了摩雲麾下這"
			"頭為首的孽蟒﹗\n" NOR, killer);
		message_vision(
			HIM "老龍氣絕之際﹐牠鱗甲間那縷受邪念溫養的戾氣嗤地散開﹐倏地"
			"凝成一線細若游絲的青黑﹐怨毒地往北面那座吞風獅穴的方向飄竄而"
			"去。你心頭一凜——摩雲麾下的孽畜雖已潰散﹐那縷牽動牠們的邪念﹐"
			"卻仍循著更深處的去路退竄。北邊那頭吞風獅﹐怕也是這殘部裡的一"
			"條硬骨頭。\n" NOR, killer);
	}

	// 屍體/bounty/善後悉依 std/char/npc.c::die()（恒呼，不可略）。
	::die();
}

// vim: set ts=4 sw=4 syntax=lpc
