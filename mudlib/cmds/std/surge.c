// surge.c -- 人類種族主動技能「救生」
//
// 人類 (human) 萬能型、什麼都普通，但在性命交關的絕境中，能誘發出驚人的救生
// 力量，回復大量的形體與氣。
// 見 docs/01-世界觀與劇情/03-種族設定.md：人類 主動「陷入絕境時可誘發驚人的
// 救生力量，恢復大量形體和氣」。
//
// 本指令放在 /cmds/std/ ，用 query_race() 鎖死成只有人類能用，其他種族
// 得到「你不會這種本事」（同 spitfire.c / digest.c 的做法──race daemon 的
// setup() 在 daemon context 跑，無法替玩家 add_action，見 content-race-active.md）。
//
// 機制摘要（恢復類，比照 digest.c 的 supplement/heal 用法）：
//   * 鎖定：query_race()=="human"，否則 notify_fail。
//   * 條件：必須身陷「絕境」──當前的氣／形體 (kee) 已掉到上限的 1/3 以下，
//           否則拒絕（「尚未到絕境，使不出這救命的氣力」）。這呼應 doc 的
//           「陷入絕境時」誘發。用 query_stat_current/query_stat_maximum 讀
//           當前值與上限（見 feature/statistic.c:71/77）。
//   * 恢復：氣／形體 (kee) 為主、精 (gin) 為輔 ── supplement_stat 補大量
//           current 到 heal/max 上限為止（見 feature/statistic.c:264）；
//           另以 heal_stat 小幅回填 kee 的可恢復上限（見 feature/statistic.c:293）。
//   * 冷卻：set_temp("surge_cooldown", time()+N) + time() 判定。絕境救命之力
//           不可常恃，故冷卻較長（同 spitfire/devour 的 30s 以上）。
//   * 硬直：start_busy。

#include <ansi.h>

inherit F_CLEAN_UP;

// 冷卻秒數、絕境門檻與回復量，集中在此方便調整平衡。
#define SURGE_COOLDOWN      120     // 兩次救生之間的冷卻秒數 (救命之力不可常恃)
#define SURGE_THRESHOLD     3       // 絕境門檻：當前 kee < 上限 / 3 才可施放
#define SURGE_KEE_HEAL      80      // 每次救生回復的氣／形體 (current，大量)
#define SURGE_KEE_MEND      15      // 每次救生回填的氣可恢復上限 (heal)
#define SURGE_GIN_HEAL      40      // 每次救生回復的精 (輔)
#define SURGE_BUSY          2       // 救生後的硬直 (heart beat 數)

void do_surge(object me);

private void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    int left, cur, max;

    // 只有人類會在絕境中誘發救生之力，其他種族不會這種本事。
    if( me->query_race() != "human" )
        return notify_fail("你不會這種本事。\n");

    if( me->query("life_form") == "ghost" )
        return notify_fail("人死了就一了百了, 快去找城隍復活吧!!\n");

    if( me->is_busy() )
        return notify_fail("請先用 halt 停止你正在做的事。\n");

    // 冷卻檢查：set_temp 存下次可用的時間戳。
    left = me->query_temp("surge_cooldown") - time();
    if( left > 0 )
        return notify_fail("這救命的氣力剛用過，一時再難激發，還得撐上 " + left + " 秒。\n");

    // 絕境判定：當前的氣／形體 (kee) 須掉到上限的 1/3 以下，方能誘發救生之力。
    cur = me->query_stat_current("kee");
    max = me->query_stat_maximum("kee");
    if( max <= 0 || cur >= max / SURGE_THRESHOLD )
        return notify_fail("你尚未到絕境，使不出這救命的氣力。\n");

    do_surge(me);
    return 1;
}

void do_surge(object me)
{
    int healed;

    // 再次確認狀態（do_surge 與 main 之間若有變化）。
    if( !me ) return;

    // 先設冷卻、進入硬直。
    me->set_temp("surge_cooldown", time() + SURGE_COOLDOWN);
    me->start_busy(SURGE_BUSY);

    message_vision(HIY "\n$N眼見命在旦夕，猛然咬牙，週身氣血霎時如怒潮般翻湧而起！\n" NOR,
        me);

    // 先小幅回填氣的可恢復上限，再大量補回當前的氣與精。
    me->heal_stat("kee", SURGE_KEE_MEND);
    healed  = me->supplement_stat("kee", SURGE_KEE_HEAL);
    healed += me->supplement_stat("gin", SURGE_GIN_HEAL);

    if( healed > 0 )
        tell_object(me, HIY "一股求生的蠻力自丹田暴湧而出，撐住了你將傾的身子，形體與氣力大為回復！\n" NOR);
    else
        tell_object(me, "你拼盡全力激發救生之氣，狀態卻已無從再補。\n");
}

int help(object me)
{
    write(@HELP
指令格式：surge   (救生)

人類一族雖樣樣稀鬆平常，卻能在性命交關的絕境之中，激發出驚人的求生力量，
回復大量的形體與氣。

唯有當你的氣力／形體已危殆到極處（掉到上限的三分之一以下），方能誘發這股
救生之力；尚未到絕境時是使不出來的。這股力量耗損極大，用過之後須得歇上好
一陣子才能再次激發，切莫倚為常技。

只有人類種族能使用這項本事。
HELP
    );
    return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
