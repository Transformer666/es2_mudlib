// giant_centipede.c -- 巨蜈，正史主線第四章「蜈蚣war」京畿地脈蜈穴(d/capital/wuxue.c)
//                      中的決戰魔頭——那盤蟠京畿地脈、蝕聖木之節以自肥的孽畜。
//
// 故事背景（承接第三章 summit.c 絕巔古碑所揭 + sanctifier 守木尊者第四章委託）：
//   三百年前那株鎮天地的聖木被斷、放出悔天鬼邪念——然斷聖木者﹐並非悔天鬼一鬼﹐
//   實為其下這條盤蟠京畿地脈的巨蜈。牠借蝕聖木之節、攫食地脈靈氣以自肥﹐三百年
//   來愈長愈巨﹐節節甲殼堅逾玄鐵﹐百足摩地如萬鼓齊鳴。悔天鬼的邪念﹐不過是這巨
//   蜈蝕節時溢出地表的餘毒。少俠持守木一脈密藏的聖劍『穿靈』降入京畿地脈﹐斫斷
//   那為巨蜈所蝕的聖木殘節(saintwood_node.c)、斷其借以自肥的地脈之養——斷節之痛
//   驚動了這蝕節盤踞的巨蜈﹐牠遂自殘根深處的蜈穴竄出迎敵。了結這條巨蜈﹐這蝕聖
//   木、亂地脈的禍根﹐方算真個斷絕。
//
// 設計（arc-boss：強悍高階 NPC﹐略遜第三章終 boss 悔天鬼(lvl52)、與獸王摩雲
//      (lvl50)相當之檔）：
//   * level 49（悔天鬼 52、摩雲 50、骨屍妖王 47）。
//   * blade 185 / parry 180 / dodge 170 / force 185（以百足、巨螯、毒牙搏殺﹐
//     設 blade 主戰﹐另 carry 毒螯為兵器）。
//   * 三圍真氣 advance_stat gin/kee/sen 430/470/420（三百年蝕聖木自肥﹐血(kee)厚
//     甲堅﹐略遜悔天鬼 460/480/500）。
//   * accept_fight 回傳 1——盤踞蜈穴、奉陪到底﹐然不主動撲噬(無 aggressive
//     attitude﹔玩家斫斷三節驚動之、自行 kill 起釁。蜈穴之門禁已於聖木殘節密室
//     saintroot.c::valid_leave 就 quest/main_canon4 >= 2 把關﹐濾去未斫斷聖木節
//     者﹐此即安全閥)。
//   * 戰鬥引擎層面之 boss 特技逾本檔範疇——以「一頭數值強悍的高階 NPC」呈現即可，
//     不另造戰鬥 efun(鏡 moyun/huitiangui 之做法)。
//
// 任務推進 + boss 信物掉落（die()）：
//   巨蜈伏誅時﹐若下手者(last_damage_giver)是身負第四章旗標(quest/main_canon4
//   == 2)的真實玩家(userp)﹕把其 quest/main_canon4 推進為 3（蝕聖木之巨蜈已誅——
//   arc 高潮完成）﹐並 message 一段高潮敘事。防重複：旗標非 2 則僅作尋常死亡、不
//   推進、不掉信物。末了恒呼 ::die()（屍體/bounty 善後依之）﹐再擲交差信物「聖木
//   殘根」+「破碎的印記」入屍身——玩家持此二物回守木尊者處交差(give_reward)。

#include <npc.h>
#include <ansi.h>

inherit F_VILLAGER;

// 掉落第四章交差信物：聖木殘根 + 破碎的印記。who=下手者(真實玩家)﹔於 ::die() 之
// 後呼叫﹐corpse 已存在於 temp("corpse")。二物置入屍身﹔屍體不存則退置房間地面。
private void drop_loot(object who)
{
	object corpse, root, seal;

	if( !who ) return;

	corpse = query_temp("corpse");

	root = new(__DIR__"obj/saintwood_root");
	if( objectp(root) && (!objectp(corpse) || !root->move(corpse)) )
		root->move(environment());

	seal = new(__DIR__"obj/broken_seal");
	if( objectp(seal) && (!objectp(corpse) || !seal->move(corpse)) )
		seal->move(environment());

	message_vision(
		HIY "巨蜈那盤蟠如山的龐然軀節在一陣劇烈的抽搐後終於癱軟僵直﹐自牠"
		"蜷曲的腹節之間﹐『骨碌碌』滾落兩件物事——一截為牠啃噬經年、猶帶齒痕"
		"涎毒的聖木殘根﹐與一枚自牠腹中翻出、殘破黯淡的古印。守木尊者言道﹕"
		"這殘根須帶回淨室溫養復甦﹐這枚破碎的印記﹐他日另有大用——快將二物拾"
		"了﹐帶回京畿神社去罷。\n" NOR);
}

