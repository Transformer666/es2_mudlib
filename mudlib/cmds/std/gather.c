// gather.c -- 巫首種族主動技能「採靈氣」
//
// 巫首 (malik) 法系神格、低物理，能盤坐採納天地靈氣，回復大量的神 (sen)。
// 見 docs/01-世界觀與劇情/03-種族設定.md：巫首 主動「採納天地靈氣恢復大量神」。
//
// 本指令放在 /cmds/std/ ，用 query_race() 鎖死成只有巫首能用，其他種族
// 得到「你不會這種本事」（同 spitfire.c / digest.c 的做法──race daemon 的
// setup() 在 daemon context 跑，無法替玩家 add_action，見 content-race-active.md）。
//
// 機制摘要（恢復類，比照 digest.c 的 supplement/heal 用法）：
//   * 鎖定：query_race()=="malik"，否則 notify_fail。
//   * 無對象：盤坐自我採氣，不需目標、不需在戰鬥中（戰鬥中亦無法靜心，見下）。
//   * 恢復：神 (sen) ── supplement_stat 補大量 current 到 heal/max 上限為止
//           （見 feature/statistic.c:264，回傳實際補回量）；另以 heal_stat
//           小幅回填神的可恢復上限（見 feature/statistic.c:293）。
//   * 冷卻：set_temp("gather_cooldown", time()+N) + time() 判定（同 digest）。
//   * 硬直：start_busy（盤坐運氣需要時間）。

#include <ansi.h>

inherit F_CLEAN_UP;

// 冷卻秒數與回復量，集中在此方便調整平衡。
#define GATHER_COOLDOWN     30      // 兩次採氣之間的冷卻秒數
#define GATHER_SEN_HEAL     60      // 每次採氣回復的神 (current，大量)
#define GATHER_SEN_MEND     10      // 每次採氣回填的神可恢復上限 (heal)
#define GATHER_BUSY         3       // 採氣後的硬直 (heart beat 數，盤坐較久)

void do_gather(object me);

private void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    int left;

    // 只有巫首會採納天地靈氣，其他種族不會這種本事。
    if( me->query_race() != "malik" )
        return notify_fail("你不會這種本事。\n");

    if( me->query("life_form") == "ghost" )
        return notify_fail("人死了就一了百了, 快去找城隍復活吧!!\n");

    if( me->is_busy() )
        return notify_fail("請先用 halt 停止你正在做的事。\n");

    // 交手之際心神俱亂，無法靜心採氣。
    if( me->is_fighting() )
        return notify_fail("你正與人交手，心神俱亂，靜不下心來採氣。\n");

    // 冷卻檢查：set_temp 存下次可用的時間戳。
    left = me->query_temp("gather_cooldown") - time();
    if( left > 0 )
        return notify_fail("天地靈氣尚未復聚，還得再等 " + left + " 秒方能再採。\n");

    // 神已滿，無需採氣。
    if( me->query_stat("sen") >= me->query_stat_maximum("sen") )
        return notify_fail("你神思澄明，已無採氣的必要。\n");

    do_gather(me);
    return 1;
}

void do_gather(object me)
{
    int healed;

    // 再次確認狀態（do_gather 與 main 之間若有變化）。
    if( !me ) return;

    // 先設冷卻、進入硬直。
    me->set_temp("gather_cooldown", time() + GATHER_COOLDOWN);
    me->start_busy(GATHER_BUSY);

    message_vision(HIC "\n$N盤膝坐定，雙目微闔，緩緩採納週遭的天地靈氣。\n" NOR,
        me);

    // 先小幅回填神的可恢復上限，再大量補回當前的神。
    me->heal_stat("sen", GATHER_SEN_MEND);
    healed = me->supplement_stat("sen", GATHER_SEN_HEAL);

    if( healed > 0 )
        tell_object(me, HIC "一道清靈之氣自百會灌入，遊走週身，你只覺神思大暢，精神為之一振。\n" NOR);
    else
        tell_object(me, "你採了半天靈氣，神思卻已無從再補。\n");
}

int help(object me)
{
    write(@HELP
指令格式：gather   (採靈氣)

巫首一族法系神格，與天地靈氣相通，能盤膝靜坐、採納週遭的天地靈氣，回復
大量的神。

採氣需盤坐靜心，故須先停下手邊的事，與人交手之際亦無法施展；採過之後天地
靈氣需要時間重新復聚，不能連續施放。神思澄明時無需採氣。

只有巫首種族能使用這項本事。
HELP
    );
    return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
