// skeleton_king.c -- 骨屍妖王，正史主線第二章「混沌珠」幽冥骨殿(bonehall.c)中的
//                   首座 boss。把持混沌珠的兩大守護之一，以萬骨煉身。
//
// 故事背景（承接第一章 shoushan.c 之領賞伏筆 + abyss.c 石壁所載）：
//   第一章「逐念入山」末了﹐守山道人參出那縷牽動摩雲一脈的至邪之物「混沌珠」﹐
//   如今正落在天靈山更深處幽冥之中﹐由這頭「骨屍妖王」把持——牠以這滿山潰散
//   孽畜、與歷代葬身此山的枯骨煉成己身﹐萬骨為甲、千骸為軀﹐刀槍難入。另有
//   「鬼王噬魂」與牠互為表裡、佐之守珠。少俠既循那縷邪念深入幽冥﹐這以萬骨
//   煉身的妖王﹐便是奪回混沌珠須過的第一關。
//
// 設計（boss-tier：較第一章獸塚老龍(lvl42)、吞風獅(lvl38)遠強﹐略勝獸王摩雲
//      (lvl50)——萬骨煉身﹐血厚甲堅﹐是第二章須有備而來、武藝精純且持械方能克
//      的首座 boss）：
//   * level 47﹔unarmed 175 / parry 175 / dodge 150 / force 180（摩雲 unarmed180/
//     blade160/parry160/dodge150/force170）——以軀體萬骨搏殺、不持兵器(unarmed
//     主戰)﹐parry 奇高(萬骨為甲)﹐血力沉雄。
//   * 三圍真氣 advance_stat gin/kee/sen 380/440/380（摩雲 360/400/360）——萬骨
//     煉身﹐血(kee)尤厚。
//   * accept_fight 回傳 1——盤踞骨殿、奉陪到底、兇悍反擊﹐然不主動撲噬(無
//     aggressive attitude﹔玩家自行 kill 起釁。幽冥入口 nether.c 之 valid_leave
//     已就 quest/main_canon2 把關濾去未接任務的冒進者﹐此即安全閥)。
//
// 任務推進（die()）：
//   骨屍妖王伏誅時﹐若下手者(last_damage_giver)是身負第二章旗標(quest/main_canon2
//   == 1)的真實玩家(userp)﹕把其 quest/main_canon2 推進為 2（首座守護已破﹐路通
//   噬魂窟）﹐並 message 一段敘事（萬骨崩散﹐邪念退向更深的噬魂窟﹐指向鬼王噬魂）。
//   防重複：旗標非 1 則僅作尋常死亡、不推進。末了恒呼 ::die()（屍體/bounty 善後
//   依之）。另設 bounty(尋常戰鬥經驗)﹐由 ::die() 一併結算給下手者。
//
// 頂裝掉落（mirror moyun.c::drop_topgear）：骨屍妖王為第二章首座 boss﹐伏誅後有
//   SKKING_TOPGEAR_PCT 的機率自其屍身遺落一件「妖塔系列」頂裝神兵(doc 05「妖塔
//   系列：摩雲、混沌珠、斬龍斧、冶磺套、冥龍甲…」)。頂裝極稀﹐故走機率掉落而非
//   必掉﹔此鉤子於 ::die() 之後執行(屆時屍體已生成並登錄 query_temp("corpse"))﹐
//   將神兵直接置入屍體﹐玩家須 search/取屍 方得。

#include <npc.h>
#include <ansi.h>

inherit F_VILLAGER;

// 頂裝(top-tier gear)稀有掉落（mirror moyun.c）：骨屍妖王伏誅後有此機率遺落一件
// 妖塔系列頂裝。極稀——調此值即調稀有度。
#define SKKING_TOPGEAR_PCT   25      // 頂裝掉落機率(%)

private mixed *skking_topgear = ({   // 頂裝掉落池（隨機取一﹐doc 妖塔系列神兵）。
	"/obj/topgear/zhanlong_axe",     // 斬龍斧（twohanded axe，doc 妖塔系列）
	"/obj/topgear/xuanshuang_sword", // 玄霜劍（sword）
});

// 稀有頂裝掉落：擲骰中獎則自掉落池隨機 clone 一件神兵﹐置入妖王屍身。
// who = 下手者(真實玩家)﹔於 ::die() 之後呼叫﹐corpse 已存在於 temp("corpse")。
private void drop_topgear(object who)
{
	object corpse, loot;
	string file;

	if( !who ) return;
	if( random(100) >= SKKING_TOPGEAR_PCT ) return;     // 未中獎，無頂裝。

	file = skking_topgear[random(sizeof(skking_topgear))];
	loot = new(file);
	if( !objectp(loot) ) return;

	// 置入屍體﹔屍體不存則退置於房間地面（防萬一）。
	corpse = query_temp("corpse");
	if( !objectp(corpse) || !loot->move(corpse) )
		loot->move(environment());

	message_vision(
		HIY "骨屍妖王那座以萬骨堆疊而成的軀殼轟然崩塌之際﹐自那紛紛迸"
		"散的枯骨之間﹐竟『噹』地滾落一件寒光懾人的神兵——想是這妖王煉"
		"身之時﹐連這等沒入枯骨的連城之珍也一併煉進了牠這身萬骨甲胄﹗\n" NOR);
}

