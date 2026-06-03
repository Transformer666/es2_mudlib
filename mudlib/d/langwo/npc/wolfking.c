// wolfking.c -- 蒼狼王，狼窩谷獵場最深處狼窟中盤踞的巨狼之王，本獵場的巔峰
//               對手(apex)。稱雄這片山林、為患武陵古道的禍首，群狼俯首，是須
//               有備而來、武藝精純且持械者方克的大物。
//
// 設計（apex beast，介於餓狼 lvl20[獵場下限偏上] 與魚鐵山 lvl40 boss / 摩雲
//   lvl50 boss[戰力天花板]之間，仍是凡間血肉、可被擊殺的猛獸，非劇情魔頭）：
//   * 戰力定在 level 40 一線﹐con64/str54﹐unarmed120/dodge60/parry80/force100﹐
//     另以 advance_stat("kee",210) 大幅加厚氣血——血厚力沉、極耐戰。
//     刻意輕於魚鐵山(lvl40 技 130-150、kee+250)與摩雲(lvl50 技 150-180、kee+400)﹕
//     是一場硬仗﹐但裝備精良、劍術或內力到家的強者堂堂正正打得過。
//     數值與黑風虎王(d/heifeng/npc/tigerking.c)同列，乃姊妹獵場的巔峰之獸。
//   * accept_fight 回傳 1 —— 奉陪到底、兇悍反擊﹐絕不退縮。
//   * 「不」設 aggressive 等主動攻擊的 attitude —— 由玩家自行 kill 起釁。
//   * 結構沿用 /d/heifeng/npc/tigerking.c（承 /d/snow/npc/rabbit.c）的獵物慣式﹐
//     die() 之 bounty/善後一併走 std/char/npc.c::die()。
//
// 死亡（die()）：狼王伏誅時﹐若下手者(last_damage_giver)為真實玩家(userp)﹐則於其
//   面前掉落一枚「狼王獠牙」(戰利品﹐可變賣)。以 if(!x->move(who)) x->move(env) 慣
//   式給物﹐防玩家已離場。本鉤子不碰任何 quest 旗標(自成一套、不牽主線)。末了恒呼
//   ::die()（屍體/bounty 悉依 std/char/npc.c::die() 一併結算給下手者）。

#include <npc.h>
#include <ansi.h>

inherit F_VILLAGER;

void create()
{
	set_name("蒼狼王", ({ "wolf king", "wolfking", "king", "canglang wang" }) );
	set("nickname", "狼窩之主");
	// 根骨 64 → 形體上限約 320 點；另以 advance_stat 大幅加厚氣血，乃本獵場血最厚之物。
	set_attr("con", 64);
	set_attr("str", 54);
	set_attr("dex", 34);
	set_race("human");
	set_class("commoner");
	set_level(40);

	// 狼王之威：撲擊勢沉力猛、爪牙俱利﹐拆招內力俱臻高手之境。
	// 技值刻意低於魚鐵山(unarmed130/blade150)——是猛獸而非武林高手。
	set_skill("unarmed", 120);
	set_skill("dodge", 60);
	set_skill("parry", 80);
	set_skill("force", 100);

	// 大幅厚其氣血（kee+210），使之血厚耐戰——仍輕於魚鐵山 lvl40 的 250、摩雲 lvl50 的 400。
	advance_stat("kee", 210);

	set("age", 13);
	set("gender", "male");
	set("long",
		"這便是稱雄這片山林、為患武陵古道的蒼狼之王。牠較尋常蒼狼\n"
		"還要大上兩圈﹐立起來幾與壯漢比肩﹐周身灰毛如鐵﹐根根倒\n"
		"豎﹐肩胛高聳如丘﹐筋肉虯結賁張。牠伏踞在這狼窩谷最深處的\n"
		"狼窟之中﹐滿洞盡是啃剩的累累白骨——獐麂野豕的、豺狼狐兔\n"
		"的﹐甚而還有行旅斷折的扁擔與破碎的行囊。牠那雙幽碧的眼睛\n"
		"深沉如淵﹐睥睨之間自有一股令百獸俯首、令勇者膽寒的滔天兇\n"
		"威。一聲低沉的長嗥自牠胸腔裡滾出﹐震得整座狼窟嗡嗡作響﹐\n"
		"碎石簌簌而落——這頭狼窩之主﹐分明已將你視作了牠下一頓的\n"
		"食料。\n");
	set("chat_chance_combat", 3);
	set("chat_msg_combat", ({
		"蒼狼王一聲震天的長嗥﹐穴頂簌簌落下碎石﹐那股兇威撲面而來﹐直欲奪人心魄。\n",
		"蒼狼王巨口開闔﹐挾著一股腥膻的勁風猛撲而至﹐爪牙所及﹐石屑橫飛。\n",
		"蒼狼王幽碧的眼睛精光暴盛﹐喉間滾出低沉的怒嗥﹐尾梢狠狠拍打著地面。\n",
	}));
	// 純 score：江湖歷練(升級)、拳腳精熟、武術造詣、武學之道、實戰經驗、武名、聲望。
	// 巔峰之獵﹐閱歷給得豐厚（survive 接近魚鐵山以上一線﹐然此為純戰鬥獵物、無錢幣）。
	set("bounty", ([
		"survive"         : 1000,
		"unarmed mastery" : 220,
		"martial art"     : 150,
		"martial mastery" : 90,
		"combat"          : 90,
		"martial fame"    : 80,
		"reputation"      : 40,
	]));
	setup();
}

