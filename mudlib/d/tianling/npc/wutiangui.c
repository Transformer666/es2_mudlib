// wutiangui.c -- 侮天鬼，正史主線第十一章「最終決戰」、亦即天朝帝國主線終點的最終 boss。
//
// 故事背景（承接第十章人靈魂泉重凝大成 renling.c/soulwell.c，並 docs 05 主線終局）：
//   遠在天地未判、神魔未分的洪荒之初，便有這麼一頭吞噬人界、與天神對賭蒼生氣運的至邪
//   巨擘——侮天鬼。牠以「侮天」為名，謂天道不仁、神不足侍，遂興兵噬界、欲吞盡這天朝帝國
//   億兆生靈的魂魄氣運，以證那「天可侮」之狂言。五千年前，上古聖者「寒於氏」捨身入此天靈
//   絕巔最深的幽窟，與牠賭命相搏，終以一身道力斬下牠這顆元神之首、將牠封鎮於此——然寒於氏
//   亦因此道消身殞，只餘一縷遺志、一脈遺澤，世代守候著重啟封印的有緣人。
//
//   五千年封印將盡，那盤桓三百年、應劫而生的「十三靈」——正是侮天鬼當年潰散的十三道厲魂所
//   凝、亦是牠重聚元神、掙脫封印的關竅。少俠歷九章、集日月星三光、於人靈魂泉重凝大成，再
//   一一了結這十三靈（quest/canon11_ling 0→13、滿則 quest/main_canon11=1，幽窟東向洞開），
//   方得入這天靈絕巔最深的幽窟，續寒於氏五千年前那未竟之戰、再封侮天鬼於永劫——此乃天朝
//   帝國主線之終點。
//
// 房間拓樸（本 NPC 由 wugui_lair.c 室生成；入場已被把關）：
//   人靈魂泉 soulwell --north--> 十三靈殿 lingdian --east--> 侮天鬼幽窟 wugui_lair
//   lingdian 室之 east 向（通幽窟）須 quest/main_canon11>=1（十三靈盡滅）方開——此即安全閥，
//   故本 boss 毋須自行把關入場資格。
//
// 設計（final-boss tier：天靈絕巔現存最強者為悔天鬼 lvl52、unarmed195/force200、gin/kee/sen
//   460/480/500——本 boss 為主線終局至邪元神，須全面壓過之，是少俠重凝大成、了結十三靈後須
//   傾盡全力方克的終局之敵；強而非無敵：高 attr/skill/hp，仍可被斬）：
//   * level 60；unarmed 235 / parry 225 / dodge 215 / force 240（悔天鬼 195/185/180/200）。
//   * 三圍真氣 advance_stat gin/kee/sen 560/600/620（悔天鬼 460/480/500）——五千年封印所養
//     的至邪元神，血(kee)、神(sen)俱沉雄。
//   * 高 attr：str/dex/con 皆 38、spi 40——元神之首所凝，神思(spi)尤盛。
//   * attitude=aggressive：最終決戰，主動撲噬入窟之人（attack.c::init switch attitude
//     "aggressive" → COMBAT_D->auto_fight；入場資格已由 lingdian east-gate 把關，故主動攻擊
//     安全無虞）。仍設 accept_fight 回傳 1，奉陪到底。
//
// 任務推進與終局（die()，務必循 lesson #10 destruct-LAST）：
//   旗標/計數/訊息/掉落邏輯一律寫在 ::die() 之前；獎勵落屍身寫在 ::die() 之後（屍身已生成、
//   登錄於 query_temp("corpse")）。
//   killer = last_damage_giver();
//   if( objectp(killer) && killer != this_object() && userp(killer)
//   &&  killer->query("quest/main_canon11") >= 1 ) {           // 十三靈已盡滅、有資格的決戰者
//       killer->set("quest/main_canon11_done", 1);             // → 主線終點
//       盛大終局 message_vision（侮天鬼元神再封、寒於氏遺志得償、天朝蒼生得救、主線終點）；
//   }
//   ::die();                                                   // 屍身於此生成（恒呼，不可略）
//   // ::die() 之後：終局獎勵「寒於氏遺澤」new() 後落入屍身（__DIR__ 已含 npc/ 結尾，
//   //   故獎勵路徑為 __DIR__"obj/hanyu_legacy"）。
//
// 不可 replace_program（本 NPC 有 die()/accept_fight 等自訂函式；lesson #11）。