void create()
{
	set_name("巨蜈", ({ "giant centipede", "centipede", "wugong" }) );
	set("nickname", "蝕木孽蜈");
	set_attr("str", 34);
	set_attr("dex", 33);
	set_attr("int", 20);
	set_attr("wis", 20);
	set_attr("spi", 26);
	set_attr("con", 35);
	set_attr("cor", 30);
	set_race("human");
	set_level(49);
	set_class("fighter");
	set("sect", "京畿地脈");
	set("rank", "蝕木孽蜈");

	// arc-boss：身手、甲堅略遜悔天鬼(unarmed195/parry185/dodge180/force200)﹐與摩雲
	// (unarmed180/blade160/parry160/dodge150/force170)同檔而更上。以巨螯毒牙搏殺。
	set_skill("blade", 185);
	set_skill("parry", 180);
	set_skill("dodge", 170);
	set_skill("force", 185);

	// 三百年蝕聖木自肥：血(kee)厚甲堅﹐略遜悔天鬼(gin/kee/sen 460/480/500)。
	advance_stat("gin", 430);
	advance_stat("kee", 470);
	advance_stat("sen", 420);

	set("gender", "male");
	set("age", 300);
	set("long",
		"這便是那盤蟠京畿地脈、蝕聖木之節以自肥的巨蜈了。牠那節節\n"
		"相連的龐然軀體足有數丈來長﹐通體覆著一層青黑泛玄、堅逾玄鐵\n"
		"的甲殼﹐甲縫間滲著灼亮黏稠的涎毒﹐所過之處岩石為之蝕出深深\n"
		"的溝痕。脊背兩側﹐數百隻鉤狀的爪足密密麻麻、無一刻安歇地翕\n"
		"動著﹐摩地之聲如萬鼓齊鳴﹐教人頭皮發麻。牠那扁平的巨首之上﹐\n"
		"一對彎月般的毒螯不住開闔﹐螯間一張森然的口器內﹐毒牙交錯、\n"
		"涎水長流。三百年來﹐牠便是借著纏蝕那株聖木深蟠地脈的殘節、\n"
		"攫食其根脈所鍾的清正靈氣﹐愈長愈巨、愈蝕愈兇——斷京畿聖木、\n"
		"致那悔天鬼邪念外溢於天靈山的真兇﹐正是這條盤蟠地底的孽蜈。\n"
		"牠才是這蝕木亂脈之禍真正的根源。\n");
	set("chat_chance_combat", 4);
	set("chat_msg_combat", ({
		"巨蜈龐然的軀節驟然高高昂起﹐數百隻鉤爪挾著腥膻的勁風當頭罩落﹗\n",
		"巨蜈一對彎月毒螯霍然張開﹐螯尖噴出一蓬灼亮的涎毒﹐所沾之處滋滋作響﹗\n",
		"巨蜈節節軀體倏地盤捲收緊﹐如一條玄鐵巨索﹐挾著千鈞之力絞捲而來﹗\n",
		"巨蜈扁平的巨首低俯﹐毒牙交錯的口器森然張開﹐徑往人的咽喉狠噬而下﹗\n",
	}));
	setup();
	carry_object("/obj/area/obj/blade")->wield();

	// 尋常戰鬥經驗（由 ::die() 結算給下手者）——arc-boss﹐厚於尋常。
	set("bounty", ([
		"survive"      : 850,
		"blade mastery": 140,
		"martial art"  : 78,
		"combat"       : 68,
		"reputation"   : 60,
	]));
}

// 盤踞蜈穴、奉陪到底﹐然不主動撲噬（入穴前聖木殘節密室 valid_leave 已把關）。
int accept_fight(object ob)
{
	do_chat((: command, "say 巨蜈龐然的軀節自蜈穴深處轟然撞出﹐數百隻鉤爪摩地如萬鼓齊鳴﹐毒螯霍張﹐迎向這膽敢斷牠地脈之養的來人﹗" :));
	return 1;
}

// 死亡：第四章旗標推進(2->3，蝕聖木之巨蜈已誅) + 高潮敘事﹐末了恒呼 ::die()﹐再
// 擲交差信物（聖木殘根 + 破碎的印記）入屍。
void die()
{
	object killer;

	killer = last_damage_giver();

	// 下手者須為身負第四章旗標(==2)的真實玩家﹐方推進旗標（防重複推進與重複掉信物）。
	if( objectp(killer)
	&&	killer != this_object()
	&&	userp(killer)
	&&	killer->query("quest/main_canon4") == 2 )
	{
		killer->set("quest/main_canon4", 3);
		message_vision(
			HIR "巨蜈發出一聲尖利刺耳、響徹地脈的悲嘶——那盤蟠數丈的龐然軀節"
			"猛地拱起、劇烈翻滾﹐數百隻鉤爪痙攣著胡亂抓撓﹐末了重重砸落、僵"
			"直癱軟於蜈穴的污泥之中。那對彎月毒螯無力地垂下﹐甲縫間的涎毒漸"
			"漸黯淡了下去。$N持聖劍穿靈﹐了結了這條蝕聖木、亂地脈三百年的巨"
			"蜈﹗\n" NOR, killer);
		message_vision(
			HIM "巨蜈一死﹐那纏蝕京畿地脈的滔天孽力霎時潰散——你只覺腳下這條"
			"深嵌地底的地脈﹐竟自四面八方傳來一陣如釋重負的悠長震顫﹐被那孽蜈"
			"蝕得將枯的聖木殘節﹐斷口處的青芒竟一分一分地重新明亮了起來。斷京"
			"畿聖木、致悔天鬼邪念外溢的禍根﹐至此終於斷絕。守山道人與守木尊者"
			"所憂心的這場蜈蚣之患﹐了了。\n" NOR, killer);
	}

	// 屍體/bounty/善後悉依 std/char/npc.c::die()（恒呼，不可略）。
	// 須先呼 ::die()(屍體於此生成並登錄 temp("corpse"))﹐再擲信物入屍。
	::die();

	// 交差信物掉落：下手者須為身負旗標(==2→已推進為3)的真實玩家﹐方掉二物入屍(必掉)。
	if( objectp(killer) && killer != this_object() && userp(killer)
	&&	killer->query("quest/main_canon4") == 3 )
		drop_loot(killer);
}

// vim: set ts=4 sw=4 syntax=lpc
