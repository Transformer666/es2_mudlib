// 怒氣訣 aggressive -- 振武軍營「怒濤先鋒」進階(二轉)所授的內功(基底 FORCE)
//
// docs 載振武軍營統領一脈有「怒氣 aggressive(殺業 1000、berserk 70)：每次消 1 殺業
// 暫提膽臂攻」(見 docs/03-門派與武功/06-軍人-振武大內.md §進階-軍隊統領)。本檔將其
// 實作為一門內功心法(force)﹐使弟子戰鬥時力道能隨內功成長﹐並借 FORCE(/std/force.c)
// 提供的打坐修煉 + valid_enable 共用機制﹔本檔只註冊心法名、登錄中文名、並 override
// cultivate_msg() 提供怒濤先鋒自家的打坐氣象。
//
// docs 將 aggressive 列為「怒氣」狀態(消殺業暫提膽臂攻)﹐屬殺業計分驅動的主動 buff。
// 本檔把它做成隨修為成長的振武內功(force 槽吐納運功供戰鬥 force_bonus 取用)﹐並在
// 此之上 override exert_function 補上 docs L42 載明的「怒氣」一式：消 1 殺業暫提膽臂攻。
//
// 字典 data/chinese.o 查無 "aggressive" key﹐以 CHINESE_D->add_translate() 自行登錄
// 中文名「怒氣訣」。
//
// === 怒氣一式(docs/03-門派與武功/06-軍人-振武大內.md L42) ===
// 「怒氣 aggressive(殺業 1000、berserk 70)：每次消 1 殺業暫提膽臂攻」。膽=cor(膽識)、
// 臂=str(膂力)、攻=apply/attack(攻擊技巧﹐戰鬥迴圈讀 feature/char/combat.c:72)。
//   觸發：exert rage(或 exert 怒氣)。(注意不可用 "aggressive" 為 func 名﹐否則會被
//         FORCE 基底認作「exert <已掛上的內功名>」而落去打坐修煉﹐見 std/force.c L86。)
//   門檻：殺業 >= 1000、本門內功(berserk/aggressive)火候 >= 70(docs)。
//   消耗：每次施展 gain_score("kill karma", -1) 扣 1 殺業。
//   效果：暫時 add_temp("apply/cor"/"apply/str"/"apply/attack", N)﹐call_out 到期後
//         以 add_temp(-N) 復原。完全鏡 daemon/skill/strategy.c::do_wis 與
//         cmds/std/wardance.c 之 add_temp + call_out -N 模型(不可 delete_temp﹐以保住
//         其他來源的同鍵加成)。
//
// 殺業軸 key(grep 全 mudlib 查無既有殺業/kills score key﹐docs 02-遊戲系統與機制/
//   04-業力與聲望.md L55 載其英文 gloss 為「kill karma」)：比照既有英文 score 軸
//   ("military service"/"martial fame"/"negative fame"﹐見 daemon/class/*.c)﹐
//   本檔取 SCORE_KILL_KARMA = "kill karma"。query_score / gain_score 走
//   feature/char/score.c(query("score/"+course) / add("score/"+course, xp))。
//
// runtime 鐵則：本式不涉 ::die()/destruct()(#10)、不 replace_program(#11)﹔為內功
// daemon(inherit FORCE)﹐非 F_VILLAGER NPC﹐不 include <weapon.h>。

#include <ansi.h>

inherit FORCE;

// === 怒氣一式的門檻/消耗/效果參數(數值依 docs﹐未明者取合理可驗值)。集中於此便於調校。===
#define SCORE_KILL_KARMA    "kills"  // 殺業軸 key(=chard.c:310 gain_score("kills",1)、data/chinese.o "score of kills":"殺業"；原誤作 "kill karma" 不存在→閘恆 0)。
#define AG_MIN_KARMA        1000     // 怒氣門檻：殺業下限(docs L42)。
#define AG_MIN_FORCE        70       // 怒氣門檻：本門內功火候下限(docs「berserk 70」)。
#define AG_KARMA_COST       1        // 每次施展所消殺業(docs「每次消 1 殺業」)。

#define AG_BUFF_COR         3        // 怒氣：膽識(apply/cor)加成。
#define AG_BUFF_STR         3        // 怒氣：膂力(apply/str)加成。
#define AG_BUFF_ATK         15       // 怒氣：攻擊技巧(apply/attack)加成。
#define AG_DURATION         30       // 怒氣：持續秒數(call_out 以秒計)。