#include <npc.h>
#include <ansi.h>

inherit F_VILLAGER;

private void drop_legacy(object who);

void create()
{
	set_name(HIR "侮天鬼" NOR, ({ "wutiangui", "sky insulter", "demon" }) );
	set("nickname", "侮天鬼");
	set_attr("str", 38);
	set_attr("dex", 38);
	set_attr("int", 30);
	set_attr("wis", 28);
	set_attr("spi", 40);
	set_attr("con", 38);
	set_attr("cor", 36);
	set_race("human");
	set_level(60);
	set_class("fighter");
	set("sect", "侮天");
	set("rank", "魔君");

	// final-boss tier：全面壓過悔天鬼(195/185/180/200)——元神之首、五千年封印所養。
	set_skill("unarmed", 235);
	set_skill("parry", 225);
	set_skill("dodge", 215);
	set_skill("force", 240);

	// 五千年封印所養的至邪元神，血(kee)、神(sen)俱沉雄——全面壓過悔天鬼(460/480/500)。
	advance_stat("gin", 560);
	advance_stat("kee", 600);
	advance_stat("sen", 620);

	set("gender", "male");
	set("age", 5000);
	set("long",
		HIR
		"幽窟最深處盤踞著的，便是那洪荒之初便已存世、自號『天可\n"
		"侮』的至邪巨擘——侮天鬼。牠被寒於氏斬去元神之首、封鎮於此已\n"
		"五千年，如今封印將盡，那顆失而復聚的猙獰鬼首重又懸於頸上，\n"
		"兩點瞳孔深處燒著兩團吞噬日月的幽冥之火。牠周身丈餘，皮肉如\n"
		"鑄鐵般青黑，遍體盤著一道道五千年來掙不脫的封印鎖鏈，每一寸\n"
		"肌理間都翻湧著億兆被牠吞噬的生靈魂魄所凝的怨煞之氣。牠俯視\n"
		"著闖入這幽窟的螻蟻，喉間滾出一陣亙古而來的譏笑——彷彿天地未\n"
		"判時牠便如此譏笑著那不仁的天道、那不足侍的眾神。這便是寒於\n"
		"氏五千年前捨身相搏、未竟其功的那一場終局之戰的對手了。\n"
		NOR);
	set("chat_chance_combat", 4);
	set("chat_msg_combat", ({
		HIR "侮天鬼喉間滾出一陣譏笑：『天道不仁、神不足侍——五千年了，又一個替天行道的蠢物？』\n" NOR,
		HIR "侮天鬼周身那億兆怨魂凝成的煞氣轟然炸開，一隻青黑如鑄鐵的巨掌挾著吞天之勢當頭拍落！\n" NOR,
		HIR "侮天鬼頸上鬼首雙瞳幽火大盛，五千年封印鎖鏈寸寸繃裂——『寒於氏斬不盡我，你又算甚麼東西！』\n" NOR,
		HIR "侮天鬼仰天長嘯，幽窟為之震顫，那億兆未散的人魂在牠周身載沉載浮、無聲哀嚎。\n" NOR,
	}));
	setup();

	// 最終決戰：主動撲噬入窟之人（入場資格已由 lingdian east-gate 把關）。
	set("attitude", "aggressive");

	// 終局戰鬥經驗（由 ::die() 結算給下手者）——主線終局之敵，賞格冠絕全章。
	set("bounty", ([
		"survive"         : 1200,
		"unarmed mastery" : 220,
		"martial art"     : 120,
		"martial mastery" : 95,
		"combat"          : 100,
	]));
}

// 盤踞幽窟、奉陪到底（attitude=aggressive 已令其主動撲噬；此為玩家若先行 kill 時之回應）。
int accept_fight(object ob)
{
	do_chat((: command, "say 侮天鬼喉間滾出一陣亙古的譏笑，億兆怨魂凝成的煞氣轟然絞向這替天行道的螻蟻！" :));
	return 1;
}

