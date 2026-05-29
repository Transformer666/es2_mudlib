// devour.c -- 夜叉種族主動技能「吞噬」(吞鬼)
//
// 夜叉 (yaksa) 是山海經的食魂惡鬼，最具特色的本事便是「吞噬其他生物的魂魄」。
// 見 docs/01-世界觀與劇情/03-種族設定.md「夜叉吞鬼 devour（重點機制）」：
//   吞噬可恢復狀態；反覆吞噬至「飽和」(約 10 隻鬼) 後，火/冰/風/雷傷+50、
//   行動+50、警覺+100、守勢+100、攻勢+100；死掉 / logout 要重吞；30 秒 CD。
//
// 本指令放在 /cmds/std/ ，用 query_race() 鎖死成只有夜叉能用，其他種族得到
// 「你不會這種本事」（同 spitfire.c / gnaw.c 的做法──race daemon 的 setup()
// 在 daemon context 跑，無法替玩家 add_action，見 content-race-active.md）。
//
// v1 範圍（安全、可控）：
//   * 對象：吞噬「房間裡的屍體」(obj/corpse.c，is_corpse() 為真)。屍體被吞噬後
//     destruct──每次吞噬都要有新屍體，沒有無限刷資源的漏洞。
//   * 恢復：精/氣/神 (gin/kee/sen) ── supplement_stat 補到 heal/max 上限為止
//     (見 feature/statistic.c:264)。
//   * 飽和：set_temp("devour_saturation", n+1)，上限 DEVOUR_SAT_MAX。
//     依當前飽和度「重算後設定」(set_temp 而非 add_temp) 各 apply/* buff，
//     所以不會跨次數無限疊加；溫和封頂。temp 在死亡/登出時清掉，符合 ES2
//     「死掉 / logout 要重吞」的設定。
//   * 冷卻：set_temp("devour_cooldown", time()+N) + time() 判定 (同 spitfire)。
//   * 硬直：start_busy。
//
// TODO（v2）：吞噬「活的鬼魂」(life_form=="ghost" 的玩家/NPC)──需處理同意、
//   PK 規則、強鬼吞噬耗時等，較複雜，v1 先只吃房間裡的屍體。
// TODO（平衡）：飽和 buff 的元素傷害鍵 (apply/armor_vs_cold/_air/_lightning) 目前
//   combat.c 並未一般性讀取 (只有 spitfire 手動讀 armor_vs_fire 抵火傷)，故元素
//   「傷害力+50」尚無對應戰鬥效果；此處先上 combat.c 確實會讀的鍵 (見下)。

#include <ansi.h>

inherit F_CLEAN_UP;

// 數值集中於此方便調整平衡。
#define DEVOUR_COOLDOWN     30      // 兩次吞噬之間的冷卻秒數 (doc：30s CD)
#define DEVOUR_BUSY         2       // 吞噬後的硬直 (heart beat 數)
#define DEVOUR_SAT_MAX      10      // 飽和上限 (doc：約 10 隻鬼)

// 每次吞噬恢復的精/氣/神 (溫和；supplement_stat 仍受上限約束)。
#define DEVOUR_GIN_HEAL     20
#define DEVOUR_KEE_HEAL     20
#define DEVOUR_SEN_HEAL     30

void do_devour(object me, object corpse);
void apply_saturation(object me);

private void create() { seteuid(getuid()); }

// 在房間裡找一具可吞噬的屍體 (is_corpse() 為真；見 obj/corpse.c)。
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

    // 只有夜叉會吞噬魂魄，其他種族不會這種本事。
    if( me->query_race() != "yaksa" )
        return notify_fail("你不會這種本事。\n");

    if( me->query("life_form") == "ghost" )
        return notify_fail("人死了就一了百了, 快去找城隍復活吧!!\n");

    if( me->is_busy() )
        return notify_fail("請先用 halt 停止你正在做的事。\n");

    // 冷卻檢查：set_temp 存下次可用的時間戳。
    left = me->query_temp("devour_cooldown") - time();
    if( left > 0 )
        return notify_fail("你腹中魔氣未平，還得再等 " + left + " 秒才能再吞。\n");

    // 必須有屍體可吞。
    corpse = find_corpse(me);
    if( !corpse )
        return notify_fail("這裡沒有可吞噬的屍體。\n");

    do_devour(me, corpse);
    return 1;
}

