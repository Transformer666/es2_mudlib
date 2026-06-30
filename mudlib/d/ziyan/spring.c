// Room: /d/ziyan/spring.c
// 紫煙溫泉——紫煙鎮心之南的溫泉景點。鎮名所本的一眼天然溫湯﹐
// 燒湯老叟在此司爐看泉（非戰鬥支線「安神香湯」的指路、授器人）。
// 唯一出口北回鎮心。no_fight。
//
// 泡溫泉（bathe / 泡溫泉）回復機制：
//   docs/01-世界觀與劇情/04-地圖與場景.md 客棧表列紫煙小棧/紫煙溫泉為溫泉鎮﹐
//   且本鎮 NPC（springman）已招呼玩家「下池泡泡﹐保管把一身的乏都泡開了」。
//   此處把那句招呼做成可實際進行的動作﹕在溫泉房 bathe/泡溫泉 → 浸浴溫湯﹐
//   緩緩回復精氣神（gin / kee / sen）﹐帶冷卻以免連點刷。
//
// 機制全部比照已讀過、確認的現有做法（cmds/std/fish.c、obj/reagent/yangqi_pill.c）：
//   * 房間自訂 init() + add_action（故【不】replace_program(ROOM)﹐見 lesson #11）。
//   * 守衛：life_form=="ghost" / is_busy() / is_fighting()﹐皆同 fish.c。
//   * 冷卻：set_temp("bathe_cooldown", time()+N)﹐以 time() 判定（同 fish.c）。
//   * 硬直：start_busy（泡湯得靜泡一陣﹐同 fish.c）。
//   * 回復：me->supplement_stat("gin"/"kee"/"sen", N)（同丹藥﹐見 yangqi_pill.c）。
//     supplement_stat 只把 current 補到 heal（受傷上限）為止﹐不會超補、不治外傷﹐
//     刻意做得比養氣丹溫和（純氣神回復、無 HP/heal_stat）﹐圖個細水長流。
//
// 平衡（皆為初版、可調﹐集中在下面 #define）：
//   冷卻 60 秒、每次回 gin/kee/sen 各 15~25。是「歇腳回神」而非速成回血——
//   不治外傷、不補形體﹐遠弱於丹藥﹐連點亦無益（冷卻內泡了也不回）。

#include <ansi.h>

inherit ROOM;

// --- 平衡參數（初版、可調）-------------------------------------------------
#define BATHE_COOLDOWN  60      // 兩次泡湯之間的冷卻秒數
#define BATHE_BUSY      2       // 泡湯後的硬直（heart beat 數）
#define BATHE_MIN       15      // 每項（gin/kee/sen）最少回復
#define BATHE_RANGE     11      // 浮動範圍：實回 = MIN + random(RANGE) → 15~25
// ---------------------------------------------------------------------------

int do_bathe(string arg);

