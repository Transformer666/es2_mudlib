// tianyou.c -- 田由，孟家莊主重金延請、坐鎮孟家後院的武師，本獵場的巔峰對手(boss)。
//
// 來歷（承接 canon）：
//   docs 01-世界觀與劇情/04-地圖與場景.md L118：孟家莊→孟家後院(六陰八卦譜：先打田由)。
//   docs 02-遊戲系統與機制/05-裝備與強化.md L232：六陰八卦譜→風城北方孟家後院(先打田由)。
//   田由是個自負武藝、性情倨傲的江湖武師，一身「六陰八卦」掌法已臻化境，掌走陰柔、
//   步隨身轉。莊主延他坐鎮後院、教授莊丁，外人欲奪他那卷鎮身的『六陰八卦譜』，
//   非堂堂正正將他擊敗不可。
//
// 設計（boss，中高階 lv50，介於 d/langwo 狼王/封山掌門 lvl40 與摩雲 lvl50 一線之間）：
//   * 戰力定在 level 50：con58/str48/dex42，掌法(unarmed)145、步法(dodge)115、招架
//     (parry)110、內功(force)130；另以 advance_stat 厚其 gin/kee/sen，使之耐戰、底氣足。
//     量級對齊摩雲 lvl50 一線(技 145-180)而略守——是一場硬仗，火候到家、持械有備的
//     強者打得過。是凡間血肉的武林高手，非劇情魔頭。
//   * accept_fight 回傳 1——奉陪到底、掌風凌厲，絕不退縮。
//   * 不設 aggressive 等主動 attitude——由玩家自行 kill 起釁(鏡 d/langwo 獵場慣式)。
//   * 結構鏡 d/langwo/npc/wolfking.c：die() 之 bounty/屍體/善後一併走 std/char/npc.c::die()。
//
// 死亡（die()）：田由伏誅時，若下手者(last_damage_giver)為真實玩家(userp)，則於 ::die()
//   之後自其屍身遺落一卷「六陰八卦譜」(F_STUDY 武功秘笈，study 可習八卦掌/八卦步法)。
//   此書非世界唯一信物——其源為可重生之 boss(鏡 wuming_manual「白猿相贈」、d/langwo 戰利品
//   慣式)，故每名真實玩家擊殺皆得一卷(直接 new 入屍體)，使本獵場可重複造訪、人人有得學。
//   此鉤子不碰任何 quest 旗標(自成一套、不牽主線)。

#include <npc.h>
#include <ansi.h>

inherit F_VILLAGER;

#define MENGJIA_MANUAL  __DIR__"obj/sixyin_manual"   // 六陰八卦譜(F_STUDY 武功秘笈)

void die();
private void drop_manual(object who);