void create()
{
	set_name("骨屍妖王", ({ "skeleton king", "boneking", "king" }) );
	set("nickname", "萬骨妖王");
	set_attr("str", 33);
	set_attr("dex", 28);
	set_attr("int", 20);
	set_attr("wis", 20);
	set_attr("spi", 26);
	set_attr("con", 35);
	set_attr("cor", 26);
	set_race("human");
	set_level(47);
	set_class("fighter");
	set("sect", "幽冥");
	set("rank", "妖王");

	// boss-tier：以萬骨為甲(parry 奇高)、不持兵器(unarmed 主戰)。
	set_skill("unarmed", 175);
	set_skill("parry", 175);
	set_skill("dodge", 150);
	set_skill("force", 180);

	// 萬骨煉身﹐血(kee)尤厚——較摩雲(gin/kee/sen 360/400/360)再進一步。
	advance_stat("gin", 380);
	advance_stat("kee", 440);
	advance_stat("sen", 380);

	set("gender", "male");
	set("age", 600);
	set("long",
		"這便是把持混沌珠、以萬骨煉身的骨屍妖王。牠並無血肉之軀——\n"
		"通體是由不知多少枯骨層層堆疊、纏絞而成的一座骨塔﹕巨象的\n"
		"頭骨作冠﹐蟒蛇的椎節為脊﹐千百根人骨獸骨交錯成這一身嶙峋\n"
		"的甲胄﹐骨縫間滲著化不開的青黑屍火﹐幽幽明滅。牠那兩點眼\n"
		"窩裡燃著兩簇陰綠的鬼磷﹐俯視之間﹐自有一股自累累白骨中熬\n"
		"煉出的、亙古而陰寒的死寂。據那骨符鬼篆所載﹐這妖王守混沌\n"
		"珠於幽冥﹐以萬骨為甲、千骸為軀﹐尋常刀兵難入其身﹐又有那\n"
		"鬼王噬魂與牠互為表裡——奪那至邪之珠﹐須先過牠這一座骨山。\n");
	set("chat_chance_combat", 3);
	set("chat_msg_combat", ({
		"骨屍妖王周身骨節格格作響﹐千百根枯骨倏地刺出﹐挾著陰寒的屍火攢射而來。\n",
		"骨屍妖王眼窩中陰綠鬼磷大盛﹐一隻由無數指骨絞成的巨掌當頭抓落﹐腥風徹骨。\n",
		"骨屍妖王發出一陣自骨縫間擠出的、嘎嘎如夜梟的怪笑﹐那一身萬骨甲胄愈見森然。\n",
	}));
	setup();

	// 尋常戰鬥經驗（由 ::die() 結算給下手者）。
	set("bounty", ([
		"survive"         : 720,
		"unarmed mastery" : 130,
		"martial art"     : 70,
		"martial mastery" : 55,
		"combat"          : 60,
	]));
}

// 盤踞骨殿、奉陪到底﹐然不主動撲噬。
int accept_fight(object ob)
{
	do_chat((: command, "say 骨屍妖王眼窩中陰綠鬼磷驟然暴漲﹐周身萬骨格格亂顫﹐發出一陣嘎嘎的怪笑迎向犯境的來人﹗" :));
	return 1;
}

// 死亡：第二章「混沌珠」旗標推進(1->2) + 敘事﹐末了恒呼 ::die()﹐再擲頂裝入屍。
void die()
{
	object killer;

	killer = last_damage_giver();

	// 下手者須為身負第二章旗標(==1)的真實玩家﹐方推進旗標（防重複推進）。
	if( objectp(killer)
	&&	killer != this_object()
	&&	userp(killer)
	&&	killer->query("quest/main_canon2") == 1 )
	{
		killer->set("quest/main_canon2", 2);
		message_vision(
			HIR "骨屍妖王發出一聲不似人聲的厲嘯﹐那座以萬骨堆疊而成的巍"
			"峨軀殼自頂端開始崩解﹐千百根枯骨格格碎裂、紛紛迸散﹐眼窩中那"
			"兩簇陰綠的鬼磷也驟然熄滅。$N破了這以萬骨煉身的妖王﹐奪回混沌"
			"珠的第一道守護﹐至此算是破了﹗\n" NOR, killer);
		message_vision(
			HIM "骨屍妖王軀殼崩散之際﹐那盤桓於萬骨之間、化不開的青黑屍火"
			"並未隨之熄滅——反倒嗤地凝成一線怨毒的陰識﹐沿著骨殿更深處那道"
			"森然的黑暗甬道倒灌而去。你心頭一凜——這妖王不過是混沌珠的守護"
			"之一﹐那與牠互為表裡的『鬼王噬魂』﹐想必正盤踞在那甬道盡頭的"
			"噬魂窟裡﹐守著那顆至邪之珠。(往北 north 可深入噬魂窟)\n" NOR, killer);
	}

	// 屍體/bounty/善後悉依 std/char/npc.c::die()（恒呼﹐不可略）。
	// 須先呼 ::die()(屍體於此生成並登錄 temp("corpse"))﹐再擲頂裝掉落入屍。
	::die();

	// 頂裝(top-tier gear)稀有掉落（mirror moyun.c）：下手者須為真實玩家﹐機率置神兵入屍身。
	if( objectp(killer) && killer != this_object() && userp(killer) )
		drop_topgear(killer);
}

// vim: set ts=4 sw=4 syntax=lpc
