// tigerking.c -- 黑風虎王，黑風山獵場最深處虎穴中盤踞的巨虎之王，本獵場的
//                巔峰對手(apex)。稱雄黑風山數十年，群獸俯首，是須有備而來、武
//                藝精純且持械者方克的大物。
//
// 設計（apex beast，介於黑熊 lvl20[獵場下限] 與魚鐵山 lvl40 boss / 摩雲 lvl50
//   boss[戰力天花板]之間，仍是凡間血肉、可被擊殺的猛獸，非劇情魔頭）：
//   * 戰力定在 level 40 一線﹐con64/str54﹐unarmed120/dodge60/parry80/force100﹐
//     另以 advance_stat("kee",210) 大幅加厚氣血——血厚力沉、極耐戰。
//     刻意輕於魚鐵山(lvl40 技 130-150、kee+250)與摩雲(lvl50 技 150-180、kee+400)﹕
//     是一場硬仗﹐但裝備精良、劍術或內力到家的強者堂堂正正打得過。
//   * accept_fight 回傳 1 —— 奉陪到底、兇悍反擊﹐絕不退縮。
//   * 「不」設 aggressive 等主動攻擊的 attitude —— 由玩家自行 kill 起釁。
//   * 結構沿用 /d/hudao/wild/npc/blackbear.c（承 /d/snow/npc/rabbit.c）的獵物慣式﹐
//     die() 之 bounty/善後一併走 std/char/npc.c::die()。
//
// 死亡（die()）：虎王伏誅時﹐若下手者(last_damage_giver)為真實玩家(userp)﹐則於其
//   面前掉落一枚「黑風虎爪」(戰利品﹐可變賣)。以 if(!x->move(who)) x->move(env) 慣
//   式給物﹐防玩家已離場。本鉤子不碰任何 quest 旗標(自成一套、不牽主線)。末了恒呼
//   ::die()（屍體/bounty 悉依 std/char/npc.c::die() 一併結算給下手者）。

#include <npc.h>
#include <ansi.h>

inherit F_VILLAGER;

void create()
{
	set_name("黑風虎王", ({ "tiger king", "tigerking", "king", "heifeng huwang" }) );
	set("nickname", "黑風山君");
	// 根骨 64 → 形體上限約 320 點；另以 advance_stat 大幅加厚氣血，乃本獵場血最厚之物。
	set_attr("con", 64);
	set_attr("str", 54);
	set_attr("dex", 34);
	set_race("human");
	set_class("commoner");
	set_level(40);

	// 虎王之威：虎掌拍擊勢沉力猛、爪牙俱利﹐拆招內力俱臻高手之境。
	// 技值刻意低於魚鐵山(unarmed130/blade150)——是猛獸而非武林高手。
	set_skill("unarmed", 120);
	set_skill("dodge", 60);
	set_skill("parry", 80);
	set_skill("force", 100);

	// 大幅厚其氣血（kee+210），使之血厚耐戰——仍輕於魚鐵山 lvl40 的 250、摩雲 lvl50 的 400。
	advance_stat("kee", 210);

	set("age", 14);
	set("gender", "male");
	set("long",
		"這便是稱雄黑風山數十年的虎王。牠較尋常斑斕虎還要高出一\n"
		"圈﹐立起來幾與壯漢比肩﹐周身的皮毛是一種近乎墨黑的暗金﹐\n"
		"墨色的斑紋如焰似浪﹐額心那個天然的「王」字深峻而分明。牠\n"
		"伏踞在這黑風山最深處的虎穴之中﹐滿洞盡是啃剩的累累白骨——\n"
		"獐麂野豕的、豺狼豹子的﹐甚而還有獵戶斷折的弓矢與破碎的衣\n"
		"甲。牠那雙琥珀色的虎目深沉如淵﹐睥睨之間自有一股令百獸俯\n"
		"首、令勇者膽寒的滔天兇威。一聲低沉的虎嘯自牠胸腔裡滾出﹐\n"
		"震得整座虎穴嗡嗡作響﹐碎石簌簌而落——這頭山君﹐分明已將你\n"
		"視作了牠下一頓的食料。\n");
	set("chat_chance_combat", 3);
	set("chat_msg_combat", ({
		"黑風虎王一聲震天的長嘯﹐穴頂簌簌落下碎石﹐那股兇威撲面而來﹐直欲奪人心魄。\n",
		"黑風虎王巨掌揮處﹐挾著一股腥膻的勁風﹐爪風所及﹐石屑橫飛。\n",
		"黑風虎王琥珀色的虎目精光暴盛﹐喉間滾出低沉的怒嗥﹐尾梢狠狠拍打著地面。\n",
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
	do_chat((: command, "say 黑風虎王一聲震天怒嘯﹐巨軀拔地而起﹐挾著滔天兇威撲向膽敢犯穴的來人﹗" :));
	return 1;
}

// 掉落戰利品：虎王伏誅時﹐於下手者(真實玩家)面前掉落一枚黑風虎爪（可變賣）。
// 以 if(!x->move(who)) x->move(environment()) 慣式給物（玩家此刻必在場﹐防萬一）。
private void drop_trophy(object who)
{
	object claw;

	if( !who || environment(who) != environment() ) return;

	claw = new(__DIR__"obj/tiger_claw");
	if( !claw->move(who) ) claw->move(environment());

	message_vision(
		HIY "$N俯身自黑風虎王的前掌上﹐費力地拔下一枚玄色的巨爪——這枚黑風虎爪﹐"
		"便是$N獵殺這頭稱雄一山的虎王、足以教滿山獵戶都豎起大拇指的憑證了﹗\n" NOR,
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
	::die();
}

// vim: set ts=4 sw=4 syntax=lpc