// 死亡：第十一章主線終點。循 lesson #10 destruct-LAST——
//   旗標/訊息一律寫在 ::die() 之前；終局獎勵落屍身寫在 ::die() 之後（屍身屆時方生成）。
void die()
{
	object killer;

	killer = last_damage_giver();

	// 下手者須為十三靈已盡滅(quest/main_canon11>=1)的真實玩家，方推進至主線終點（防誤判）。
	if( objectp(killer)
	&&	killer != this_object()
	&&	userp(killer)
	&&	killer->query("quest/main_canon11") >= 1 )
	{
		// 主線終點（於任何 destruct 之前先記旗標——destruct-LAST）。
		killer->set("quest/main_canon11_done", 1);

		message_vision(
			HIR "侮天鬼發出一聲撼動天地的厲嘯——那一聲嘶吼裡，五千年的不甘、洪荒"
			"以來的狂傲俱化作齏粉。牠頸上那顆失而復聚的元神之首再度自軀體上崩裂、墜"
			"落，遍體的封印鎖鏈轟然絞緊，將那顆猙獰的鬼首重重纏鎖、拖回那五千年前寒於"
			"氏為牠掘下的幽窟深淵。億兆被牠吞噬的生靈魂魄自牠潰散的軀殼中泠泠飛升，化"
			"作漫天清光，緩緩散入這天朝帝國的山川人間。\n" NOR, killer);
		message_vision(
			HIY "幽窟深處一片澄明——$N繼五千年前那位捨身相搏的上古聖者寒於氏之後，"
			"終於了結了這場橫亙五千年的終局之戰。侮天鬼的元神再度被封鎮於永劫，寒於氏"
			"那未竟的遺志、那捨身一搏的聖戰，至此終得告慰；那欲吞盡蒼生氣運、以證『天"
			"可侮』的狂言，永遠地碎在了這幽窟之中。天朝帝國億兆生靈，自這一刻起得救了。\n" NOR,
			killer);
		message_vision(
			HIM "（這是天朝帝國正史主線的終點——少俠歷九章艱險、於人靈魂泉重凝大成、"
			"了結十三厲魂，終承寒於氏五千年前未竟之志，再封侮天鬼於永劫。一場橫亙洪荒"
			"與五千年的因果，至此盡了。天下蒼生，都記著少俠這最後一程。）\n" NOR,
			killer);
	}

	// 屍體/bounty/善後悉依 std/char/npc.c::die()（恒呼，不可略）。
	// 須先呼 ::die()（屍身於此生成並登錄 temp("corpse")），再將終局獎勵落入屍身。
	::die();

	// ::die() 之後（屍身已生成）：終局獎勵「寒於氏遺澤」落入侮天鬼屍身。
	// 下手者須為十三靈已盡滅的真實決戰者，方落獎勵（鏡旗標推進之守衛）。
	if( objectp(killer)
	&&	killer != this_object()
	&&	userp(killer)
	&&	killer->query("quest/main_canon11") >= 1 )
		drop_legacy(killer);
}

// 終局獎勵「寒於氏遺澤」落入侮天鬼屍身。who=下手者(真實決戰者)；於 ::die() 之後呼叫，
//   corpse 已存在於 query_temp("corpse")。__DIR__ 已含 npc/ 結尾，故路徑為 __DIR__"obj/hanyu_legacy"。
//   獎勵置入屍身；屍身不存則退置於房間地面（防萬一）。
private void drop_legacy(object who)
{
	object corpse, loot;

	if( !who ) return;

	loot = new(__DIR__"obj/hanyu_legacy");
	if( !objectp(loot) ) return;

	corpse = query_temp("corpse");
	if( !objectp(corpse) || !loot->move(corpse) )
		loot->move(environment());

	message_vision(
		HIY "侮天鬼那青黑如鑄鐵的軀殼轟然崩散之際，自牠胸腹封印鎖鏈最深處——那正是"
		"五千年前寒於氏一道道力斬入、與牠的元神同封於此的所在——竟泠泠墜下一脈流轉著"
		"清正之光的遺物。想是那位捨身相搏的上古聖者，將自身最後一縷遺志、一脈遺澤，連"
		"同這頭至邪元神同封了五千年；如今封解魔滅，這『寒於氏遺澤』，便落到了續其聖戰"
		"的有緣人手中。\n" NOR, who);
}

// vim: set ts=4 sw=4 syntax=lpc
