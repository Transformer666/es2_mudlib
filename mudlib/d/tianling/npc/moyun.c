// moyun.c -- 獸王摩雲，主線任務八「天靈降魔」的決戰魔頭(最終 boss)
//
// 故事背景（承接主線七「鎮邪求聖」）：
//   獸王摩雲生具懾服百獸之能﹐極是狡黠兇悍﹐受天靈山深處那頭悔天鬼與「混沌
//   珠」的牽動﹐每隔數十年便興一場獸亂。歷代獵王世家三代追之不得。近來牠循
//   著天靈山那縷邪念退守天靈山麓﹐蟄伏蓄勢﹐欲養足兇威再興更大的獸亂。雲遊
//   高僧與守木尊者道破：摩雲一脈之邪皆源自那縷牽動百獸的邪念﹐尋常刀兵難傷
//   其本﹐唯有自聖木餘力溫養而成的「淨邪聖木牌」(制邪聖物)方能克其邪念、護
//   人破障。少俠既已求得聖物、破障入窟﹐這頭獸王﹐便是他了結這場禍事的去處。
//
// 設計（boss-tier，較雪吟莊主魚鐵山更強的最終魔頭）：
//   * 戰力遠勝魚鐵山(lvl40)：level 50﹐unarmed 180 / blade 160 / parry 160 /
//     dodge 150 / force 170﹐三圍真氣 advance_stat gin/kee/sen 360/400/360
//     (魚鐵山為 240/250/230)﹐血厚力沉﹐是須有備而來、武藝精純且持械者方能克
//     的最終 boss。
//   * accept_fight 回傳 1 —— 奉陪到底、兇悍反擊﹐絕不退縮。
//   * 「不」設 aggressive 等主動攻擊的 attitude —— 牠蟄伏蓄勢﹐並不主動撲噬﹐
//     由玩家自行 kill 起釁(入窟前的邪障隘口 cleft.c 已把關﹐濾去未備聖物與
//     未完成主線七的冒進者﹐此即安全閥)。
//   * 聖物於戰中之意義(flavour + 輕機制)：玩家入窟/init 時﹐若身懷淨邪聖木牌﹐
//     則 message 一段「聖物青芒護持心神、壓制摩雲邪念」的敘述(純 flavour)﹔
//     摩雲被設定為「無聖物不可制」(由隘口把關強制持有聖物)。實際戰鬥仍走標準
//     戰鬥系統﹐不另造戰鬥 efun。
//
// 任務完成（die()）：
//   摩雲伏誅時﹐若 last_damage_giver()(下手者)是身負主線七旗標(quest/main_omen7
//   >= 3)的真實玩家(userp)且尚未完成主線八(main_omen8 < 3)﹕
//     - 把下手者 quest/main_omen8 設為 3（arc 高潮完成）
//     - 給決戰大賞：銅錢 800 + 一帖金液丹 + 一把洗銀劍﹐並授存活/俠義/聲望/武
//       名等大筆 gain_score(以 if(!x->move(who)) x->move(environment()) 慣式給物)
//     - message_vision 一段高潮敘事：摩雲伏誅﹐然其身死之際黑霧化作一縷邪念遁
//       向天靈山深處——混沌珠/悔天鬼之事未了(為更深的正史 arc 鋪路﹐不開任何新
//       任務)
//   防重複：若 main_omen8 已 >= 3﹐則僅作尋常死亡(不重複給賞)。
//   末了恒呼 ::die()（屍體/bounty/善後悉依 std/char/npc.c::die()）。
//   另設 bounty(尋常戰鬥經驗)﹐由 ::die() 一併結算給下手者。

#include <npc.h>
#include <ansi.h>

inherit F_VILLAGER;

