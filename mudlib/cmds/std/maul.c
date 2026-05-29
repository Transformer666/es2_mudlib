// maul.c -- 阿修羅種族主動技能「啖屍」
//
// 阿修羅 (ashura) 高攻擊、可食屍體，能撕咬倒地的屍體，藉血肉回復自身狀態。
// 見 docs/01-世界觀與劇情/03-種族設定.md：阿修羅 主動「吞食屍體恢復狀態」。
//
// 本指令放在 /cmds/std/ ，用 query_race() 鎖死成只有阿修羅能用，其他種族
// 得到「你不會這種本事」（同 spitfire.c / devour.c 的做法──race daemon 的
// setup() 在 daemon context 跑，無法替玩家 add_action，見 content-race-active.md）。
//
// 與夜叉吞噬 (devour.c) 的分工：devour 另有「飽和 buff」的複雜機制；阿修羅啖屍
// 是單純的「吃屍回狀態」，故本檔比照 devour 的找屍／毀屍流程，但只做恢復、
// 不上任何 buff。
//
// 機制摘要（恢復類，比照 devour.c 的找屍 + supplement 用法）：
//   * 鎖定：query_race()=="ashura"，否則 notify_fail。
//   * 對象：吞食「房間裡的屍體」(obj/corpse.c，is_corpse() 為真)。屍體被啖食後
//     destruct──每次啖屍都要有新屍體，沒有無限刷資源的漏洞（同 devour）。
//   * 恢復：氣/精 (kee/gin) ── supplement_stat 補 current 到 heal/max 上限為止
//     （見 feature/statistic.c:264，回傳實際補回量）。形體 (kee) 為主、精 (gin) 為輔。
//   * 冷卻：set_temp("maul_cooldown", time()+N) + time() 判定（同 devour）。
//   * 硬直：start_busy（撕咬吞嚥需要時間）。

#include <ansi.h>

inherit F_CLEAN_UP;

// 冷卻秒數與回復量，集中在此方便調整平衡。
#define MAUL_COOLDOWN       30      // 兩次啖屍之間的冷卻秒數
#define MAUL_KEE_HEAL       40      // 每次啖屍回復的氣／形體 (主)
#define MAUL_GIN_HEAL       20      // 每次啖屍回復的精 (輔)
#define MAUL_BUSY           2       // 啖屍後的硬直 (heart beat 數)

void do_maul(object me, object corpse);

private void create() { seteuid(getuid()); }

// 在房間裡找一具可啖食的屍體 (is_corpse() 為真；見 obj/corpse.c)。
// 比照 devour.c::find_corpse──新鮮屍 / 腐屍皆可，骸骨 (decayed>=2) 不算。
object find_corpse(object me)
{
    object env, ob;

    env = environment(me);
    if( !env ) return 0;

    foreach(ob in all_inventory(env)) {
        if( !ob ) continue;
        if( living(ob) ) continue;          // 活物不是屍體
        if( ob->is_corpse() ) return ob;    // 新鮮屍 / 腐屍皆可，骸骨不算
    }
    return 0;
}

int main(object me, string arg)
{
    int left;
    object corpse;

    // 只有阿修羅會啖食屍體，其他種族不會這種本事。
    if( me->query_race() != "ashura" )
        return notify_fail("你不會這種本事。\n");

    if( me->query("life_form") == "ghost" )
        return notify_fail("人死了就一了百了, 快去找城隍復活吧!!\n");

    if( me->is_busy() )
        return notify_fail("請先用 halt 停止你正在做的事。\n");

    // 冷卻檢查：set_temp 存下次可用的時間戳。
    left = me->query_temp("maul_cooldown") - time();
    if( left > 0 )
        return notify_fail("你腹中尚在消受方才的血肉，還得再等 " + left + " 秒才能再啖。\n");

    // 必須有屍體可啖。
    corpse = find_corpse(me);
    if( !corpse )
        return notify_fail("這裡沒有可啖食的屍體。\n");

    do_maul(me, corpse);
    return 1;
}

void do_maul(object me, object corpse)
{
    int healed;

    // 再次確認狀態（do_maul 與 main 之間若有變化）。
    if( !me ) return;
    if( !corpse || !corpse->is_corpse() ) {
        // 屍體在這空檔被搶食 / 腐成骸骨了（同 devour 的補救）。
        corpse = find_corpse(me);
        if( !corpse ) {
            tell_object(me, "那具屍體已經沒了。\n");
            return;
        }
    }

    // 先設冷卻、進入硬直（無論恢復多少都只判一次）。
    me->set_temp("maul_cooldown", time() + MAUL_COOLDOWN);
    me->start_busy(MAUL_BUSY);

    message_vision(HIR "\n$N獰笑一聲，俯身撕咬" + corpse->name()
        + HIR "，將其血肉大口大口地吞嚥入腹！\n" NOR, me);

    // 屍體被啖食殆盡──每次啖屍都得有新屍體，杜絕無限刷資源。
    destruct(corpse);

    // 啖屍恢復氣／精；supplement_stat 補到 heal/max 上限為止，回傳實際補回量。
    healed  = me->supplement_stat("kee", MAUL_KEE_HEAL);
    healed += me->supplement_stat("gin", MAUL_GIN_HEAL);

    if( healed > 0 )
        tell_object(me, HIR "腥熱的血肉化作一股蠻力衝入四肢百骸，你只覺氣力大振。\n" NOR);
    else
        tell_object(me, "你飽食已極，這一口竟補不進什麼了。\n");
}

int help(object me)
{
    write(@HELP
指令格式：maul   (啖屍)

阿修羅一族性嗜血肉，可俯身撕咬倒在地上的屍體，將其血肉大口吞嚥入腹，藉此
回復自身的氣力與精。

每次啖屍之後，腹中需要片刻消受血肉，不能連續施放；場中沒有屍體時自然無從
下口。

只有阿修羅種族能使用這項本事。
HELP
    );
    return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
