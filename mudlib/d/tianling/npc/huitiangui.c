// huitiangui.c -- 悔天鬼，正史主線第三章「悔天鬼」天靈絕巔(summit.c)上的決戰魔頭，
//                亦是整條「動物war」大弧的終 boss(司獸亂之源)。
//
// 故事背景（承接序章 shoushan.c → 第一章(老龍/吞風獅) → 第二章(骨屍妖王/鬼王噬魂、
//   奪回混沌珠) 一脈而下；並承 abyss.c/soulpit.c 鬼篆、shrinekeeper.c/diviner.c
//   等序章框架所立之設定）：
//   三百年前﹐天靈山那株鎮著天地的聖木被人斫斷﹐自其封印之下放出了一縷亙古的至
//   邪邪念——這縷邪念的本體﹐便是這頭盤踞天靈絕巔、雲遮霧繞之巔的「悔天鬼」。牠
//   是這滿山獸亂真正的源頭﹕受牠牽動﹐獸王摩雲懾百獸而興獸亂﹔奉牠之命﹐骨屍妖
//   王與鬼王噬魂下幽冥共守那聚天下戾氣為一的「混沌珠」。摩雲也好、骨屍妖王也罷﹐
//   皆不過是這悔天鬼驅策的爪牙。少俠循那縷邪念一路追兇——破摩雲、掃殘部、奪混沌
//   珠——如今守山道人已借京畿神社聖木餘力、會同那奪回的混沌珠﹐煉成一方「淨邪鎮
//   魂印」交在少俠手中﹔少俠持此聖印登上天靈絕巔﹐了結這頭悔天鬼﹐這場綿延三百
//   年的獸亂﹐方能真個平息。
//
// 設計（arc 終 boss：全弧最強——較第二章骨屍妖王(lvl47)、鬼王噬魂(lvl45)、獸王
//      摩雲(lvl50)俱更上一檔﹐司獸亂之源、三百年邪念所凝）：
//   * level 52（摩雲 lvl50、骨屍妖王 lvl47、鬼王噬魂 lvl45）——arc 之最。
//   * unarmed 195 / parry 185 / dodge 180 / force 200（骨屍妖王 unarmed175/parry175/
//     dodge150/force180；鬼王噬魂 unarmed165/parry150/dodge180/force175）——身手、
//     血甲、內力俱凌駕兩守護之上。以邪念所凝之厲爪搏殺、不持兵器(unarmed 主戰)。
//   * 三圍真氣 advance_stat gin/kee/sen 460/480/500（骨屍妖王 380/440/380、鬼王噬
//     魂 400/400/420）——三百年邪念所凝﹐神(sen)尤其深厚﹐血(kee)亦冠絕全弧。
//   * accept_fight 回傳 1——盤踞絕巔、奉陪到底﹐然不主動撲噬(無 aggressive
//     attitude﹔玩家自行 kill 起釁。絕巔之路 cleft→summit 沿途 valid_leave 已就
//     quest/main_canon3 與隨身淨邪鎮魂印把關﹐濾去未接任務、無聖印護持者﹐此即
//     安全閥)。
//   * 戰鬥引擎層面之 boss 特技(分相/特殊攻擊)逾本檔範疇——以「一頭數值凌駕全弧的
//     強力高階 NPC」呈現即可﹐不另造戰鬥 efun(鏡 moyun/skeleton_king/soul_devourer
//     之做法)。
//
// 任務推進 + 終 boss 信物掉落（die()）：
//   悔天鬼伏誅時﹐若下手者(last_damage_giver)是身負第三章旗標(quest/main_canon3
//   == 1)的真實玩家(userp)﹕把其 quest/main_canon3 推進為 2（獸亂之源已誅——arc
//   高潮完成）﹐並 message 一段高潮敘事（三百年邪念潰散、獸亂平息）。防重複：旗
//   標非 1 則僅作尋常死亡、不推進、不掉信物。末了恒呼 ::die()（屍體/bounty 善後
//   依之）﹐再擲交差信物「悔天鬼殘魄」(npc/obj/sky_ghost_relic)入屍身——玩家持此
//   殘魄回守山道人處交差(give_reward3)。另設 bounty﹐由 ::die() 結算給下手者。
//
// 頂裝掉落（mirror moyun.c / skeleton_king.c::drop_topgear）：悔天鬼為 arc 終 boss﹐
//   伏誅後另有 HTG_TOPGEAR_PCT 的機率自其屍身遺落一件「妖塔系列」頂裝神兵(doc 05
//   妖塔系列：摩雲、混沌珠、斬龍斧、冶磺套、冥龍甲…)。頂裝極稀﹐故走機率掉落而非
//   必掉(交差信物則必掉)﹔此鉤於 ::die() 之後執行(屆時屍體已生成並登錄 query_temp
//   ("corpse"))﹐將神兵直接置入屍體﹐玩家須 search/取屍 方得。