void create()
{
	set_name("摩雲", ({ "moyun", "beast lord", "beastlord" }) );
	set("nickname", "獸王");
	set_attr("str", 33);
	set_attr("dex", 30);
	set_attr("int", 22);
	set_attr("wis", 22);
	set_attr("spi", 28);
	set_attr("cps", 30);
	set_attr("con", 34);
	set_attr("cor", 28);
	set_race("human");
	set_level(50);
	set_class("fighter");
	set("sect", "天靈山");
	set("rank", "獸王");

	// boss-tier：較魚鐵山(unarmed130/blade150/parry130/dodge110/force130)全面更強。
	set_skill("unarmed", 180);
	set_skill("blade", 160);
	set_skill("parry", 160);
	set_skill("dodge", 150);
	set_skill("force", 170);

	// 真氣遠厚於魚鐵山(gin/kee/sen 240/250/230)——血厚力沉的最終 boss。
	advance_stat("gin", 360);
	advance_stat("kee", 400);
	advance_stat("sen", 360);

	set("gender", "male");
	set("age", 300);
	set("long",
		"這便是那懾服天靈山百獸的獸王摩雲。牠形貌似獸而非獸——龐然\n"
		"如山的身軀蹲踞於青黑霧靄之中﹐一身森然倒豎的黑毛纏裹著化不\n"
		"開的戾氣﹐脊背起伏如連綿丘陵﹐四肢虯結﹐爪如彎鉤﹐單一爪便\n"
		"足以裂石分金。牠那雙深陷的眼眸裡幽幽燃著兩點青芒﹐睥睨之間\n"
		"自有一股令百獸俯首、令勇者膽寒的滔天兇威。據雲遊高僧所言﹐\n"
		"這頭獸王受了天靈山深處那頭悔天鬼與混沌珠的牽動﹐周身那縷牽\n"
		"動百獸發狂的邪念﹐尋常刀兵難傷其本——唯有至清至正的聖物﹐方\n"
		"克得這一身戾氣。牠蟄伏窟中﹐似在蓄養兇威﹐只待養足了氣力﹐\n"
		"便要再興一場席捲天下的滔天獸亂。\n");
	set("chat_chance_combat", 3);
	set("chat_msg_combat", ({
		"摩雲一聲震天的長嘯﹐窟頂簌簌落下碎石﹐那縷青黑戾氣隨之暴漲﹐直欲撕裂人的心神。\n",
		"摩雲巨爪揮處﹐挾著一股腥膻的勁風﹐爪風所及﹐石屑橫飛。\n",
		"摩雲雙目青芒大盛﹐喉間滾出低沉的怨嗥﹐那股懾服百獸的兇威撲面而來。\n",
	}));
	setup();
	carry_object("/obj/area/obj/blade")->wield();
	carry_money("coin", 300);

	// 尋常戰鬥經驗（由 ::die() 結算給下手者）。
	set("bounty", ([
		"survive" : 600,
		"martial fame" : 120,
		"reputation" : 60,
	]));
}

void init()
{
	::init();

	// 聖物於戰中之意義（純 flavour）：玩家持淨邪聖木牌入窟﹐木牌青芒護持心神、
	// 壓制摩雲那一身邪念。實際戰鬥仍走標準戰鬥系統。
	if( this_player() && interactive(this_player())
	&&	present("holy relic", this_player()) )
		tell_object(this_player(),
			CYN "你懷中那面淨邪聖木牌青芒隱隱流轉﹐如一泓清泉護住你的心神﹐"
			"那撲面而來、勾魂攝魄的青黑邪念﹐竟被這聖物之力壓得節節退散——"
			"摩雲一身的戾氣雖盛﹐這一回﹐你總算能與牠堂堂正正地周旋一場了。\n"
			NOR);
}

// 頂級裝備(top-tier gear)稀有掉落（決策 G）：摩雲為 lvl50 最終 boss，伏誅後有
// MOYUN_TOPGEAR_PCT 的機率自其屍身中遺落一件頂裝神兵——隨機為「斬龍斧」(妖塔
// 系列，doc 名)或「玄霜劍」其一。頂裝極稀，故走機率掉落而非必掉；此鉤子於
// ::die() 之後執行（屆時屍體已由 char.c::die()→make_corpse 生成並登錄於
// query_temp("corpse")），將神兵直接置入屍體，玩家須 search/取屍 方得。
//
// 機制(corpse-drop)：clone 神兵 → 移入 query_temp("corpse")(屍體)；屍體不存
//   (極端情形)則退而置於房間地面。神兵以 new() clone，每把各擁獨立 dp(per-
//   clone dbase)，互不干涉。神兵起手即頂住 enchant_cap(見各 obj/topgear/*.c)，
//   不破壞強化系統建立的戰鬥平衡。
#define MOYUN_TOPGEAR_PCT   25      // 頂裝掉落機率(%)。極稀——調此值即調稀有度。

private mixed *moyun_topgear = ({    // 頂裝掉落池（隨機取一）。
	"/obj/topgear/zhanlong_axe",     // 斬龍斧（twohanded axe，doc 妖塔系列）
	"/obj/topgear/xuanshuang_sword", // 玄霜劍（sword）
});