// apex：奉陪到底、兇悍反擊（牠並不主動撲路人﹐由玩家 kill 起釁）。
int accept_fight(object ob)
{
	do_chat((: command, "say 蒼狼王一聲震天怒嗥﹐巨軀拔地而起﹐挾著滔天兇威撲向膽敢犯窟的來人﹗" :));
	return 1;
}

// 頂級裝備(top-tier gear)稀有掉落（決策 G）：狼王為 lvl40 巔峰之獸，伏誅後除必掉
// 的普通戰利品「狼王獠牙」外，另有 WOLFKING_TOPGEAR_PCT 的機率自其屍身遺落一件頂
// 裝——隨機為神兵「蒼狼噬月刀」、或頂防「火鱗胸鎧」/「六合玲瓏靴」其一。頂裝極稀，
// 故走機率掉落。此鉤子於 ::die() 之後執行（屍體已由 char.c::die()→make_corpse 生
// 成並登錄 query_temp("corpse")），將頂裝直接置入屍體。
//
// 機制(corpse-drop)：clone 頂裝 → 移入 query_temp("corpse")(屍體)；屍體不存(極端
//   情形)則退置於房間地面。神兵起手即頂住 enchant_cap(見 obj/topgear/*.c)，不破壞
//   強化系統建立的戰鬥平衡。
#define WOLFKING_TOPGEAR_PCT    20      // 頂裝掉落機率(%)。極稀——調此值即調稀有度。

private mixed *wolfking_topgear = ({   // 頂裝掉落池（隨機取一）。
	"/obj/topgear/canglang_blade",      // 蒼狼噬月刀（blade，神兵）
	"/obj/topgear/firescale_armor",     // 火鱗胸鎧（body armor，頂防）
	"/obj/topgear/wonder_boots",        // 六合玲瓏靴（feet_eq，頂防）
});

// 稀有頂裝掉落：擲骰中獎則自掉落池隨機 clone 一件頂裝，置入狼王屍身。
// who = 下手者(真實玩家)；於 ::die() 之後呼叫，corpse 已存在於 temp("corpse")。
private void drop_topgear(object who)
{
	object corpse, loot;
	string file;

	if( !who ) return;
	if( random(100) >= WOLFKING_TOPGEAR_PCT ) return;  // 未中獎，無頂裝。

	file = wolfking_topgear[random(sizeof(wolfking_topgear))];
	loot = new(file);
	if( !objectp(loot) ) return;

	// 置入屍體；屍體不存則退置於房間地面（防萬一）。
	corpse = query_temp("corpse");
	if( !objectp(corpse) || !loot->move(corpse) )
		loot->move(environment());

	message_vision(
		HIY "蒼狼王那龐然的屍身轟然倒地之際﹐自牠滿是累累白骨的巢穴血肉之間﹐"
		"竟『噹』地滑落一件寒光懾人的奇珍——想是這頭狼窩之主生前不知撕碎了"
		"多少行旅豪客﹐連這等連城之寶也一併沒入了牠的巢中﹗\n" NOR);
}

// 掉落戰利品：狼王伏誅時﹐於下手者(真實玩家)面前掉落一枚狼王獠牙（可變賣）。
// 以 if(!who->move(...)) ...move(environment()) 慣式給物（玩家此刻必在場﹐防萬一）。
private void drop_trophy(object who)
{
	object fang;

	if( !who || environment(who) != environment() ) return;

	fang = new(__DIR__"obj/wolf_fang");
	if( !fang->move(who) ) fang->move(environment());

	message_vision(
		HIY "$N俯身自蒼狼王的巨口中﹐費力地拔下一枚雪亮的獠牙——這枚狼王獠牙﹐"
		"便是$N獵殺這頭為患一方的狼窩之主、足以教滿山獵戶與武陵行旅都豎起大拇指的憑證了﹗\n" NOR,
		who);
}

// 死亡：掉落戰利品（下手者須為真實玩家），末了恒呼 ::die()（bounty/屍體悉依之）。
void die()
{
	object killer;

	killer = last_damage_giver();

	if( objectp(killer)
	&&	killer != this_object()
	&&	userp(killer) )
		drop_trophy(killer);

	// 屍體/bounty/善後悉依 std/char/npc.c::die()（恒呼﹐不可略）。
	// 須先呼 ::die()(屍體於此生成並登錄 temp("corpse"))，再擲頂裝掉落入屍。
	::die();

	// 頂裝(top-tier gear)稀有掉落（決策 G）：下手者須為真實玩家﹐機率置頂裝入屍身。
	if( objectp(killer) && killer != this_object() && userp(killer) )
		drop_topgear(killer);
}

// vim: set ts=4 sw=4 syntax=lpc