#include <npc.h>
#include <ansi.h>

inherit F_VILLAGER;

// 頂裝(top-tier gear)稀有掉落（mirror moyun/skeleton_king）：悔天鬼伏誅後有此機率
// 遺落一件妖塔系列頂裝。極稀——調此值即調稀有度。
#define HTG_TOPGEAR_PCT   30      // 頂裝掉落機率(%)

private mixed *htg_topgear = ({   // 頂裝掉落池（隨機取一﹐doc 妖塔系列神兵）。
	"/obj/topgear/zhanlong_axe",     // 斬龍斧（twohanded axe，doc 妖塔系列）
	"/obj/topgear/xuanshuang_sword", // 玄霜劍（sword）
});

// 掉落第三章交差信物：悔天鬼殘魄。who=下手者(真實玩家)﹔於 ::die() 之後呼叫﹐corpse
// 已存在於 temp("corpse")。殘魄置入屍身﹔屍體不存則退置房間地面（防萬一）。
private void drop_relic(object who)
{
	object corpse, loot;

	if( !who ) return;

	loot = new(__DIR__"obj/sky_ghost_relic");
	if( !objectp(loot) ) return;

	corpse = query_temp("corpse");
	if( !objectp(corpse) || !loot->move(corpse) )
		loot->move(environment());

	message_vision(
		HIY "悔天鬼那團龐然的青黑邪念潰散殆盡之際﹐自牠魂氣最核心處﹐倏地"
		"墜下一縷凝而不散、幽幽搏動的殘魄——那是這三百年邪念之主最後一絲未"
		"消的存念。守山道人言道﹐此殘魄須帶回交與他﹐方能借京畿神社聖木餘"
		"力﹐將這獸亂之源徹底封鎮、永絕後患。\n" NOR);
}

// 稀有頂裝掉落：擲骰中獎則自掉落池隨機 clone 一件神兵﹐置入悔天鬼屍身。
// who = 下手者(真實玩家)﹔於 ::die() 之後呼叫﹐corpse 已存在於 temp("corpse")。
private void drop_topgear(object who)
{
	object corpse, loot;
	string file;

	if( !who ) return;
	if( random(100) >= HTG_TOPGEAR_PCT ) return;     // 未中獎，無頂裝。

	file = htg_topgear[random(sizeof(htg_topgear))];
	loot = new(file);
	if( !objectp(loot) ) return;

	// 置入屍體﹔屍體不存則退置於房間地面（防萬一）。
	corpse = query_temp("corpse");
	if( !objectp(corpse) || !loot->move(corpse) )
		loot->move(environment());

	message_vision(
		HIY "悔天鬼魂氣潰散、青黑邪念紛紛迸落之際﹐自那翻卷的邪氣深處﹐竟"
		"『噹』地滾落一件寒光懾人的神兵——想是這三百年的至邪之主﹐連這等沒"
		"入邪念的連城之珍﹐也一併煉進了牠這一身邪氣之中﹗\n" NOR);
}

