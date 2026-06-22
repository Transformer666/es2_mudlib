// yan_kuangfeng.c -- 黑風寨大寨主 閰狂風（黑風寨四頭目之首，本副本主 boss）。
//
// 設定（依 docs/02-遊戲系統與機制/05-裝備與強化.md L184-186「黑風寨四頭目」：
//   「閰狂風 → 巨劍『破石』、紫羅點翠戰甲、天地雲衫、杞庸兵書」，及 docs/01-世界觀
//   與劇情/04-地圖與場景.md L124「黑風寨：四頭目掉裝」）：
//   閰狂風乃盤踞黑風絕壁峽口、稱霸一方的綠林巨梟﹐黑風寨大寨主。天生神力﹐慣使一柄
//   開山巨劍「破石」﹐當年連劈黑風山三道石坊而劍鋒不卷﹐「破石」之名由此而起。
//
// 戰力定位（boss，lv 60，黑風寨四頭目之首，戰力高於餘三頭目）：
//   * 規格參照魚鐵山(d/snowmanor lv40 技130-150/kee+250)以上一線﹐並提至 lv60、技
//     150-170、advance_stat kee/gin/sen 各 +320﹐血厚力沉、極耐戰——是須有備而來、
//     裝備精良、武藝精純者方克的大物。仍屬凡間血肉、可被擊殺(非劇情魔頭)。
//   * accept_fight 回傳 1 —— 奉陪到底、兇悍反擊。
//   * 「不」設 aggressive —— 由玩家自行 kill 起釁(黑風寨為高階副本﹐玩家擇機挑戰)。
//   * 結構/掉落鏡 d/fonxan/npc/master.c：die() 先 ::die()(屍體生成、登錄 temp("corpse"))，
//     再於下手者為真實玩家時走 LOOT_D->unique_drop 掉全服唯一簽名神兵；神兵已現世則
//     改掉普通的「黑風寨刀」(非 unique)使本次擊殺仍有兵刃可得。
//
// 簽名掉落（doc 指定，全服唯一）：閰狂風 → 巨劍『破石』(/obj/topgear/poshi_greatsword.c)。
//   docs 另列其名下「紫羅點翠戰甲、天地雲衫、杞庸兵書」三件——本副本將之分屬其餘三頭目
//   各一件掉落(熊兆雄→戰甲、雲八方→雲衫、殷無常→兵書)，使「四頭目掉裝」四件俱備。

#include <npc.h>
#include <ansi.h>

inherit F_VILLAGER;

// 全服唯一簽名神兵 / 神兵已現世時的普通替代刀。
#define YAN_UNIQUE_LOOT  "/obj/topgear/poshi_greatsword"      // 神兵 破石巨劍(全服唯一)
#define YAN_NORMAL_LOOT  "/d/heifeng/npc/obj/zhaidao"         // 普通 黑風寨刀(神兵已現世時替代)

void die();
private void drop_signature(object who);

