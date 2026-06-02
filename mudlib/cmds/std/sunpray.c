// sunpray.c -- 人類族（avatar）種族主動技能「太陽神祈禱」
//
// 人類族是人類的萬分之一隱藏變體，萬能而稟賦過人。其主動本事為向太陽神
// 金烏祈禱，承陽光的祝福，回復大量的精、氣、神。
// 見 docs/01-世界觀與劇情/03-種族設定.md：人類族 主動「通過向太陽神祈禱獲得
// 陽光的祝福，恢復大量狀態」；docs/01-世界觀與劇情/01-神話與創世.md：太陽神
// 即元神之神「金烏」。
//
// 本指令放在 /cmds/std/ ，所有人的指令搜尋路徑都包含此目錄，故此處以
// query_race()=="avatar" 把指令鎖死成只有人類族能用；其他種族會得到「你不會
// 這種本事」。這是目前 mudlib 唯一可靠的「種族專屬指令」做法──race daemon 的
// setup() 在 daemon context 執行，無法替玩家 add_action（見 surge.c/spitfire.c
// 的同款註解與 doc/efuns/add_action）。
//
// 機制摘要（恢復類，整體比照人類 救生 surge.c，但無「絕境」前提──祈禱隨時
// 可行，且三維(精/氣/神)俱補）：
//   * 鎖定：query_race()=="avatar"，否則 notify_fail。
//   * 條件：活人方能祈禱（ghost 拒絕）、非硬直中（is_busy 拒絕）。無血量門檻。
//   * 恢復：先以 heal_stat 回填三維的可恢復上限，再以 supplement_stat 大量補回
//           當前值（見 feature/statistic.c:264/293）。
//   * 陽光：以 localtime(time()) 取現實時辰（同 natured.c 的做法），白天
//           (06:00–18:00) 陽光充沛、回復加成；夜晚僅餘暉，回復減半。呼應
//           doc 的「獲得陽光的祝福」。
//   * 冷卻：set_temp("sunpray_cooldown", time()+N) + time() 判定。神恩不可
//           常恃，冷卻較長（比照 surge 的 120s）。
//   * 硬直：start_busy（祈禱需凝神片刻）。

#include <ansi.h>
#include <localtime.h>

inherit F_CLEAN_UP;

// 冷卻秒數、回復量與硬直，集中於此方便調整平衡。
#define SUNPRAY_COOLDOWN    120     // 兩次祈禱之間的冷卻秒數（神恩不可常恃）
#define SUNPRAY_KEE_HEAL    120     // 每次祈禱回復的氣／形體 (current，大量)
#define SUNPRAY_GIN_HEAL    120     // 每次祈禱回復的精 (current，大量)
#define SUNPRAY_SEN_HEAL    120     // 每次祈禱回復的神 (current，大量)
#define SUNPRAY_MEND        25      // 每次祈禱回填三維的可恢復上限 (heal)
#define SUNPRAY_BUSY        2       // 祈禱後的硬直 (heart beat 數)

void do_sunpray(object me, int daylight);

private void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    int left, hour, daylight;

    // 只有人類族（avatar）能向太陽神祈禱，其他種族不會這種本事。
    if( me->query_race() != "avatar" )
        return notify_fail("你不會這種本事。\n");

    if( me->query("life_form") == "ghost" )
        return notify_fail("人死了就一了百了, 快去找城隍復活吧!!\n");

    if( me->is_busy() )
        return notify_fail("請先用 halt 停止你正在做的事。\n");

    // 冷卻檢查：set_temp 存下次可用的時間戳。
    left = me->query_temp("sunpray_cooldown") - time();
    if( left > 0 )
        return notify_fail("你方才已向太陽神祈求過，神恩不可貪得，還得靜候 " + left + " 秒。\n");

    // 陽光判定：白天 06:00–18:00 陽光普照，祈禱效力全開。
    hour = localtime(time())[LT_HOUR];  // 取現實時辰（同 natured.c 的做法）
    daylight = (hour >= 6 && hour < 18);

    do_sunpray(me, daylight);
    return 1;
}

void do_sunpray(object me, int daylight)
{
    int kee, gin, sen, mend, healed;

    // 再次確認狀態（do_sunpray 與 main 之間若有變化）。
    if( !me ) return;

    // 先設冷卻、進入硬直。無論回復多寡都只付一次代價。
    me->set_temp("sunpray_cooldown", time() + SUNPRAY_COOLDOWN);
    me->start_busy(SUNPRAY_BUSY);

    kee  = SUNPRAY_KEE_HEAL;
    gin  = SUNPRAY_GIN_HEAL;
    sen  = SUNPRAY_SEN_HEAL;
    mend = SUNPRAY_MEND;

    if( daylight ) {
        message_vision(HIY "\n$N朝天合十，向太陽神金烏默默祈禱，霎時一道金燦燦的陽光自天際傾灑而下，將$N週身裹入暖意之中！\n" NOR,
            me);
    } else {
        // 入夜陽光隱沒，僅餘天光餘暉，回復減半。
        kee  /= 2;
        gin  /= 2;
        sen  /= 2;
        mend /= 2;
        message_vision(HIW "\n$N朝天合十，向太陽神金烏默默祈禱，然而夜幕低垂，金烏已歸西山，只餘一線微弱的天光垂照$N。\n" NOR,
            me);
    }

    // 先小幅回填三維的可恢復上限，再大量補回當前的精、氣、神。
    me->heal_stat("kee", mend);
    me->heal_stat("gin", mend);
    me->heal_stat("sen", mend);

    healed  = me->supplement_stat("kee", kee);
    healed += me->supplement_stat("gin", gin);
    healed += me->supplement_stat("sen", sen);

    if( healed > 0 )
        tell_object(me, HIY "陽光的祝福流遍你的四肢百骸，精、氣、神為之一振，大為回復！\n" NOR);
    else
        tell_object(me, "你虔誠地向太陽神祈禱，然而此刻精氣神俱滿，已無從再補。\n");
}

int help(object me)
{
    write(@HELP
指令格式：sunpray   (太陽神祈禱)

人類族乃人類萬分之一的稟賦異種，萬般皆能，更得太陽神金烏的眷顧。施展此本事，
向太陽神祈禱，承陽光的祝福，可一舉回復大量的精、氣、神。

白晝之時陽光普照，祈禱的效力最為宏大；入夜後金烏歸隱，僅餘天光餘暉，回復之效
將大為減損。神恩不可貪得，每次祈禱之後須得靜候一陣，方能再次祈求。

只有人類族（avatar）能使用這項本事。
HELP
    );
    return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