// 稀有頂裝掉落：擲骰中獎則自掉落池隨機 clone 一件神兵，置入摩雲屍身。
// who = 下手者(真實玩家)；於 ::die() 之後呼叫，corpse 已存在於 temp("corpse")。
private void drop_topgear(object who)
{
	object corpse, loot;
	string file;

	if( !who ) return;
	if( random(100) >= MOYUN_TOPGEAR_PCT ) return;     // 未中獎，無頂裝。

	file = moyun_topgear[random(sizeof(moyun_topgear))];
	loot = new(file);
	if( !objectp(loot) ) return;

	// 置入屍體；屍體不存則退置於房間地面（防萬一）。
	corpse = query_temp("corpse");
	if( !objectp(corpse) || !loot->move(corpse) )
		loot->move(environment());

	message_vision(
		HIY "摩雲那龐然的屍身轟然委地之際﹐自牠虯結的皮肉骨血之間﹐"
		"竟『噹』地滑落一件寒光懾人的神兵——想是這頭獸王生前不知吞噬"
		"了多少英雄豪傑﹐連這等連城之珍也一併沒入了牠的腹中﹗\n" NOR);
}

// 給決戰大賞：銅錢、金液丹、洗銀劍﹐並授存活/俠義之舉/聲望/武名等大筆閱歷。
// （以 if(!x->move(who)) x->move(environment()) 慣式給物。）
private void give_reward(object who)
{
	object coin, pill, sword;

	if( !who || environment(who) != environment() ) return;

	coin = new("/obj/money/coin");
	coin->set_amount(800);
	if( !coin->move(who) ) coin->move(environment());

	pill = new("/obj/medication/alchemist/aquapill");
	if( !pill->move(who) ) pill->move(environment());

	sword = new("/d/snow/npc/obj/silversword");
	if( !sword->move(who) ) sword->move(environment());

	who->gain_score("survive", 1500);
	who->gain_score("emprise", 400);
	who->gain_score("reputation", 250);
	who->gain_score("martial fame", 300);
	who->gain_score("martial mastery", 120);
}

// 最終 boss：奉陪到底、兇悍反擊。
int accept_fight(object ob)
{
	do_chat((: command, "say 摩雲一聲震天怒嘯﹐巨軀拔地而起﹐撲向膽敢犯境的來人﹗" :));
	return 1;
}

// 死亡：主線八「天靈降魔」完成判定 + 決戰大賞 + 高潮敘事﹐末了恒呼 ::die()。
void die()
{
	object killer;

	killer = last_damage_giver();

	// 下手者須為身負主線七旗標的真實玩家﹐且尚未完成主線八（防重複給賞）。
	if( objectp(killer)
	&&	killer != this_object()
	&&	userp(killer)
	&&	killer->query("quest/main_omen7") >= 3
	&&	killer->query("quest/main_omen8") < 3 )
	{
		killer->set("quest/main_omen8", 3);
		give_reward(killer);

		// 高潮敘事：摩雲伏誅﹐然黑霧化作一縷邪念遁向天靈山深處——
		// 混沌珠/悔天鬼之事未了（為更深的正史 arc 鋪路﹐不開任何新任務）。
		message_vision(
			HIR "獸王摩雲發出一聲撕心裂肺的悲嘯﹐龐然的巨軀轟然委頓於地﹐"
			"濺起漫天的白骨與塵土。$N長身而立﹐這頭為禍歷代、令獵王世家三"
			"代追之不得的獸王﹐終於伏誅在你的手下﹗\n" NOR, killer);
		message_vision(
			HIM "然而﹐就在摩雲氣絕的剎那﹐牠周身那團青黑戾氣並未隨之消散——"
			"反倒猛地凝聚成一縷濃黑的邪念﹐發出一聲幽長而怨毒的嘶鳴﹐穿窟破"
			"霧﹐徑往天靈山更深、更幽暗的方向飄遁而去﹐轉瞬沒入雲靄之中。\n"
			"你心頭一凜——摩雲不過是受人驅策的爪牙﹐那縷遁去的邪念﹐分明指"
			"向天靈山深處那頭悔天鬼﹐與那顆喚作『混沌珠』的至邪之物。這場禍"
			"事﹐遠遠還沒有了結 ...\n"
			"那縷邪念穿壁遁去之際﹐窟室後壁竟被硬生生轟裂開一道幽深的縫隙﹐"
			"露出往北深入天靈山腹地的去路——循那縷邪念的去向追下去﹐前頭似有"
			"一位守山的道人正在恭候。(往北 north 可深入幽壑)\n" NOR, killer);
	}

	// 屍體/bounty/善後悉依 std/char/npc.c::die()（恒呼﹐不可略）。
	// 須先呼 ::die()(屍體於此生成並登錄 temp("corpse"))，再擲頂裝掉落入屍。
	::die();

	// 頂裝(top-tier gear)稀有掉落（決策 G）：下手者須為真實玩家﹐機率置神兵入屍身。
	if( objectp(killer) && killer != this_object() && userp(killer) )
		drop_topgear(killer);
}

// vim: set ts=4 sw=4 syntax=lpc
