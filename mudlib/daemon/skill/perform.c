// 絕招系統 perform -- 戰鬥「絕招(perform)」的累點與施放總機(中央 perform daemon)
//
// 來歷(docs/03-門派與武功/04-書生-步玄玄天.md §9/2 平衡 L100-104)：書生(及全
// MUD 各門派)的「絕招」需以 perform 指令於戰鬥中手動施放﹔docs §平衡 L101 明載
// 「perform >6 點 delay 2」——即一次施放消耗逾 6 點絕招點者﹐施招者自身硬直
// (delay)2 個 heart_beat。docs 對各絕招效果多為「定性」描述(步玄七絕「不可防禦
// 傷害」、玄天劍訣「定單一敵人」、步玄雙龍劍氣「必兩次命中」、棄徒/使者「無視防禦/
// 定人/連擊」…見各 daemon/skill/*.c 之 TODO 註)﹐未給確切數值。
//
// === 本檔在 docs 留白處所取的「合理可驗預設」(全部集中於下方 #define﹐標明為預設) ===
// docs 只給「>6 點 delay 2」此一硬數字﹐其餘(累點速率/上限、各絕招門檻、無視防禦
// 的傷害倍率、定人秒數、連擊段數)docs 皆未明定﹐本檔依授權取「合理且可在 MUD 內
// EFFECT 驗證」的預設值﹐供日後平衡微調。所有預設皆以 [預設] 標註。
//
// === 累點機制(每出招/受擊 +1﹐存 temp) ===
// docs「累積七點後發動」之語意 = 戰鬥中持續累積絕招點。為不更動 /adm(combatd.c﹐
// 鐵則 #4 慎改)與 /std(char.c::heart_beat)等系統核心檔﹐本 daemon 自帶一個
// 「每約一回合(2 秒) +1」的 call_out 累點迴圈(player 在戰鬥中時)﹐由 perform 指令
// (cmds/std/perform.c)首次施招/查點時 lazily 啟動(start_accumulate)。每 tick
// 視同「出招/受擊」各 +1(故戰鬥中每回合 +2﹐近似 docs「出招+受擊」雙來源)﹐點數
// 存於 query_temp(PERFORM_POINT_KEY)﹐上限 PERFORM_POINT_MAX。脫離戰鬥即停止累點。
//
// === 派發結構(鏡 cmds/std/exert.c → daemon force / cmds/std/tactic.c → strategy.c) ===
// 玩家鍵入 `perform <技能:絕招> [on <目標>]`。cmds/std/perform.c::main 解析後呼
// PERFORM_D->perform_action(me, 技能名, 絕招名, target)。本檔依絕招名分派至三種
// 通用絕招效果(無視防禦 ignoredef / 定人 hold / 連擊 combo)﹐查點達門檻則扣點施放﹐
// 扣逾 6 點者 self start_busy(2)(docs L101)。各門派招式 daemon 日後可覆寫
// perform_action 以接自家專屬絕招﹔未覆寫者一律落到本通用總機。
//
// 機制對齊(皆為已驗範式)：
//   * 無視防禦「必中高傷」：直接 victim->receive_damage(dmg, me, me)(繞過 defend/
//     absorb﹐見 feature/char/combat.c::receive_damage)﹐dmg 依攻擊力道折算(鏡
//     combatd.c::fight 之 strength 流程﹐但不給 victim 防禦機會)。
//   * 定人 hold：target->start_busy(N)(鏡 std/magic.c::magic_delay、strategy.c::
//     do_charge 之 target->start_busy)。
//   * 連擊 combo：me->attack(target) 連呼 N 次(每次走玩家慣用武器/拳腳的招式表﹐
//     見 feature/char/attack.c::attack)。
//   * 自身 delay：me->start_busy(2)(鏡 strategy.c 各 do_* 之 me->start_busy)。
//   * 累點：set_temp/query_temp(feature/dbase.c)﹐call_out 迴圈(鏡 royal_force.c/
//     strategy.c 之 call_out 復原模型)。
//
// runtime 鐵則：本檔不涉 ::die()/destruct()(#10)、不 replace_program(#11)﹔為技能
// daemon(inherit SKILL﹐非 NPC)﹐不 include <weapon.h>(無 nomask 衝突)。

#include <ansi.h>

inherit SKILL;

// ── 累點參數(docs 未明定累點速率/上限﹐取合理可驗預設)。──────────────────────
#define PERFORM_POINT_KEY   "perform_point"     // 絕招點存放的 temp key。
#define PERFORM_TICKING_KEY "perform_ticking"   // 累點迴圈進行中的旗標 temp key。
#define PERFORM_POINT_MAX   12      // [預設] 絕招點上限(docs 各絕招門檻 ≤7﹐留餘裕)。
#define PERFORM_TICK_SEC    2       // [預設] 累點 tick 秒數(≈一個 heart_beat 回合)。
#define PERFORM_GAIN_PER_TICK 2     // [預設] 每 tick +2(視同該回合「出招+受擊」各 +1)。