void create()
{
	set("short", "紫煙溫泉");
	set("long", @LONG
這便是紫煙鎮聲名所本的那一眼溫泉了。一泓碧瑩瑩的溫湯盈在天
然的石窪裡﹐底下通著地脈﹐汩汩地翻著細密的水泡﹐騰起的湯氣裊裊
而上﹐在斜照裡泛出一抹說不清的淡紫﹐如煙如縠﹐這「紫煙」二字便
是從這湯氣來的。泉畔壘著一座石砌的湯灶﹐一位司爐看泉的老叟正守
在灶邊﹐替泡湯的客人添著柴火、看著水溫。湯氣裡浮著淡淡的硫泉與
草木的氣味﹐聞著便教人鬆乏。幾個鎮上的女兒在泉的下游就著溫湯浣
著巾帕﹐有一搭沒一搭地閒話。泉畔暖意融融﹐解衣下池泡個溫泉
（bathe﹐或 泡溫泉）﹐最是舒筋活絡、安神回乏。回北邊石階上去﹐
便是紫煙鎮心。
LONG
	);
	set("detail", ([
		"溫泉" : "一泓碧瑩瑩的溫湯盈在天然的石窪裡﹐水底通著地脈﹐終年汩汩地冒著溫熱的泉。湯氣裊裊﹐斜照一映便泛出淡淡的紫煙。聽老叟說﹐這泉水含著地底的礦氣﹐泡了舒筋活血﹐汲來煮茶焙香﹐更是別處比不得的。下池泡泡（bathe）﹐保管把一身的乏都泡開。\n",
		"湯灶" : "泉畔壘著一座石砌的湯灶﹐灶上溫著幾甕引來的泉水﹐灶口柴火明滅。司爐的老叟成日守在這兒﹐替泡湯的客人看著水溫、添著柴火﹐也替鎮上要煮茶焙香的人家﹐汲取最新鮮的溫泉。\n",
		"紫煙" : "溫泉蒸騰的湯氣裊裊而上﹐在晨昏的斜照裡泛出一抹淡淡的紫﹐如紗如夢﹐裊裊不散。鎮上人說﹐這紫煙是地脈的靈氣﹐紫煙鎮、紫煙小棧、紫煙溫泉﹐一鎮的名號全是從這一縷煙氣來的。\n",
		"女兒" : "泉的下游溫湯漫流處﹐幾個鎮上的女兒挽著袖子﹐就著暖暖的泉水浣著巾帕﹐木杵起落﹐一面浣一面低聲閒話﹐見了生客﹐只是靦腆地一笑。\n",
		"湯氣" : "泉上的湯氣溫溫熱熱﹐浮著淡淡的硫泉氣與草木的清味﹐深深吸一口﹐胸臆間說不出的鬆乏舒坦﹐一路趕來的塵勞﹐彷彿都教這暖香化開了。\n",
	]));
	set("objects", ([
		__DIR__"npc/springman" : 1,
		__DIR__"npc/girl" : 1,
	]));
	set("outdoors", "ziyan");
	set("no_fight", 1);
	set("exits", ([ /* sizeof() == 1 */
		"north" : __DIR__"square",
	]));

	setup();
	// 本房有自訂 init()/do_bathe﹐故【不】replace_program(ROOM)（lesson #11）。
}

void init()
{
	::init();
	add_action("do_bathe", ({ "bathe", "泡溫泉", "泡湯" }) );
}

int do_bathe(string arg)
{
	object me = this_player();
	int left, n;

	if( !me ) return 0;

	if( me->query("life_form") == "ghost" )
		return notify_fail("你已是縹緲一縷幽魂﹐這溫湯潤不著你了﹐快去找城隍復活罷。\n");

	if( me->is_busy() )
		return notify_fail("請先用 halt 停止你正在做的事。\n");

	// 泉畔失火般打殺﹐哪能寬衣泡湯。
	if( me->is_fighting() )
		return notify_fail("你正與人交手﹐哪有閒情泡湯﹖\n");

	// 冷卻檢查：set_temp 存下次可用的時間戳（同 fish.c）。
	left = me->query_temp("bathe_cooldown") - time();
	if( left > 0 )
		return notify_fail("你方纔纔泡過﹐渾身正暖著呢﹐且歇上 " + left + " 秒﹐回頭再下池罷。\n");

	// 先設冷卻、進入硬直——浸浴須靜泡一陣方能回神。
	me->set_temp("bathe_cooldown", time() + BATHE_COOLDOWN);
	me->start_busy(BATHE_BUSY);

	message_vision(HIC "\n$N解衣下了溫泉﹐沒入那碧瑩瑩的溫湯裡﹐湯氣裊裊﹐"
		"半晌只覺一身的塵勞乏意都教這暖湯泡得化開了。\n" NOR, me);

	// 回復精氣神：supplement_stat 只補到 heal（受傷上限）為止﹐不超補、不治外傷。
	n  = me->supplement_stat("gin", BATHE_MIN + random(BATHE_RANGE));
	n += me->supplement_stat("kee", BATHE_MIN + random(BATHE_RANGE));
	n += me->supplement_stat("sen", BATHE_MIN + random(BATHE_RANGE));

	if( n > 0 )
		tell_object(me,
			"你在溫湯裡舒舒服服地泡了一回﹐起身時但覺精神一振、氣力回轉﹐"
			"通體說不出的鬆爽。\n");
	else
		tell_object(me,
			"你在溫湯裡泡了一回﹐只覺通體舒泰﹔本就氣神飽滿﹐倒也沒甚好回的了。\n");

	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