void create()
{
	set_name("田由", ({ "tian you", "tianyou", "martial master", "master" }) );
	set("nickname", "六陰掌");
	// 根骨 58 → 形體上限約 290 點；另以 advance_stat 厚其氣血，血厚力沉、極耐戰。
	set_attr("con", 58);
	set_attr("str", 48);
	set_attr("dex", 42);
	set_attr("int", 28);
	set_race("human");
	set_class("fighter");
	set_level(50);

	// 六陰八卦：掌走陰柔詭譎(unarmed)、步隨身轉(dodge)、拆招老辣(parry)、內力雄渾(force)。
	// 技值對齊摩雲 lvl50 一線而略守——是武林高手而非凡獸，靠掌法與步法纏鬥取勝。
	set_skill("unarmed", 145);
	set_skill("dodge", 115);
	set_skill("parry", 110);
	set_skill("force", 130);
	// 掌法以八卦掌數行之、步法以八卦步法行之(主招式對應基礎 unarmed/dodge，沿用通用招式)。

	// 厚其三元，使之底氣充沛、耐戰持久——仍守於摩雲 lvl50 之下。
	advance_stat("gin", 280);
	advance_stat("kee", 280);
	advance_stat("sen", 200);

	set("age", 46);
	set("gender", "male");
	set("long",
		"這便是孟家莊主重金延請、坐鎮後院的武師田由了。他身形魁\n"
		"梧﹐赤著精壯的上身﹐筋肉虯結賁張﹐一雙手掌寬厚如蒲扇﹐掌\n"
		"緣磨出了一層厚厚的繭。他一身武學走的是陰柔詭譎的「六陰八\n"
		"卦」一路——掌法開闔吞吐如太極兩儀﹐步法循八卦方位游走﹐步\n"
		"隨掌轉、身似游龍﹐掌風所及﹐捲得滿場塵土飛旋。他自幼苦修\n"
		"這六陰八卦之學﹐如今早已臻於化境﹐江湖上敬畏地喚他一聲\n"
		"「六陰掌」。此刻他抱掌而立﹐冷眼掃量著闖院的來人﹐神情倨\n"
		"傲﹐眉宇間自有一股睥睨群雄、不可一世的傲氣——分明沒把你放\n"
		"在眼裡。\n");
	set("chat_chance_combat", 3);
	set("chat_msg_combat", ({
		"田由雙掌陡然一錯﹐掌風如刀﹐循著八卦方位倏地搶到你的側後﹐陰柔的掌力直拍後心。\n",
		"田由腳下步法一變﹐身形如游龍般繞著你滑轉﹐忽前忽後﹐教人摸不準他的掌從何處拍來。\n",
		"田由冷哼一聲﹐沉聲道﹕就憑你也想闖我孟家後院、奪我的六陰八卦譜﹖痴心妄想﹗\n",
		"田由雙掌一合﹐掌心吞吐出一團陰柔的勁氣﹐拍向你的當胸﹐掌風過處﹐塵土簌簌而落。\n",
	}));
	// 純 score：江湖歷練(升級)、掌法精熟、武術造詣、武學之道、實戰經驗、武名、聲望。
	// boss 之獵，閱歷給得豐厚(對齊 d/langwo 狼王一線，略高，因 lv50)；此為純戰鬥 boss、無錢幣。
	set("bounty", ([
		"survive"         : 1300,
		"unarmed mastery" : 260,
		"martial art"     : 180,
		"martial mastery" : 110,
		"combat"          : 110,
		"martial fame"    : 100,
		"reputation"      : 50,
	]));
	setup();
}

// boss：奉陪到底、掌風凌厲(他並不主動撲路人﹐由玩家 kill 起釁)。
int accept_fight(object ob)
{
	do_chat((: command, "say 田由倨傲地一抱拳﹐冷笑道﹕來得好﹗且讓你嚐嚐我六陰八卦的厲害﹗" :));
	return 1;
}

// 簽名掉落：下手者須為真實玩家；於 ::die() 之後呼叫，corpse 已生成於 temp("corpse")。
//   六陰八卦譜非世界唯一信物(源為可重生之 boss)，故直接 new 一卷入屍——每名真實玩家
//   擊殺皆得一卷，使本獵場可重複造訪、人人有得學(鏡 wuming_manual「白猿相贈」之非唯一)。
private void drop_manual(object who)
{
	object corpse, book;

	if( !objectp(who) ) return;

	book = new(MENGJIA_MANUAL);
	if( !objectp(book) ) return;

	// 置入屍體；屍體不存(極端情形)則退置於房間地面(防萬一)。
	corpse = query_temp("corpse");
	if( !objectp(corpse) || !book->move(corpse) )
		book->move(environment());

	message_vision(HIY
		"田由身形一晃﹐終究撐不住那致命的一擊﹐悶哼一聲頹然栽倒。他懷中滑落一卷\n"
		"以陳年絹帛裝裱、邊角磨得起了毛的舊譜——封皮上『六陰八卦譜』五個古樸的篆\n"
		"字赫然在目﹗這卷他畢生鑽研、視若性命的鎮身武學﹐到底是隨著他的敗亡﹐落\n"
		"到了你的手裡。\n" NOR);
}

// 死亡：先 ::die()(屍體/bounty/善後悉依 std/char/npc.c::die()﹐恒呼不可略﹐屍體於此生成
//   並登錄 temp("corpse"))﹐再於下手者為真實玩家時﹐自屍身遺落六陰八卦譜。
void die()
{
	object killer;

	killer = last_damage_giver();

	// 屍體/bounty/善後悉依 std/char/npc.c::die()(恒呼)。須先 ::die()(屍體於此生成
	// 並登錄 temp("corpse"))，再於其後將秘笈置入屍體。
	::die();

	if( objectp(killer) && killer != this_object() && userp(killer) )
		drop_manual(killer);
}

// vim: set ts=4 sw=4 syntax=lpc