// 前置宣告(lesson #12：自訂函式一律先前置宣告﹐免「定義前引用」編譯 Undefined
//   function﹐進而導致 daemon lazy-load 靜默失敗、exert 指令靜默回 0)。
varargs int exert_function(object me, string func, object target);
int ag_rage(object me);
void ag_end_rage(object me);

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("aggressive");
	// 自行登錄中文名﹐字典查無此 key﹐使 enable / skills 等顯示「怒氣訣」而非英文代號。
	CHINESE_D->add_translate("aggressive", "怒氣訣");
	setup();
}

// 怒濤先鋒打坐運功時所現的內功氣象。
string cultivate_msg()
{
	return HIR "$N咬牙瞋目﹐緩緩運轉怒氣訣﹐周身似有一股暴烈的殺氣自丹田奔湧而上﹐"
	           "如怒濤拍岸、如烈火焚膛﹐膽氣與臂力俱隨之鼓盪不息。\n" NOR;
}

// ── 怒氣 rage：消 1 殺業﹐暫提膽識(cor)、膂力(str)、攻擊技巧(apply/attack)。docs L42 ──
// add_temp buff + call_out -N 復原﹐完全鏡 daemon/skill/strategy.c::do_wis 與
// cmds/std/wardance.c(用 add_temp(-N) 而非 delete_temp﹐保住其他來源的同鍵加成)。
// 膽識 apply/cor、膂力 apply/str 由 query_attr 讀(feature/attribute.c:29)﹐攻擊技巧
// apply/attack 由戰鬥迴圈讀(feature/char/combat.c:72)。
int
ag_rage(object me)
{
	if( !objectp(me) ) return 0;

	// 門檻：殺業須達 docs 載明的 1000。
	if( (int)me->query_score(SCORE_KILL_KARMA) < AG_MIN_KARMA )
		return notify_fail(sprintf(
			"你殺業未足(需殺業 %d)﹐這股嗜血怒氣激不起來。\n", AG_MIN_KARMA));

	// 門檻：本門內功火候須達 docs 載明的 70。
	if( me->query_skill("berserk", 1) < AG_MIN_FORCE )
		return notify_fail(sprintf(
			"你狂擊亂鬥之法火候未到(需 berserk %d)﹐運不起這股暴烈怒氣。\n", AG_MIN_FORCE));

	// 怒氣 buff 尚在身上時不可重複施展(避免無限延長)。
	if( me->query_temp("aggressive_rage_active") )
		return notify_fail("你周身殺氣正酣﹐這股暴怒尚未消退。\n");

	// 消殺業：gain_score 加負值即扣(見 feature/char/score.c::gain_score)。
	me->gain_score(SCORE_KILL_KARMA, -AG_KARMA_COST);

	me->set_temp("aggressive_rage_active", 1);
	me->add_temp("apply/cor", AG_BUFF_COR);
	me->add_temp("apply/str", AG_BUFF_STR);
	me->add_temp("apply/attack", AG_BUFF_ATK);
	me->set_temp("aggressive_rage_callout",
		call_out("ag_end_rage", AG_DURATION, me));

	message_vision(HIR
		"$N咬牙瞋目﹐運轉怒氣訣激起滿腔殺業﹐周身血氣如怒濤暴漲﹐"
		"膽氣臂力俱盛﹐殺招更見凌厲﹗\n" NOR, me);
	tell_object(me, sprintf(HIR
		"你激起怒氣﹐膽識、膂力與攻擊俱有起色。(消殺業 %d﹐持續 %d 秒)\n" NOR,
		AG_KARMA_COST, AG_DURATION));
	return 1;
}

// 怒氣 buff 到期：把先前加的量「減回去」並清旗標。用 add_temp(-N)﹐不可 delete_temp。
void
ag_end_rage(object me)
{
	if( !objectp(me) ) return;
	me->add_temp("apply/cor", -AG_BUFF_COR);
	me->add_temp("apply/str", -AG_BUFF_STR);
	me->add_temp("apply/attack", -AG_BUFF_ATK);
	me->delete_temp("aggressive_rage_active");
	me->delete_temp("aggressive_rage_callout");
	tell_object(me, NOR "你那股暴烈的怒氣漸漸平息了下來。\n");
}

// exert rage(或 exert 怒氣) -- 怒氣一式：消 1 殺業暫提膽臂攻(docs L42)。
// 其餘 func(含 "aggressive" 本身打坐修煉)落回 FORCE 基底。注意不可用 "aggressive"
// 為觸發 func﹐否則會被 FORCE 基底認作「exert <已掛上的內功名>」而落去打坐。
varargs int exert_function(object me, string func, object target)
{
	if( !objectp(me) ) me = this_player();
	if( !objectp(me) ) return 0;

	switch( func ) {
	case "rage": case "怒氣": return ag_rage(me);
	}

	return ::exert_function(me, func, target);
}

// vim: set ts=4 sw=4 syntax=lpc
