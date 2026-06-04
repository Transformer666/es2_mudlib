// soul_devourer.c -- 鬼王噬魂，正史主線第二章「混沌珠」幽冥噬魂窟(soulpit.c)中的
//                   次座(亦終座) boss。把持混沌珠的兩大守護之二﹐與骨屍妖王互為表裡。
//
// 故事背景（承接 skeleton_king.c 之後 + abyss.c 石壁「鬼王噬魂佐之，與之互為表
//   裡」所載）：
//   骨屍妖王以萬骨煉「身」﹐這鬼王噬魂則司其「魂」——牠本是幽冥中一縷亙古的厲
//   鬼﹐專噬生靈之魂魄以自肥﹐其形若有若無﹐縹緲難捉。牠與骨屍妖王一身(骨)一魂
//   (魄)、互為表裡﹐共守那顆聚天下戾氣為一的至邪之珠「混沌珠」。骨屍妖王既破﹐
//   這鬼王噬魂便是奪回混沌珠須過的最後一關——斬之﹐則那守珠的最後一道桎梏盡去﹐
//   混沌珠遂可奪。
//
// 設計（co-boss：較骨屍妖王(lvl47)略低半檔﹐然以縹緲詭譎見長——身手奇捷、傷魂攝
//      神﹐是第二章終座 boss）：
//   * level 45﹔unarmed 165 / parry 150 / dodge 180 / force 175（骨屍妖王 unarmed175/
//     parry175/dodge150/force180）——縹緲無形﹐dodge 奇高(難以命中)﹐然血甲略遜
//     於那以萬骨煉身的妖王。以魂體厲爪搏殺、不持兵器(unarmed 主戰)。
//   * 三圍真氣 advance_stat gin/kee/sen 400/400/420（骨屍妖王 380/440/380）——
//     司魂魄之鬼﹐神(sen)尤厚﹐血(kee)略遜於萬骨之軀。
//   * accept_fight 回傳 1——盤踞噬魂窟、奉陪到底﹐然不主動撲噬(無 aggressive
//     attitude﹔玩家自行 kill 起釁。骨殿 bonehall.c 之 valid_leave 已就 quest/
//     main_canon2 >= 2 把關﹐須先破骨屍妖王方得入此窟﹐此即安全閥)。
//
// 任務推進 + 混沌珠掉落（die()）：
//   鬼王噬魂伏誅時﹐若下手者(last_damage_giver)是身負第二章旗標(quest/main_canon2
//   == 2)的真實玩家(userp)﹕把其 quest/main_canon2 推進為 3（第二章「奪珠」之關隘
//   盡破——守珠兩大守護皆除）﹐並 message 一段敘事﹔旗標既達 3﹐混沌珠遂可奪——
//   遂 clone 混沌珠(npc/obj/chaos_pearl)置入噬魂屍身(mirror windlion.c 掉骨符之
//   corpse-drop 機制)﹐玩家須 search/取屍 方得。防重複：旗標非 2 則僅作尋常死亡、
//   不推進、不掉珠。末了恒呼 ::die()。另設 bounty﹐由 ::die() 結算給下手者。

#include <npc.h>
#include <ansi.h>

inherit F_VILLAGER;

// 掉落第二章交差信物：混沌珠。who=下手者(真實玩家)﹔於 ::die() 之後呼叫﹐corpse
// 已存在於 temp("corpse")。混沌珠置入屍身﹔屍體不存則退置房間地面（防萬一）。
private void drop_pearl(object who)
{
	object corpse, loot;

	if( !who ) return;

	loot = new(__DIR__"obj/chaos_pearl");
	if( !objectp(loot) ) return;

	corpse = query_temp("corpse");
	if( !objectp(corpse) || !loot->move(corpse) )
		loot->move(environment());

	message_vision(
		HIY "鬼王噬魂那縷縹緲的魂體潰散之際﹐自牠盤桓不去的陰冷氣息核心"
		"裡﹐倏地墜下一顆渾圓之物——只見那珠通體幽黑﹐其中無數猙獰的人面"
		"鬼影翻滾明滅、無聲嘶嚎。守珠的兩大守護皆已伏誅﹐這顆聚天下戾氣"
		"為一、至邪不祥的『混沌珠』﹐終於墜落在你的面前﹗\n" NOR);
}

