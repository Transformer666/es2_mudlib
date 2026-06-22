// yaoshou.c -- 靈樞藥叟，世代守護秋一谷的谷主，本獵場的巔峰對手(boss)。
//
// 來歷（承接 canon）：
//   docs 02-遊戲系統與機制/05-裝備與強化.md L233：藥石脈錄→水嵐東方森林秋一谷。
//   docs 02-遊戲系統與機制/06-煉丹與書本系統.md L160：藥石脈錄→水嵐東方森林秋一谷。
//   靈樞藥叟者，秋一谷世代守藥的谷主也。他枯瘦如柴、形容古拙，卻畢生浸於這藥
//   石之谷的靈氣藥理，將谷中藥石所藏的醫藥脈理盡參於胸，著成一卷『藥石脈錄』。
//   他守谷甚嚴，外人欲奪這卷畢生心血的藥石奇書，非堂堂正正將他擊敗不可。
//
// 設計（boss，中高階 lv50，對齊 d/mengjia 田由 / d/langwo 摩雲一線之 lv50 巔峰）：
//   * 戰力定在 level 50：con58/str46/dex42，內功(force)145 為主(藥叟以藥石內力見
//     長)、徒手(unarmed)125、招架(parry)120、身法(dodge)105；另以 advance_stat
//     厚其 gin/kee/sen，使之耐戰、底氣足。量級對齊田由 lv50(技 130-145)而略守——
//     是一場硬仗，火候到家、持械有備的強者打得過。是凡間血肉的隱世藥師，非劇情魔頭。
//   * accept_fight 回傳 1——奉陪到底、藥石內力雄渾，絕不退縮。
//   * 不設 aggressive 等主動 attitude——由玩家自行 kill 起釁(鏡獵場慣式)。
//   * 結構鏡 d/mengjia/npc/tianyou.c：die() 之 bounty/屍體/善後一併走 std/char/npc.c::die()。
//   * do_ask(藥石脈錄) lore 閒談——點出此書來歷與奪書須先伏其人(純氣氛，不設旗標)。
//
// 死亡（die()）：藥叟伏誅時，若下手者(last_damage_giver)為真實玩家(userp)，則於 ::die()
//   之後自其屍身遺落一卷「藥石脈錄」(F_STUDY 頂級書，study 可進針法/內功)。此書非世界
//   唯一信物——其源為可重生之 boss(鏡 sixyin_manual / wuming_manual 之非唯一)，故每名真實
//   玩家擊殺皆得一卷(直接 new 入屍體)，使本獵場可重複造訪、人人有得學。不碰任何 quest 旗標。

#include <npc.h>
#include <ansi.h>

inherit F_VILLAGER;

#define QIUYI_BOOK  __DIR__"obj/yaoshi_book"   // 藥石脈錄(F_STUDY 頂級書)

void die();
int do_ask(string arg);
private void drop_book(object who);

