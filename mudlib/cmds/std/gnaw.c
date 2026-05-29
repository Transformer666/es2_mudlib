// gnaw.c -- 黑齒種族主動技能「啃噬」
//
// 黑齒 (blackteeth) 一族生著一口堅硬黑牙，可啃噬咀嚼以調動體內氣血、回復狀態。
// 見 docs/01-世界觀與劇情/03-種族設定.md：黑齒 主動「吞食物品恢復狀態」，
// memory/patterns/content-race-active.md 記其「恢復 kee、伴隨咬齧的耗損」。
//
// 本指令放在 /cmds/std/ ，用 query_race() 鎖死成只有黑齒能用，其他種族
// 得到「你不會這種本事」（同 spitfire.c 的做法）。
//
// 機制摘要（恢復類，比照 berserk.c 的 supplement/consume 用法）：
//   * 鎖定：query_race()=="blackteeth"，否則 notify_fail。
//   * 恢復：氣 (kee) ── 用 supplement_stat("kee", n)（見 feature/statistic.c:264，
//           會把 current 補到 heal/max 上限為止，回傳實際補回量）。
//   * 代價／downside：消耗精 (gin)；並對自身上限值小幅 damage_stat("kee", n)
//           （咬齧的耗損，當下回復、但氣的可恢復上限略降，需休養回填）。
//   * 冷卻：set_temp("gnaw_cooldown", time()+N) + time() 判定。
//   * 不需在戰鬥中即可施放（自我回復），但會有短暫硬直 start_busy。

#include <ansi.h>

inherit F_CLEAN_UP;

// 冷卻秒數、回復／消耗量，集中在此方便調整平衡。
#define GNAW_COOLDOWN       20      // 兩次啃噬之間的冷卻秒數
#define GNAW_GIN_COST       8       // 每次啃噬消耗的精
#define GNAW_KEE_HEAL       25      // 每次啃噬回復的氣
#define GNAW_WEAR           3       // 咬齧造成的氣上限耗損（downside）
#define GNAW_BUSY           1       // 啃噬後的硬直 (heart beat 數)

void do_gnaw(object me);

private void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    int left;

    // 只有黑齒會啃噬回氣，其他種族不會這種本事。
    if( me->query_race() != "blackteeth" )
        return notify_fail("你不會這種本事。\n");

    if( me->query("life_form") == "ghost" )
        return notify_fail("人死了就一了百了, 快去找城隍復活吧!!\n");

    if( me->is_busy() )
        return notify_fail("請先用 halt 停止你正在做的事。\n");

    // 冷卻檢查：set_temp 存下次可用的時間戳。
    left = me->query_temp("gnaw_cooldown") - time();
    if( left > 0 )
        return notify_fail("你齒間還在隱隱發酸，得再歇 " + left + " 秒才能再啃。\n");

    // 精不足，沒有本錢調動氣血。
    if( me->query_stat("gin") < GNAW_GIN_COST )
        return notify_fail("你的精不夠，啃不動了。\n");

    // 氣已滿，無需啃噬。
    if( me->query_stat("kee") >= me->query_stat_maximum("kee") )
        return notify_fail("你氣力充沛，沒有啃噬的必要。\n");

    do_gnaw(me);
    return 1;
}

void do_gnaw(object me)
{
    int healed;

    // 再次確認狀態（do_gnaw 與 main 之間若有變化）。
    if( !me || me->query_stat("gin") < GNAW_GIN_COST ) return;

    // 先付代價、設冷卻、進入硬直。
    me->consume_stat("gin", GNAW_GIN_COST);
    me->set_temp("gnaw_cooldown", time() + GNAW_COOLDOWN);
    me->start_busy(GNAW_BUSY);

    // 咬齧的耗損：氣的可恢復上限 (heal 值) 略降，當下雖回氣，但需休養回填。
    me->damage_stat("kee", GNAW_WEAR);

    // 啃噬回氣：supplement_stat 會補到 heal/max 上限為止，回傳實際補回量。
    healed = me->supplement_stat("kee", GNAW_KEE_HEAL);

    message_vision(HIG "\n$N齜出一口黑牙，咯吱咯吱地用力啃噬咀嚼起來。\n" NOR,
        me);

    if( healed > 0 )
        tell_object(me, HIG "一股氣力自齒間泛起，你只覺週身一振，回復了些許氣力。\n" NOR);
    else
        tell_object(me, "你啃了半天，卻沒能調動起多少氣力。\n");
}

int help(object me)
{
    write(@HELP
指令格式：gnaw   (啃噬)

黑齒一族生著一口堅硬黑牙，能藉啃噬咀嚼來調動體內氣血，回復氣力。

每次啃噬都會消耗你的精，且劇烈的咬齧會略損你氣力的可恢復上限（需稍加休養
方能回填），齒間也需要時間平復，不能連續施放。氣力已滿時無需啃噬。

只有黑齒種族能使用這項本事。
HELP
    );
    return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