// ── 各通用絕招的門檻與加成(docs 只給定性描述與「>6 點 delay 2」﹐其餘取預設)。──
// 三式通用絕招﹐玩家以 `perform <技能>:<以下絕招名>` 施放﹕
#define IGNOREDEF_NAME      "ignoredef"  // 無視防禦：必中、繞過拆招/閃躲、高傷一擊。
#define IGNOREDEF_COST      4       // [預設] 無視防禦門檻/耗點(≤6﹐不觸發 delay 2)。
#define IGNOREDEF_DMGDIV    2000    // [預設] 無視防禦傷害除數(力道/此值=傷害﹐見 do_ignoredef)。
                                    //   約使起步玩家單擊 ~25-35、頂尖 ~60-70(高於普攻而非秒殺)。

#define HOLD_NAME           "hold"       // 定人：令目標短暫無法行動(start_busy)。
#define HOLD_COST           5       // [預設] 定人門檻/耗點(≤6﹐不觸發 delay 2)。
#define HOLD_BUSY           2       // [預設] 定人硬直回合數(target start_busy N)。

#define COMBO_NAME          "combo"      // 連擊：對目標連續追擊數次。
#define COMBO_COST          7       // [預設] 連擊門檻/耗點(>6﹐觸發 self delay 2)。
#define COMBO_HITS          3       // [預設] 連擊追擊次數(額外 me->attack(target) N 次)。

// docs L101 唯一硬數字：一次施放耗點 > DELAY_THRESHOLD 者﹐施招者 self delay。
#define DELAY_THRESHOLD     6       // docs：「perform >6 點 delay 2」。
#define SELF_DELAY          2       // docs：delay 2 個 heart_beat。

// ── 前置宣告(lesson #12)：以下函式於定義前先被 perform_action 之 switch 與
//    accumulate 迴圈引用﹐LPC 須先宣告否則「Undefined function」編譯失敗(已驗踩坑)。
int query_perform_point(object me);
void start_accumulate(object me);
void accumulate(object me);
private int spend_and_delay(object me, int cost);
private int do_ignoredef(object me, object target);
private int do_hold(object me, object target);
private int do_combo(object me, object target);

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("perform");
    // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
    CHINESE_D->add_translate("perform", "絕招");
    setup();
}

// perform 為主動施放的戰鬥絕招總機﹐不佔 enable(內功/武功)槽﹐故 valid_enable 回 0。
int
valid_enable(string usage)
{
    return 0;
}

// ── 累點：查詢目前絕招點 ──────────────────────────────────────────────────
int
query_perform_point(object me)
{
    if( !objectp(me) ) return 0;
    return me->query_temp(PERFORM_POINT_KEY);
}

// ── 累點：啟動累點迴圈(lazily﹐由 perform 指令呼叫)。已在跑則不重複啟動。──────
void
start_accumulate(object me)
{
    if( !objectp(me) ) return;
    if( me->query_temp(PERFORM_TICKING_KEY) ) return;  // 已在累點。
    me->set_temp(PERFORM_TICKING_KEY, 1);
    call_out("accumulate", PERFORM_TICK_SEC, me);
}

// ── 累點：每 tick +PERFORM_GAIN_PER_TICK(出招/受擊各 +1)﹐封頂 PERFORM_POINT_MAX。
//    僅在 me 仍在戰鬥時持續﹔脫戰即停(清旗標﹐下次 perform 再 lazily 重啟)。──────
void
accumulate(object me)
{
    int pt;

    if( !objectp(me) ) return;

    // 脫離戰鬥(或昏迷/不在)：停止累點﹐清旗標。
    if( !living(me) || !me->is_fighting() ) {
        me->delete_temp(PERFORM_TICKING_KEY);
        return;
    }

    pt = query_perform_point(me) + PERFORM_GAIN_PER_TICK;
    if( pt > PERFORM_POINT_MAX ) pt = PERFORM_POINT_MAX;
    me->set_temp(PERFORM_POINT_KEY, pt);

    // 排下一個 tick。
    call_out("accumulate", PERFORM_TICK_SEC, me);
}

// ── perform_action(me, skill, act, target) ───────────────────────────────
// cmds/std/perform.c 派發至此。skill 為玩家施招所用技能名(僅作訊息/未來擴充用)﹐
// act 為絕招名﹐target 為目標。依 act 分派三式通用絕招﹔不識者落回 notify_fail。
// 回傳非 0 表成功(指令層據此回報)。
varargs int
perform_action(object me, string skill, string act, object target)
{
    if( !objectp(me) ) me = this_player();
    if( !objectp(me) ) return 0;

    // 確保累點迴圈在跑(玩家戰鬥中才會真正累積)。
    start_accumulate(me);

    if( !stringp(act) || act == "" )
        return notify_fail("你要施展哪一招絕招﹖\n");

    // 目標檢查(三式通用絕招皆需目標)。
    if( !objectp(target) || !target->is_character() )
        return notify_fail("你要對誰施展絕招﹖\n");
    if( target == me )
        return notify_fail("你總不能對自己施展絕招罷﹖\n");
    if( environment(target) != environment(me) )
        return notify_fail("這裡並沒有這個目標。\n");

    switch( act ) {
    case IGNOREDEF_NAME: return do_ignoredef(me, target);
    case HOLD_NAME:      return do_hold(me, target);
    case COMBO_NAME:     return do_combo(me, target);
    default:
        return notify_fail("你並不會「" + act + "」這一招絕招。\n"
            "(通用絕招﹕" IGNOREDEF_NAME "(無視防禦)、"
            HOLD_NAME "(定人)、" COMBO_NAME "(連擊))\n");
    }
}