void create()
{
	set_name("靈樞藥叟", ({ "yao shou", "yaoshou", "old herbalist", "herbalist" }) );
	set("nickname", "守谷藥叟");
	// 根骨 58 → 形體上限約 290 點；另以 advance_stat 厚其氣血，內力雄渾、極耐戰。
	set_attr("con", 58);
	set_attr("str", 46);
	set_attr("dex", 42);
	set_attr("int", 30);
	set_attr("wis", 30);
	set_race("human");
	set_class("alchemist");
	set_level(50);

	// 藥叟之藝：畢生浸於藥石靈氣，內功(force)雄渾醇厚為主，徒手點穴(unarmed)、
	// 拆招(parry)、身法(dodge)俱臻高手之境。另諳針法、藥理(守谷者之能)。
	set_skill("unarmed", 125);
	set_skill("dodge", 105);
	set_skill("parry", 120);
	set_skill("force", 145);
	set_skill("needle", 130);
	set_skill("literate", 80);

	// 厚其三元，使之底氣充沛、耐戰持久——對齊田由 lv50 一線而略守。
	advance_stat("gin", 280);
	advance_stat("kee", 280);
	advance_stat("sen", 220);

	set("age", 78);
	set("gender", "male");
	set("long",
		"這便是世代守護秋一谷的谷主靈樞藥叟了。他鬚眉皆白﹐枯瘦\n"
		"如柴﹐一領藥農布袍補綴得重重疊疊﹐洗得灰白﹐看去與尋常的\n"
		"採藥老農別無二致。然他久居這藥石之谷﹐吸納了滿谷醇厚的藥\n"
		"石靈氣﹐一身內力早已雄渾深湛得不可思議——那雙手枯瘦如鷹\n"
		"爪﹐指節間隱隱透著一層瑩潤的藥色﹐顯是常年揉搓藥石、運氣\n"
		"煉藥所致。他雖形容枯槁﹐一雙眼睛卻精光內斂﹐深不見底﹐周\n"
		"身自有一股淵渟嶽峙、與這秋一谷渾然一體的沉靜氣度。這谷中\n"
		"的奇花異草、靈芝藥石﹐連同他畢生參詳藥理而成的那卷『藥石\n"
		"脈錄』﹐外人若想奪取﹐須得先過他這一關。\n");
	set("chat_chance_combat", 3);
	set("chat_msg_combat", ({
		"靈樞藥叟枯瘦的手掌一翻﹐指尖點點﹐竟是一路精準狠辣的點穴手法﹐直取你周身要害。\n",
		"靈樞藥叟運起一身雄渾的藥石內力﹐枯瘦的身形陡然一震﹐掌風過處﹐藥氣氤氳如霧。\n",
		"靈樞藥叟沉聲道﹕老朽守這藥石之谷一甲子﹐這卷脈錄是老朽畢生的心血——豈容你輕易奪去﹗\n",
		"靈樞藥叟身形飄忽如一縷藥煙﹐繞著你游走不定﹐枯指彈出﹐勁氣如針﹐專點你的麻穴。\n",
	}));
	// 純 score：江湖歷練(升級)、武術造詣、武學之道、實戰經驗、武名、聲望。
	// boss 之獵，閱歷給得豐厚(對齊田由 lv50 一線)；此為純戰鬥 boss、無錢幣。
	set("bounty", ([
		"survive"         : 1300,
		"unarmed mastery" : 240,
		"martial art"     : 180,
		"martial mastery" : 110,
		"combat"          : 110,
		"martial fame"    : 100,
		"reputation"      : 50,
	]));
	setup();
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

// lore 閒談：點出藥石脈錄的來歷與「奪書須先伏其人」(純氣氛，不設任何旗標)。
int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想向這藥叟請教甚麼﹖（試試 ask yaoshou about 藥石脈錄）\n");

	if( arg == "yaoshou about 藥石脈錄"
	||  arg == "yaoshou about 脈錄"
	||  arg == "yaoshou about 藥石"
	||  arg == "yaoshou about 秋一谷"
	||  arg == "yaoshou about book"
	||  arg == "yaoshou about yaoshi" ) {
		do_chat(({
			(: command, "say 後生問這個﹖這秋一谷的藥石﹐石上的紋理暗合人身的經脈藥理——老朽守谷一甲子﹐日日參詳﹐方悟得這藥石之中所藏的醫藥脈絡、針砭之道。" :),
			(: command, "say 老朽將這一甲子的所悟﹐盡數著成了一卷『藥石脈錄』。譜中所載﹐上自藥石經脈、下至運針施治﹐皆是天底下最精微的醫藥針石之學﹐讀通了﹐於針法、內功俱有大進益。" :),
			(: command, "say 只是這卷脈錄是老朽畢生的心血﹐豈是隨口討得去的﹖後生若真有那份能耐與緣法﹐便堂堂正正勝過老朽這把朽骨——這卷脈錄﹐自然便是你的了。" :),
		}));
		return 1;
	}

	return notify_fail("藥叟枯瘦的手掌一翻﹐自顧揉搓著一味藥石﹐恍若未聞。\n");
}

// boss：奉陪到底、藥石內力雄渾(他並不主動撲路人﹐由玩家 kill 起釁)。
int accept_fight(object ob)
{
	do_chat((: command, "say 靈樞藥叟緩緩起身﹐枯瘦的手掌一翻﹐沉聲道﹕也罷﹐既要奪老朽的脈錄﹐便先過了老朽這一關再說﹗" :));
	return 1;
}

// 簽名掉落：下手者須為真實玩家；於 ::die() 之後呼叫，corpse 已生成於 temp("corpse")。
//   藥石脈錄非世界唯一信物(源為可重生之 boss)，故直接 new 一卷入屍——每名真實玩家擊殺
//   皆得一卷，使本獵場可重複造訪、人人有得學(鏡 sixyin_manual / wuming_manual 之非唯一)。
private void drop_book(object who)
{
	object corpse, book;

	if( !objectp(who) ) return;

	book = new(QIUYI_BOOK);
	if( !objectp(book) ) return;

	// 置入屍體；屍體不存(極端情形)則退置於房間地面(防萬一)。
	corpse = query_temp("corpse");
	if( !objectp(corpse) || !book->move(corpse) )
		book->move(environment());

	message_vision(HIY
		"靈樞藥叟枯瘦的身軀晃了一晃﹐終究撐不住那致命的一擊﹐長嘆一聲﹐頹然\n"
		"倒在了那方青玉藥案之畔。他懷中滑落一卷古樸的書冊——封皮上『藥石脈錄』\n"
		"四個蒼勁的篆字赫然在目﹗這卷他守谷一甲子、畢生參詳藥石針理而成的奇\n"
		"書﹐到底是隨著他的敗亡﹐落到了你的手裡。\n" NOR);
}

// 死亡：先 ::die()(屍體/bounty/善後悉依 std/char/npc.c::die()﹐恒呼不可略﹐屍體於此生成
//   並登錄 temp("corpse"))﹐再於下手者為真實玩家時﹐自屍身遺落藥石脈錄。
void die()
{
	object killer;

	killer = last_damage_giver();

	// 屍體/bounty/善後悉依 std/char/npc.c::die()(恒呼)。須先 ::die()(屍體於此生成
	// 並登錄 temp("corpse"))，再於其後將秘笈置入屍體。
	::die();

	if( objectp(killer) && killer != this_object() && userp(killer) )
		drop_book(killer);
}

// vim: set ts=4 sw=4 syntax=lpc
