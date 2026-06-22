// gongsunyixiao.c -- 平陽寨主 公孫一笑，平陽山獵場最深處寨主廳上盤踞的山賊之王，
//                    本獵場的巔峰之敵(apex)。據平陽山為患一方、聚嘯群賊、劫掠客商的
//                    禍首，是須有備而來、武藝精純且持械者方克的大物。
//
// 來歷(canon)：docs/02-遊戲系統與機制/05-裝備與強化.md L160「平陽寨主公孫一笑 → 冥龍甲、
//   金龍杖、杞庸兵書」(L229/06-煉丹與書本系統.md L156 另以「平陽山老大」列為杞庸兵書來源)。
//   本檔落實其為平陽山 boss，伏誅後掉落 canon 所載之頂級兵書「杞庸兵書」與頂防「冥龍甲」。
//   (金龍杖屬武器，本次任務未含其物件，從略——日後可比照另立。)
//
// 設計(apex，承黑風山蒼狼[lvl26]、狼窩谷狼王[lvl40 獵場 boss]往上一級，定 level 56，介於
//   魚鐵山[lvl40 莊主]與摩雲[lvl50 獸王]之上一線，為一名久經廝殺的山賊梟雄)：
//   * 戰力定在 level 56﹐con70/str58﹐blade150/parry130/dodge90/force130﹐另以
//     advance_stat 大幅加厚氣血——血厚刀沉、極耐戰。是一場硬仗﹐但裝備精良、刀術或
//     內力到家的強者堂堂正正打得過。
//   * accept_fight 回 1 —— 奉陪到底、兇悍反擊﹐絕不退縮。
//   * 「不」設 aggressive 等主動攻擊的 attitude —— 由玩家自行 kill 起釁。
//   * 結構沿用 d/langwo/npc/wolfking.c(獵場 boss die() 掉落範式)與 d/fonxan/npc/master.c
//     (簽名掉落 + LOOT_D 全服唯一-或-普通備援範式)：die() 之 bounty/善後一併走
//     std/char/npc.c::die()。
//
// 死亡(die())：公孫一笑伏誅時﹐若下手者(last_damage_giver)為真實玩家(userp)﹐則自其屍身
//   遺落 canon 簽名掉落：
//     (1) 杞庸兵書(qiyong_book)——必掉。canon 頂級兵書﹐每次擊殺皆得(以 new 置入屍體)。
//     (2) 冥龍甲(minglong_armor)——走 LOOT_D("/daemon/misc/loot.c")->unique_drop 全服唯一：
//         世界尚無任一件冥龍甲則掉之(全服唯一神甲)﹔已有一件則改掉普通備援甲「玄鐵戰甲」
//         (xuantie_armor，非 unique)﹐使第二位以後的殺者仍得一件像樣的好甲、不致空手。
//   末了恒呼 ::die()？──否﹕須**先**呼 ::die()(屍體於此生成並登錄 temp("corpse"))﹐**再**
//   於屍體內置入掉落物(鏡 wolfking.c / master.c：唯一/簽名掉落須在屍體生成「後」入屍)。
//   runtime-gotchas #10：die() 內 ::die() 之後不再 destruct 自身﹐善後悉依 ::die()。

#include <npc.h>
#include <ansi.h>

inherit F_VILLAGER;

// ── 簽名掉落藍本路徑。集中於此便於日後維護。──
// 杞庸兵書：docs 列其同為平陽寨主(L160)與黑風寨頭目(L186)之掉落物——同一部 canon 兵書、
//   兩處來源。前一任務已於 d/heifeng/npc/obj/qiyong_book.c 建立其唯一藍本(study force/parry、
//   identifiers 含「兵書」)。為免兩處各立一部效果歧異的杞庸兵書，本 boss 直接沿用該既有藍本
//   (同一部書兩處可得，clone 互不衝突)，不另建第二份。
#define QIYONG_BOOK       "/d/heifeng/npc/obj/qiyong_book"     // 杞庸兵書(必掉，canon 頂級兵書，沿用既有藍本)
#define MINGLONG_ARMOR    "/obj/topgear/minglong_armor"        // 冥龍甲(全服唯一頂防)
#define XUANTIE_ARMOR     "/d/pingyang/npc/obj/xuantie_armor"  // 玄鐵戰甲(冥龍甲已現世時的普通備援)

void die();
private void drop_signature(object who);