void do_devour(object me, object corpse)
{
    int healed, sat;

    // 再次確認狀態 (do_devour 與 main 之間若有變化)。
    if( !me ) return;
    if( !corpse || !corpse->is_corpse() ) {
        // 屍體在這空檔被搶吞 / 腐成骸骨了。
        corpse = find_corpse(me);
        if( !corpse ) {
            tell_object(me, "那具屍體已經沒了。\n");
            return;
        }
    }

    // 先設冷卻、進入硬直 (無論恢復多少都只判一次)。
    me->set_temp("devour_cooldown", time() + DEVOUR_COOLDOWN);
    me->start_busy(DEVOUR_BUSY);

    message_vision(HIM "\n$N張開血盆大口，將" + corpse->name()
        + HIM "的魂魄連皮帶骨地吞噬入腹！\n" NOR, me);

    // 屍體被吞噬殆盡──每次吞噬都得有新屍體，杜絕無限刷資源。
    destruct(corpse);

    // 吞噬恢復精/氣/神；supplement_stat 補到 heal/max 上限為止，回傳實際補回量。
    healed  = me->supplement_stat("gin", DEVOUR_GIN_HEAL);
    healed += me->supplement_stat("kee", DEVOUR_KEE_HEAL);
    healed += me->supplement_stat("sen", DEVOUR_SEN_HEAL);

    if( healed > 0 )
        tell_object(me, HIM "一股腥熱的魔氣自腹中升起，你只覺精氣神為之一振。\n" NOR);
    else
        tell_object(me, "你飽食已極，這一口竟補不進什麼了。\n");

    // 累積飽和度 (上限封頂)，並依新的飽和度重算 buff。
    sat = me->query_temp("devour_saturation");
    if( sat < DEVOUR_SAT_MAX ) {
        sat++;
        me->set_temp("devour_saturation", sat);
    }
    apply_saturation(me);

    if( sat >= DEVOUR_SAT_MAX )
        tell_object(me, HIR "你魔氣淋漓，週身鼓盪，已臻飽和之境！\n" NOR);
}

// 依當前飽和度設定各項 apply/* buff。
//
// 用「重算後 set_temp」而非 add_temp：每次吞噬都把 buff 鍵直接設成目標值，
// 因此不會跨次數無限疊加 (這是本技能的關鍵安全點)。這些鍵都是夜叉 daemon
// 沒有碰過的鍵 (daemon 只 add_temp apply/defense、apply/attack)，所以在這裡
// set_temp 不會覆蓋掉種族被動加成。
//
// buff 隨飽和度線性成長，飽和 (DEVOUR_SAT_MAX) 時達到 doc 的上限值：
//   攻勢 (apply/intimidate) +100、守勢 (apply/wittiness) +100、
//   行動 (apply/move) +50、警覺 (apply/awarness) +100。
// 這些鍵 combat.c 確實會讀 (見 feature/char/combat.c:90/99/122/131)。
// 另上 apply/armor_vs_fire +50 作為「火傷」相關的防禦面呼應 (此鍵已被
//   spitfire.c 證實會被讀)；其餘元素鍵 combat 尚未一般性讀取，見檔頭 TODO。
//
// 註：apply/awarness 是 mudlib 既有的拼法 (非 awareness)，須照原拼法。
void apply_saturation(object me)
{
    int sat;

    if( !me ) return;
    sat = me->query_temp("devour_saturation");
    if( sat < 0 ) sat = 0;
    if( sat > DEVOUR_SAT_MAX ) sat = DEVOUR_SAT_MAX;

    // 線性內插：sat / SAT_MAX 比例 * 上限值。飽和時取得完整加成。
    me->set_temp("apply/intimidate",     100 * sat / DEVOUR_SAT_MAX);
    me->set_temp("apply/wittiness",      100 * sat / DEVOUR_SAT_MAX);
    me->set_temp("apply/move",            50 * sat / DEVOUR_SAT_MAX);
    me->set_temp("apply/awarness",       100 * sat / DEVOUR_SAT_MAX);
    me->set_temp("apply/armor_vs_fire",   50 * sat / DEVOUR_SAT_MAX);
}

int help(object me)
{
    write(@HELP
指令格式：devour   (吞噬)

夜叉一族乃食魂惡鬼，可張口吞噬倒在地上的屍體，將其魂魄連皮帶骨地吞入腹中，
藉此回復自身的精、氣、神。

反覆吞噬會使體內魔氣漸盛，待累積至「飽和」之境，攻勢、守勢、行動、警覺等
戰技都將大幅提升。但這股魔氣並不長久──一旦身死或離線，便須重新吞噬蓄積。

每次吞噬之間需要片刻平復腹中魔氣，不能連續施放；場中沒有屍體時自然無從下口。

只有夜叉種族能使用這項本事。
HELP
    );
    return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
