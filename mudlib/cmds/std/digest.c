// digest.c -- 無腸種族主動技能「化水」
//
// 無腸 (woochan) 一族體內貯水、不需食物（被動：防+5、守勢+25、不需食物）。
// 見 docs/01-世界觀與劇情/03-種族設定.md：無腸 主動「消化體內的水氣恢復狀態」。
//
// 本指令放在 /cmds/std/ ，用 query_race() 鎖死成只有無腸能用，其他種族
// 得到「你不會這種本事」（同 spitfire.c 的做法）。
//
// 機制摘要（恢復類）：
//   * 鎖定：query_race()=="woochan"，否則 notify_fail。
//   * 燃料：飲水 (water) ── 用 query_stat("water")/consume_stat("water", n)。
//           water 是正規 stat（見 feature/drink.c、feature/statistic.c）。
//   * 恢復：神 (sen) 與 氣 (kee) ── supplement_stat（見 feature/statistic.c:264，
//           補到 heal/max 上限為止，回傳實際補回量）。
//   * 冷卻：set_temp("digest_cooldown", time()+N) + time() 判定。
//   * 不需在戰鬥中即可施放（自我回復），但會有短暫硬直 start_busy。

#include <ansi.h>

inherit F_CLEAN_UP;

// 冷卻秒數、耗水量與回復量，集中在此方便調整平衡。
#define DIGEST_COOLDOWN     20      // 兩次化水之間的冷卻秒數
#define DIGEST_WATER_COST   30      // 每次化水消耗的飲水
#define DIGEST_SEN_HEAL     20      // 每次化水回復的神
#define DIGEST_KEE_HEAL     15      // 每次化水回復的氣
#define DIGEST_BUSY         1       // 化水後的硬直 (heart beat 數)

void do_digest(object me);

private void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    int left;

    // 只有無腸會消化水氣回復，其他種族不會這種本事。
    if( me->query_race() != "woochan" )
        return notify_fail("你不會這種本事。\n");

    if( me->query("life_form") == "ghost" )
        return notify_fail("人死了就一了百了, 快去找城隍復活吧!!\n");

    if( me->is_busy() )
        return notify_fail("請先用 halt 停止你正在做的事。\n");

    // 冷卻檢查：set_temp 存下次可用的時間戳。
    left = me->query_temp("digest_cooldown") - time();
    if( left > 0 )
        return notify_fail("你體內的水氣尚未蓄足，還得再等 " + left + " 秒。\n");

    // 飲水不足，無水可化。
    if( me->query_stat("water") < DIGEST_WATER_COST )
        return notify_fail("你體內水氣不足，化不出什麼來。\n");

    // 神與氣都已滿，無需化水。
    if( me->query_stat("sen") >= me->query_stat_maximum("sen")
    &&  me->query_stat("kee") >= me->query_stat_maximum("kee") )
        return notify_fail("你神完氣足，沒有化水的必要。\n");

    do_digest(me);
    return 1;
}

void do_digest(object me)
{
    int healed;

    // 再次確認狀態（do_digest 與 main 之間若有變化）。
    if( !me || me->query_stat("water") < DIGEST_WATER_COST ) return;

    // 先耗水、設冷卻、進入硬直。
    me->consume_stat("water", DIGEST_WATER_COST);
    me->set_temp("digest_cooldown", time() + DIGEST_COOLDOWN);
    me->start_busy(DIGEST_BUSY);

    // 消化水氣，回復神與氣；supplement_stat 補到上限為止，回傳實際補回量。
    healed = me->supplement_stat("sen", DIGEST_SEN_HEAL);
    healed += me->supplement_stat("kee", DIGEST_KEE_HEAL);

    message_vision(HIC "\n$N閉目凝神，緩緩運轉體內水氣，將其層層消化開來。\n" NOR,
        me);

    if( healed > 0 )
        tell_object(me, HIC "一股清涼的水氣化入週身經脈，你只覺神清氣爽，狀態回復了不少。\n" NOR);
    else
        tell_object(me, "你運了半天水氣，狀態卻已無從再補。\n");
}

int help(object me)
{
    write(@HELP
指令格式：digest   (化水)

無腸一族體內貯水、不假外食，能將體內的水氣緩緩消化運轉，化為精神與氣力。

每次化水都會耗去你體內不少飲水，藉此回復神與氣；水氣需要時間重新蓄積，不
能連續施放。神完氣足時無需化水。

只有無腸種族能使用這項本事。
HELP
    );
    return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
