// trample.c -- 釘靈種族主動技能「踐踏」
//
// 釘靈 (dingling) 是一支天生善跑、腿力驚人的種族（被動：移+50、傷+10）。
// 見 docs/01-世界觀與劇情/03-種族設定.md：釘靈 主動「踐踏目標使其無法攻擊或行動」。
//
// 本指令放在 /cmds/std/ ，所有人的指令搜尋路徑都包含此目錄，所以這裡
// 用 query_race() 把指令鎖死成只有釘靈能用；其他種族會得到「你不會這種
// 本事」的回應（同 spitfire.c 的做法──race daemon 無法替玩家 add_action）。
//
// 機制摘要（皆比照 spitfire.c / berserk.c）：
//   * 鎖定：query_race()=="dingling"，否則 notify_fail。
//   * 消耗：氣 (kee) ── 比照 berserk.c 用 query_stat("kee")/consume_stat。
//   * 冷卻：set_temp("trample_cooldown", time()+N) + time() 判定。
//   * 傷害：對「當前單一目標」query_opponent() 呼叫 receive_damage()；
//           先 kill_ob 進入 kill_mode，踐踏才會真的造成形體傷害（見 combat.c）。
//   * 定身：對目標 start_busy(N)──busy 時 heart_beat 會跑 continue_action
//           而非 attack()（見 feature/char/action.c），目標短暫無法攻擊／行動，
//           恰好對應 doc 的「使其無法攻擊或行動」。

#include <ansi.h>

inherit F_CLEAN_UP;

// 冷卻秒數、氣消耗、傷害係數與定身時間，集中在此方便調整平衡。
#define TRAMPLE_COOLDOWN    25      // 兩次踐踏之間的冷卻秒數
#define TRAMPLE_KEE_COST    15      // 每次踐踏消耗的氣
#define TRAMPLE_BASE_DMG    20      // 基礎踐踏傷害
#define TRAMPLE_BUSY        2       // 踐踏後自己的硬直 (heart beat 數)
#define TRAMPLE_STUN        2       // 目標被踏倒後無法行動的 heart beat 數

void do_trample(object me);

private void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    int left;

    // 只有釘靈會踐踏，其他種族不會這種本事。
    if( me->query_race() != "dingling" )
        return notify_fail("你不會這種本事。\n");

    if( me->query("life_form") == "ghost" )
        return notify_fail("人死了就一了百了, 快去找城隍復活吧!!\n");

    if( me->is_busy() )
        return notify_fail("請先用 halt 停止你正在做的事。\n");

    // 必須在戰鬥中才有對手可踏。
    if( !me->is_fighting() )
        return notify_fail("你得先有交手的對象，才能施展踐踏！\n");

    if( environment(me)->query("no_fight") )
        return notify_fail("這裡不准戰鬥。\n");

    // 冷卻檢查：set_temp 存下次可用的時間戳。
    left = me->query_temp("trample_cooldown") - time();
    if( left > 0 )
        return notify_fail("你的雙腿尚未蓄足勁道，還得再等 " + left + " 秒。\n");

    // 氣不足無法施展。
    if( me->query_stat("kee") < TRAMPLE_KEE_COST )
        return notify_fail("你的氣不夠，使不出這記重踏。\n");

    do_trample(me);
    return 1;
}

void do_trample(object me)
{
    object victim, *enemy;
    int power, dmg, resist;

    // 再次確認狀態（do_trample 與 main 之間若有變化）。
    if( !me || me->query_stat("kee") < TRAMPLE_KEE_COST ) return;

    // 踐踏單一目標：取當前敵人之一（query_opponent 只在有設定首要目標時才有值，
    // 一般戰鬥用 query_enemy()，同 spitfire）。
    victim = me->query_opponent();
    if( !victim ) {
        enemy = me->query_enemy();
        if( arrayp(enemy) && sizeof(enemy) ) victim = enemy[0];
    }
    if( !victim || environment(victim) != environment(me)
    ||  !victim->is_character() || victim->is_corpse() ) {
        tell_object(me, "你眼前並沒有可踏的對手。\n");
        return;
    }

    // 先消耗氣並設下冷卻、進入硬直，無論成不成功都只付一次代價。
    me->consume_stat("kee", TRAMPLE_KEE_COST);
    me->set_temp("trample_cooldown", time() + TRAMPLE_COOLDOWN);
    me->start_busy(TRAMPLE_BUSY);

    // 確保進入 kill_mode，踐踏才會真的傷到形體。
    me->kill_ob(victim);

    // 傷害力隨膂力 (str) 微幅成長，整體壓低避免濫用。
    power = TRAMPLE_BASE_DMG + me->query_attr("str") / 3;
    dmg = power + random(power / 2 + 1);

    // 護甲 (apply/armor) 在此略作抵減，呼應一般防具的用意。
    resist = victim->query_temp("apply/armor");
    if( resist > 0 ) {
        dmg -= random(resist / 2 + 1);
        if( dmg < 1 ) dmg = 1;
    }

    message_vision(HIY "\n$N雙腿勁發，一個箭步欺身，狠狠將$n踏倒在地！\n" NOR,
        me, victim);
    victim->receive_damage(dmg, me, me);

    // 把目標踏得無法動彈：給對方上 busy，heart_beat 會改跑 continue_action
    // 而非 attack()，目標短暫無法攻擊／行動。
    if( victim && !victim->is_corpse() ) {
        victim->start_busy(TRAMPLE_STUN);
        message_vision(HIY "$n被踏得手忙腳亂，一時間竟無法還手！\n" NOR,
            me, victim);
    }
}

int help(object me)
{
    write(@HELP
指令格式：trample   (踐踏)

釘靈一族腿力驚人，善於奔走衝刺，可以一個箭步欺近交戰中的對手，雙腿勁發將
其狠狠踏倒在地。

這記重踏只能施於你當前的對手，造成形體傷害之餘，更會令對方手忙腳亂、短暫
無法攻擊或行動。傷害力隨你的膂力提升，但每次施展都得耗去不少氣，雙腿也需
要時間重新蓄勁，不能連續施放。

只有釘靈種族能使用這項本事。
HELP
    );
    return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