void create()
{
	set_name("悔天鬼", ({ "huitiangui", "sky ghost", "ghost" }) );
	set("nickname", "獸亂之源");
	set_attr("str", 35);
	set_attr("dex", 35);
	set_attr("int", 28);
	set_attr("wis", 26);
	set_attr("spi", 34);
	set_attr("con", 36);
	set_attr("cor", 32);
	set_race("human");
	set_level(52);
	set_class("fighter");
	set("sect", "天靈山");
	set("rank", "獸亂之源");

	// arc 終 boss：身手、血甲、內力俱凌駕第二章兩守護(骨屍妖王 175/175/150/180、
	// 鬼王噬魂 165/150/180/175)與獸王摩雲(180/160/160/150/170)之上。
	set_skill("unarmed", 195);
	set_skill("parry", 185);
	set_skill("dodge", 180);
	set_skill("force", 200);

	// 三百年邪念所凝：血(kee)、神(sen)俱冠絕全弧——較骨屍妖王(gin/kee/sen 380/440/
	// 380)、鬼王噬魂(400/400/420)再上一檔。
	advance_stat("gin", 460);
	advance_stat("kee", 480);
	advance_stat("sen", 500);

	set("gender", "male");
	set("age", 300);
	set("long",
		"這便是盤踞天靈絕巔、司這滿山獸亂之源的悔天鬼了。牠並非血\n"
		"肉之軀——只是一團龐然如山、不住翻卷的青黑邪念所凝。那邪念\n"
		"濃稠如墨、幽深莫測﹐勉強凝出一道頂天立地的魁偉人形﹐周身\n"
		"卻又時時崩散作漫天戾氣、復又收攏﹐縹緲而沉雄。牠那一張面\n"
		"孔似哭似笑、似悔似怨﹐五官在那團邪氣中扭曲明滅﹐永無定\n"
		"形﹔兩點深陷的眼眶裡﹐燃著兩簇亙古不熄的幽暗鬼火﹐俯視之\n"
		"間﹐三百年的怨毒、不甘與滔天的戾氣盡數壓下﹐教人魂魄俱\n"
		"顫。三百年前那株鎮天聖木被斫斷﹐自封印下放出的﹐便是這縷\n"
		"邪念——獸王摩雲受牠牽動而興獸亂﹐骨屍妖王、鬼王噬魂奉牠之\n"
		"命而守混沌珠。牠﹐才是這整場獸亂真正的源頭與終結。\n");
	set("chat_chance_combat", 4);
	set("chat_msg_combat", ({
		"悔天鬼那似哭似笑的面孔驟然扭曲﹐周身青黑邪念暴漲如潮﹐挾著三百年的怨毒當頭壓落﹗\n",
		"悔天鬼魁偉的身形倏地崩散作漫天戾氣﹐自四面八方詭譎地絞捲而來﹐令人神魂俱裂。\n",
		"悔天鬼兩簇幽暗鬼火大盛﹐一隻由純粹邪念凝成的巨爪自雲霧中探出﹐徑往人的識海攫來﹗\n",
		"悔天鬼發出一聲似悔似怨、響徹絕巔的長嘯﹐滿山雲霧為之翻湧倒捲﹐天地一時失色。\n",
	}));
	setup();

	// 尋常戰鬥經驗（由 ::die() 結算給下手者）——arc 終 boss﹐較兩守護更厚。
	set("bounty", ([
		"survive"         : 880,
		"unarmed mastery" : 150,
		"martial art"     : 80,
		"martial mastery" : 64,
		"combat"          : 70,
	]));
}

// 盤踞絕巔、奉陪到底﹐然不主動撲噬。
int accept_fight(object ob)
{
	do_chat((: command, "say 悔天鬼那似哭似笑的面孔在邪氣中緩緩轉來﹐周身三百年的戾氣驟然暴漲﹐迎向這膽敢登巔的來人﹗" :));
	return 1;
}

// 死亡：第三章旗標推進(1->2，獸亂之源已誅) + 高潮敘事﹐末了恒呼 ::die()﹐再擲交差
// 信物入屍、機率擲頂裝入屍。
void die()
{
	object killer;

	killer = last_damage_giver();

	// 下手者須為身負第三章旗標(==1)的真實玩家﹐方推進旗標（防重複推進與重複掉信物）。
	if( objectp(killer)
	&&	killer != this_object()
	&&	userp(killer)
	&&	killer->query("quest/main_canon3") == 1 )
	{
		killer->set("quest/main_canon3", 2);
		message_vision(
			HIR "悔天鬼發出一聲撕裂天地、響徹九霄的悲嘯——那似悔似怨的面孔在"
			"剎那間扭曲、潰散﹐那團盤踞絕巔三百年的龐然邪念自核心處轟然炸裂開"
			"來﹐青黑的戾氣如墨潮般四下迸散﹐兩簇亙古不熄的鬼火﹐也終於在這一"
			"刻黯然熄滅。$N持淨邪鎮魂印﹐了結了這頭司獸亂之源的悔天鬼﹗\n" NOR,
			killer);
		message_vision(
			HIM "悔天鬼一死﹐那縷牽動了三百年的至邪邪念霎時失了依憑——你只覺這"
			"終年雲遮霧繞的天靈絕巔﹐霧靄竟在這一瞬間自四面八方潰散開來﹐一線久"
			"違的天光自雲隙間直射而下﹐灑在這絕巔之上。獸王摩雲、骨屍妖王、鬼王"
			"噬魂——那一連串的爪牙與守護﹐其根本至此盡除。這場綿延三百年、害得滿"
			"山百獸發狂、生靈塗炭的獸亂﹐終於……平息了。\n" NOR, killer);
	}

	// 屍體/bounty/善後悉依 std/char/npc.c::die()（恒呼，不可略）。
	// 須先呼 ::die()(屍體於此生成並登錄 temp("corpse"))﹐再擲信物/頂裝入屍。
	::die();

	// 交差信物掉落：下手者須為身負旗標(==1→已推進為2)的真實玩家﹐方掉殘魄入屍(必掉)。
	if( objectp(killer) && killer != this_object() && userp(killer)
	&&	killer->query("quest/main_canon3") == 2 )
		drop_relic(killer);

	// 頂裝(top-tier gear)稀有掉落（mirror moyun/skeleton_king）：下手者須為真實玩家﹐
	// 機率置神兵入屍身(極稀)。
	if( objectp(killer) && killer != this_object() && userp(killer) )
		drop_topgear(killer);
}

// vim: set ts=4 sw=4 syntax=lpc