void create()
{
	set_name("鬼王噬魂", ({ "soul devourer", "devourer", "ghost king" }) );
	set("nickname", "噬魂鬼王");
	set_attr("str", 30);
	set_attr("dex", 34);
	set_attr("int", 24);
	set_attr("wis", 24);
	set_attr("spi", 30);
	set_attr("con", 31);
	set_attr("cor", 28);
	set_race("human");
	set_level(45);
	set_class("fighter");
	set("sect", "幽冥");
	set("rank", "鬼王");

	// co-boss：縹緲無形(dodge 奇高)、傷魂攝神(force 高)，不持兵器(unarmed 主戰)。
	set_skill("unarmed", 165);
	set_skill("parry", 150);
	set_skill("dodge", 180);
	set_skill("force", 175);

	// 司魂魄之鬼﹐神(sen)尤厚﹐血(kee)略遜於骨屍妖王(gin/kee/sen 380/440/380)。
	advance_stat("gin", 400);
	advance_stat("kee", 400);
	advance_stat("sen", 420);

	set("gender", "male");
	set("age", 800);
	set("long",
		"這便是與骨屍妖王互為表裡、共守混沌珠的鬼王噬魂。牠並無實\n"
		"體——只是一團不住翻卷、縹緲如墨煙的幽暗魂氣﹐煙氣之中﹐無數\n"
		"被牠生前吞噬的魂魄化作一張張猙獰扭曲的人面﹐載沉載浮﹐無聲\n"
		"地開闔著嘴﹐似在永無休止地哀嚎。煙氣的核心處﹐勉強凝著一道\n"
		"頎長而模糊的人形輪廓﹐兩點幽藍的鬼火便是牠的雙目。據那骨符\n"
		"鬼篆所載﹐這鬼王專噬生靈魂魄以自肥﹐骨屍妖王煉其『身』、牠\n"
		"則司其『魂』﹐一身一魂、共鎮那顆至邪的混沌珠——骨屍妖王既\n"
		"破﹐斬了這鬼王﹐那守珠的最後一道桎梏﹐便算是盡去了。\n");
	set("chat_chance_combat", 3);
	set("chat_msg_combat", ({
		"鬼王噬魂周身那無數人面齊齊發出一聲無聲的哀嚎﹐一股攝人心魂的陰寒直撲識海。\n",
		"鬼王噬魂的魂體驟然散作漫天墨煙﹐自四面八方詭譎地絞捲而來﹐令人神魂俱顫。\n",
		"鬼王噬魂兩點幽藍鬼火大盛﹐一隻自煙氣中探出的魂手徑往人的天靈蓋攫來﹗\n",
	}));
	setup();

	// 尋常戰鬥經驗（由 ::die() 結算給下手者）。
	set("bounty", ([
		"survive"         : 680,
		"unarmed mastery" : 120,
		"martial art"     : 66,
		"martial mastery" : 52,
		"combat"          : 58,
	]));
}

// 盤踞噬魂窟、奉陪到底﹐然不主動撲噬。
int accept_fight(object ob)
{
	do_chat((: command, "say 鬼王噬魂周身那無數人面齊聲哀嚎﹐一團墨煙驟然絞向犯境的來人﹗" :));
	return 1;
}

// 死亡：第二章旗標推進(2->3，奪珠關隘盡破) + 敘事﹐末了恒呼 ::die()﹐再擲混沌珠入屍。
void die()
{
	object killer;

	killer = last_damage_giver();

	// 下手者須為身負第二章旗標(==2)的真實玩家﹐方推進旗標（防重複推進與重複掉珠）。
	if( objectp(killer)
	&&	killer != this_object()
	&&	userp(killer)
	&&	killer->query("quest/main_canon2") == 2 )
	{
		killer->set("quest/main_canon2", 3);
		message_vision(
			HIR "鬼王噬魂發出一聲撕裂識海的無聲悲嚎﹐那團縹緲的魂氣自核心"
			"處潰散開來﹐周身無數猙獰的人面一張張化作青煙消融﹐兩點幽藍的鬼"
			"火也終於黯滅。$N斬了這司魂攝魄的鬼王——守混沌珠的兩大守護﹐至此"
			"盡數伏誅了﹗\n" NOR, killer);
		message_vision(
			HIM "骨屍妖王煉其身、鬼王噬魂司其魂﹐這一身一魂的兩大守護既已盡"
			"除﹐那鎮鎖混沌珠的桎梏便隨之冰消。你只覺這噬魂窟中盤桓亙古的陰寒"
			"死寂﹐竟在這一瞬間鬆動、潰散——那顆聚天下戾氣為一的至邪之珠﹐再"
			"無人能為它遮掩了。\n" NOR, killer);
	}

	// 屍體/bounty/善後悉依 std/char/npc.c::die()（恒呼）。
	// 須先呼 ::die()(屍體於此生成並登錄 temp("corpse"))﹐再擲混沌珠入屍。
	::die();

	// 混沌珠掉落：下手者須為身負旗標(==2→已推進為3)的真實玩家﹐方掉珠入屍。
	if( objectp(killer) && killer != this_object() && userp(killer)
	&&	killer->query("quest/main_canon2") == 3 )
		drop_pearl(killer);
}

// vim: set ts=4 sw=4 syntax=lpc