void create()
{
	set_name("公孫一笑", ({ "gongsun yixiao", "gongsunyixiao", "yixiao",
		"zhaizhu", "chief" }) );
	set("nickname", "平陽寨主");
	// 根骨 70 → 形體上限約 350 點；另以 advance_stat 大幅加厚氣血，乃本獵場血最厚之物。
	set_attr("str", 58);
	set_attr("dex", 36);
	set_attr("con", 70);
	set_attr("int", 30);
	set_race("human");
	set_class("commoner");
	set_level(56);

	// 寨主之威：朴刀勢沉力猛、刀法精純，拆招閃躲、吐納內力俱臻高手之境。
	set_skill("blade", 150);
	set_skill("unarmed", 90);
	set_skill("parry", 130);
	set_skill("dodge", 90);
	set_skill("force", 130);

	// 大幅厚其氣血(kee+260)，使之血厚耐戰——一場硬仗，然裝備精良者堂堂正正打得過。
	advance_stat("kee", 260);

	set("age", 41);
	set("gender", "male");
	set("long",
		"這便是據平陽山為患一方、聚嘯群賊的寨主公孫一笑了。他生得\n"
		"面白無鬚、身形精壯﹐一襲錦袍玉帶﹐偏又腰挎一柄缺了口卻磨得\n"
		"雪亮的朴刀﹐文不文、武不武﹐眉宇間自有一股梟雄的剽悍與算計。\n"
		"他原是個落第的武舉﹐因犯了人命亡命上山﹐憑著一身好刀法與一\n"
		"部祖傳的『杞庸兵書』﹐收攏流民潑皮、據險設伏﹐不過數年便將\n"
		"這平陽山經營成了周近數百里聞之色變的賊窟。他端坐在那張虎皮\n"
		"交椅上﹐一面把玩著手中那柄金燦燦的龍頭手杖﹐一面似笑非笑地\n"
		"睨著闖上廳來的你——那似笑非笑之間﹐殺機已隱隱凝聚。\n");
	set("chat_chance_combat", 3);
	set("chat_msg_combat", ({
		"公孫一笑似笑非笑﹐刀勢卻陡然轉急﹕好身手﹗可惜今日是你葬身之地﹗\n",
		"公孫一笑朴刀一橫﹐沉聲喝道﹕也罷﹐讓你嚐嚐我平陽寨主的厲害﹗\n",
		"公孫一笑足下七星亂踏﹐一刀斜削而出﹐刀風挾著一股逼人的煞氣。\n",
	}));
	// 純 score 為主、另掉散碎銀錢：江湖歷練(升級)、刀法精熟、武術造詣、武學之道、實戰
	// 經驗、武名、聲望。巔峰之敵﹐閱歷給得豐厚(接近狼窩谷狼王以上一線)。
	set("bounty", ([
		"survive"      : 1500,
		"blade mastery" : 300,
		"martial art"   : 200,
		"martial mastery": 120,
		"combat"        : 120,
		"martial fame"  : 100,
		"reputation"    : 60,
	]));
	setup();
	// 寨主隨身佩刀(沿用既有通用 blade 武器物件 /obj/area/obj/blade，不另立物件)與一筆
	// 劫掠所得的銀錢(屍身可取)。
	carry_object("/obj/area/obj/blade")->wield();
	carry_money("silver", 30);
}

// apex：奉陪到底、兇悍反擊（他並不主動撲路人﹐由玩家 kill 起釁）。
int accept_fight(object ob)
{
	do_chat((: command, "say 公孫一笑霍然起身﹐反手抽出朴刀﹐冷笑道﹕不知死活的東西﹐既上了我平陽山﹐就別想活著下去﹗" :));
	return 1;
}

// 簽名掉落：下手者須為真實玩家；於 ::die() 之後呼叫，corpse 已生成於 temp("corpse")。
//   (1) 杞庸兵書——必掉(new 入屍)。
//   (2) 冥龍甲——LOOT_D->unique_drop 全服唯一；世界已有一件則回 0，改掉普通的玄鐵戰甲(new)。
// (LOOT_D 巨集需 globals.h，npc.h 未含，故逕用字面路徑 "/daemon/misc/loot.c"——等義 call_other。)
private void drop_signature(object who)
{
	object corpse, book, armor;

	if( !objectp(who) ) return;

	corpse = query_temp("corpse");
	if( !objectp(corpse) ) return;

	// ── (1) 杞庸兵書：canon 頂級兵書，必掉。 ──
	book = new(QIYONG_BOOK);
	if( objectp(book) ) {
		if( !book->move(corpse) ) book->move(environment());
		message_vision(HIY
			"公孫一笑頹然倒地之際﹐懷中一卷陳舊絹帛裝裱的兵書「啪」地滑落塵埃——書頁泛黃、"
			"封題斑駁﹐赫然便是那部令他據山稱王數年的祖傳『杞庸兵書』﹗\n" NOR);
	}

	// ── (2) 冥龍甲：LOOT_D 盤點世界現存冥龍甲 clone 數，無則 new 一件入屍(全服唯一)。 ──
	armor = "/daemon/misc/loot.c"->unique_drop(MINGLONG_ARMOR, corpse);
	if( objectp(armor) ) {
		message_vision(HIC
			"公孫一笑那身錦袍崩裂處﹐露出一件墨黑幽藍、狀如龍鱗的曠世神甲——鱗光流轉、"
			"陰寒徹骨﹐正是他視若性命、護身鎮寨的『冥龍甲』﹗\n" NOR);
		return;
	}

	// 冥龍甲已現世於他處(全服唯一) → 改掉落普通的玄鐵戰甲(非 unique)，使本次擊殺仍有好甲可得。
	armor = new(XUANTIE_ARMOR);
	if( !objectp(armor) ) return;
	if( !armor->move(corpse) ) armor->move(environment());

	message_vision(HIR
		"公孫一笑那身錦袍崩裂處﹐露出一件鉚滿鐵釘的玄鐵戰甲——雖非那件鎮寨的神甲﹐"
		"也是一件難得的好甲。\n" NOR);
}

// 死亡：先 ::die()(屍體/bounty/善後悉依 std/char/npc.c::die()﹐恒呼不可略﹐屍體於此生成
//   並登錄 temp("corpse"))﹐再於下手者為真實玩家時﹐自屍身遺落簽名掉落(杞庸兵書 + 冥龍甲)。
void die()
{
	object killer;

	killer = last_damage_giver();

	::die();

	if( objectp(killer) && killer != this_object() && userp(killer) )
		drop_signature(killer);
}

// vim: set ts=4 sw=4 syntax=lpc