void create()
{
	set_name("閰狂風", ({ "yan kuangfeng", "kuangfeng", "zhaizhu", "yan" }) );
	set("nickname", "黑風寨主");
	set_attr("str", 30);
	set_attr("dex", 26);
	set_attr("int", 22);
	set_attr("wis", 22);
	set_attr("spi", 24);
	set_attr("cps", 25);
	set_attr("con", 30);
	set_attr("cor", 26);
	set_race("human");
	set_level(60);
	set_class("fighter");
	set("sect", "黑風寨");
	set("rank", "大寨主");

	// 大寨主之威：巨劍剛猛、內力深厚﹐技值居四頭目之首。
	set_skill("unarmed", 120);
	set_skill("sword", 170);
	set_skill("parry", 150);
	set_skill("dodge", 130);
	set_skill("force", 150);

	advance_stat("gin", 320);
	advance_stat("kee", 320);
	advance_stat("sen", 320);

	set("gender", "male");
	set("age", 48);
	set("long",
		"這便是稱霸黑風一帶、令來往商旅聞風喪膽的黑風寨大寨主閰狂\n"
		"風。他生得身軀魁梧如鐵塔﹐袒著半邊精赤的胸膛﹐虯結的肌肉\n"
		"上橫七豎八地縱橫著舊年廝殺留下的刀疤﹐一張黑臉煞氣騰騰﹐\n"
		"一部鋼針般的虯髯根根戟張。他天生神力﹐背上斜插著一柄烏沉\n"
		"沉的開山巨劍﹐尋常人連舉都舉不起﹐他卻能雙手掄之如風。相\n"
		"傳當年他憑這一劍連劈黑風山三道石坊而劍鋒不卷﹐「破石」之\n"
		"名由此而起。他踞坐在聚義廳的虎皮交椅上﹐睥睨之間自有一股\n"
		"睥睨群梟、殺伐決斷的兇威——這黑風寨上下數百嘍囉、三位頭\n"
		"目﹐俱在他一聲令下之間。\n");
	set("chat_chance_combat", 3);
	set("chat_msg_combat", ({
		"閰狂風厲喝一聲﹐雙手掄起那柄破石巨劍當頭斫落﹐劍風掃處﹐石屑橫飛﹗\n",
		"閰狂風一聲狂笑﹕黑風寨的地界﹐也是你撒野的地方﹖\n",
		"閰狂風巨劍橫掃﹐挾著一股開山裂石的沉雄之勢﹐颯颯有聲﹗\n",
	}));
	// boss 閱歷豐厚（lv60 四頭目之首；survive 高於 lv40 巔峰獸一線，另給黑道聲望/錢幣）。
	set("bounty", ([
		"survive"         : 1500,
		"sword mastery"   : 240,
		"martial art"     : 180,
		"martial mastery" : 110,
		"combat"          : 110,
		"martial fame"    : 100,
		"reputation"      : 60,
	]));
	setup();
	// 生前佩一柄普通的黑風寨刀應戰——「不」carry 簽名神兵破石巨劍：carry_object 對
	// unique 物會走 violate_unique→create_replica 在世間留下一柄 clone，將令死亡時
	// LOOT_D->unique_drop 的 world_count 誤判已有一柄而拒掉(全服唯一機制)。神兵破石
	// 巨劍僅於死亡時依唯一性掉落(見 die()/drop_signature)。鏡 d/fonxan/npc/master.c：
	// 該掌門生前佩 silversword(非神兵)，神兵玄蘇劍只在死後 LOOT_D 掉落。
	carry_object(YAN_NORMAL_LOOT)->wield();
	carry_money("coin", 2000);
}

// boss：奉陪到底、兇悍反擊（不主動撲路人﹐由玩家 kill 起釁）。
int accept_fight(object ob)
{
	do_chat((: command, "say 閰狂風虎目一張﹐厲喝道﹕哪裡來的不知死活的小輩﹐也敢上我黑風寨來撒野﹗" :));
	return 1;
}

// 簽名掉落：下手者須為真實玩家；於 ::die() 之後呼叫，corpse 已生成於 temp("corpse")。
//   先試掉全服唯一簽名神兵「破石巨劍」(LOOT_D->unique_drop)；世界已有一柄則回 0，改掉
//   普通的「黑風寨刀」(new)，使第二位以後的殺者仍得一柄像樣的刀、不致空手。
//   (LOOT_D 巨集需 globals.h，npc.h 未含，故逕用字面路徑 "/daemon/misc/loot.c"——等義 call_other。)
private void drop_signature(object who)
{
	object corpse, loot;

	if( !objectp(who) ) return;

	corpse = query_temp("corpse");
	if( !objectp(corpse) ) return;

	// 全服唯一簽名神兵：LOOT_D 盤點世界現存破石巨劍 clone 數，無則 new 一柄入屍、回該物件。
	loot = "/daemon/misc/loot.c"->unique_drop(YAN_UNIQUE_LOOT, corpse);
	if( objectp(loot) ) {
		message_vision(HIY
			"閰狂風那魁梧的屍身轟然倒地之際﹐背上那柄烏沉沉的開山巨劍「噹啷」脫落墜地"
			"——劍闊如門板、烏沉不見光﹐劍脊上一個斗大的「破」字筆勢狂橫﹐赫然便是這寨"
			"主稱霸一方、連劈三道石坊而鋒不卷的鎮寨神兵「破石巨劍」﹗\n" NOR);
		return;
	}

	// 神兵已現世於他處(全服唯一) → 改掉落普通的黑風寨刀(非 unique)，使本次擊殺仍有兵刃可得。
	loot = new(YAN_NORMAL_LOOT);
	if( !objectp(loot) ) return;
	if( !loot->move(corpse) ) loot->move(environment());

	message_vision(HIR
		"閰狂風頹然倒地﹐手中一柄烏黑的厚背鋼刀「噹」地墜落——是一柄黑風寨頭目慣用的黑風寨刀。\n" NOR);
}

// 死亡：先 ::die()(屍體/bounty/善後悉依 std/char/npc.c::die()﹐恒呼不可略﹐屍體於此生成
//   並登錄 temp("corpse"))﹐再於下手者為真實玩家時﹐自屍身遺落簽名掉落。
void die()
{
	object killer;

	killer = last_damage_giver();

	::die();

	if( objectp(killer) && killer != this_object() && userp(killer) )
		drop_signature(killer);
}

// vim: set ts=4 sw=4 syntax=lpc