// ── 共用：檢查/扣點﹐並依 docs「>6 點 delay 2」對自身 delay。──────────────────
// 回傳 1 表扣點成功(可施放)﹔0 表點數不足(已 notify_fail)。
private int
spend_and_delay(object me, int cost)
{
    int pt;

    pt = query_perform_point(me);
    if( pt < cost ) {
        notify_fail(sprintf("你的絕招點不足(需 %d﹐現有 %d)﹐再纏鬥幾招蓄勢罷﹗\n",
            cost, pt));
        return 0;
    }

    // 扣點(set_temp 直接覆寫﹐絕招點為本系統獨佔之 temp key﹐無他源加成顧慮)。
    me->set_temp(PERFORM_POINT_KEY, pt - cost);

    // docs L101：一次施放耗點 > 6 者﹐施招者 self delay 2 個 heart_beat。
    if( cost > DELAY_THRESHOLD )
        me->start_busy(SELF_DELAY);

    return 1;
}

// ── ignoredef 無視防禦：必中、繞過拆招/閃躲的高傷一擊。docs 步玄七絕「不可防禦
//    傷害」/古劍門「無視防禦絕招」等之通用版。直接 receive_damage 不給防禦機會。──
private int
do_ignoredef(object me, object target)
{
    int strength, dmg;

    if( !spend_and_delay(me, IGNOREDEF_COST) )
        return 0;

    // 力道折算(鏡 combatd.c::fight 之 query_strength("attack")﹐但不過 defend/absorb)。
    strength = me->query_strength("attack");
    // 高傷一擊：力道 / 除數(IGNOREDEF_DMGDIV 越小傷越高)﹐至少 1。預設值供平衡微調。
    dmg = strength / IGNOREDEF_DMGDIV;
    if( dmg < 1 ) dmg = 1;

    message_vision(HIR
        "$N氣沉丹田﹐一招迅雷不及掩耳的絕殺直取$n要害——這一擊封死了$n所有閃避拆解之機﹗\n"
        NOR, me, target);

    // 必中：直接施加傷害(from=me, attacker=me)﹐繞過 victim 的 defend/absorb。
    target->receive_damage(dmg, me, me);

    tell_object(me, sprintf(HIW
        "你傾盡功力施出無視防禦的絕殺﹗(耗 %d 點絕招點)\n" NOR, IGNOREDEF_COST));
    return 1;
}

// ── hold 定人：令目標短暫無法行動(start_busy)。docs 玄天劍訣「定單一敵人」/使者
//    「定人」等之通用版。鏡 std/magic.c::magic_delay。──────────────────────────
private int
do_hold(object me, object target)
{
    if( !spend_and_delay(me, HOLD_COST) )
        return 0;

    message_vision(HIM
        "$N身形一錯﹐一招絕技點中$n周身大穴﹐$n登時手足一滯﹐動彈不得﹗\n"
        NOR, me, target);

    // 定人：使目標 start_busy 數個 heart_beat(既有 freeze 同機制)。
    target->start_busy(HOLD_BUSY);

    tell_object(me, sprintf(HIW
        "你一招定住了$n﹗(耗 %d 點絕招點)\n" NOR, HOLD_COST));
    tell_object(target, HIR "你被一招絕技定住﹐一時間僵在原地動彈不得﹗\n" NOR);
    return 1;
}

// ── combo 連擊：對目標連續追擊數次。docs 步玄雙龍劍氣「必兩次命中」/狂戰「多段
//    連擊」等之通用版。每次 me->attack(target) 走玩家慣用武器/拳腳的招式表。──────
// 此絕招預設耗 7 點(>6)﹐故 spend_and_delay 會觸發 docs「delay 2」。
private int
do_combo(object me, object target)
{
    int i;

    if( !spend_and_delay(me, COMBO_COST) )
        return 0;

    message_vision(HIY
        "$N足尖一點凌空而起﹐一套絕招連環攻勢如怒濤拍岸﹐招招相銜直罩向$n﹗\n"
        NOR, me, target);

    // 連擊：額外追擊 COMBO_HITS 次(每次都重新走攻擊判定/招式表)。
    // 逐次檢查 target 仍在、仍活、仍同房﹐免在目標已倒下後空打。
    for( i = 0; i < COMBO_HITS; i++ ) {
        if( !objectp(target) || !living(target) ) break;
        if( environment(target) != environment(me) ) break;
        me->attack(target);
    }

    tell_object(me, sprintf(HIW
        "你施出絕招連擊﹐攻勢綿綿不絕﹗(耗 %d 點絕招點﹐隨後微微一頓)\n" NOR,
        COMBO_COST));
    return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
