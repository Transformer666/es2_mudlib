// spitfire.c -- 厭火種族主動技能「吐火」
//
// 厭火 (yenhold) 是火系種族，可以吐出熊熊烈火燒傷四周所有對手。
// 見 docs/01-世界觀與劇情/03-種族設定.md：厭火 主動「吐出熊熊烈火燒傷所有對手」。
//
// 本指令放在 /cmds/std/ ，所有人的指令搜尋路徑都包含此目錄，所以這裡
// 用 query_race() 把指令鎖死成只有厭火能用；其他種族會得到「你不會這種
// 本事」的回應。這是目前 mudlib 唯一可靠的「種族專屬指令」做法──race
// daemon 的 setup() 在 daemon context 執行，無法替玩家 add_action（見
// doc/efuns/add_action：定義指令的物件必須與玩家同處一室）。
//
// 機制摘要（皆比照現有指令）：
//   * 消耗：神 (sen) ── 比照 study.c 用 query_stat("sen")/consume_stat。
//   * 冷卻：set_temp("spitfire_cooldown", time()+N) + time() 判定。
//   * 傷害：對每個敵人呼叫 victim->receive_damage()（見 feature/char/combat.c）。
//           先 kill_ob 進入 kill_mode，烈火才會真的造成形體傷害。
//   * 火防：若對手身上有 apply/armor_vs_fire（厭火被動即是 +50），
//           於此處自行抵減，呼應該屬性鍵的設計用意。

#include <ansi.h>

inherit F_CLEAN_UP;

// 冷卻秒數、神消耗下限與傷害係數，集中在此方便調整平衡。
#define SPITFIRE_COOLDOWN   30      // 兩次吐火之間的冷卻秒數
#define SPITFIRE_SEN_COST   10      // 每次吐火消耗的神
#define SPITFIRE_BASE_DMG   15      // 基礎火傷
#define SPITFIRE_BUSY       2       // 吐火後的硬直 (heart beat 數)

void do_spitfire(object me);

private void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    int left;

    // 只有厭火會吐火，其他種族不會這種本事。
    if( me->query_race() != "yenhold" )
        return notify_fail("你不會這種本事。\n");

    if( me->query("life_form") == "ghost" )
        return notify_fail("人死了就一了百了, 快去找城隍復活吧!!\n");

    if( me->is_busy() )
        return notify_fail("請先用 halt 停止你正在做的事。\n");

    // 必須在戰鬥中才有對手可燒。
    if( !me->is_fighting() )
        return notify_fail("你得先有交手的對象，才能吐火傷敵！\n");

    if( environment(me)->query("no_fight") )
        return notify_fail("這裡不准戰鬥。\n");

    // 冷卻檢查：set_temp 存下次可用的時間戳。
    left = me->query_temp("spitfire_cooldown") - time();
    if( left > 0 )
        return notify_fail("你體內的火種尚未蓄足，還得再等 " + left + " 秒。\n");

    // 神不足無法運火。
    if( me->query_stat("sen") < SPITFIRE_SEN_COST )
        return notify_fail("你的神不夠，運不起這口烈焰。\n");

    do_spitfire(me);
    return 1;
}

void do_spitfire(object me)
{
    object *enemy, victim;
    int power, dmg, resist, hit;

    // 再次確認狀態（do_spitfire 與 main 之間若有變化）。
    if( !me || me->query_stat("sen") < SPITFIRE_SEN_COST ) return;

    enemy = me->query_enemy();
    if( !arrayp(enemy) || !sizeof(enemy) ) {
        tell_object(me, "你四下一望，竟沒有可燒的對手。\n");
        return;
    }

    // 先消耗神並設下冷卻、進入硬直，無論燒到幾個敵人都只付一次代價。
    me->consume_stat("sen", SPITFIRE_SEN_COST);
    me->set_temp("spitfire_cooldown", time() + SPITFIRE_COOLDOWN);
    me->start_busy(SPITFIRE_BUSY);

    // 全場提示：吐出熊熊烈火。
    message_vision(HIR "\n$N張口噴出一道熊熊烈火，霎時將四周染成一片火海！\n\n" NOR,
        me);

    // 傷害力隨膂力 (str) 與神 (sen) 微幅成長，整體壓低避免濫用。
    power = SPITFIRE_BASE_DMG
        + me->query_attr("str") / 3
        + me->query_stat("sen") / 8;

    hit = 0;
    foreach(victim in enemy) {
        if( !victim ) continue;
        // 只燒同一個房間裡的敵人。
        if( environment(victim) != environment(me) ) continue;
        if( !victim->is_character() ) continue;
        if( victim->is_corpse() ) continue;

        // 確保進入 kill_mode，烈火才會真的傷到形體。
        me->kill_ob(victim);

        // 計算這一下火傷：基礎力道再加少許隨機。
        dmg = power + random(power / 2 + 1);

        // 對手的火防 (apply/armor_vs_fire) 在此抵減，呼應該屬性鍵用意。
        // 注意：base resist_damage() 只讀 apply/armor，火防需在這裡自行處理。
        resist = victim->query_temp("apply/armor_vs_fire");
        if( resist > 0 ) {
            dmg -= random(resist);
            if( dmg < 1 ) {
                message_vision(HIY "烈火舔過$n的身體，卻被一層灼熱的氣勁擋了下來。\n" NOR,
                    me, victim);
                continue;
            }
        }

        message_vision(HIR "$n被$N噴出的烈火燒得焦頭爛額，慘叫連連！\n" NOR,
            me, victim);
        victim->receive_damage(dmg, me, me);
        hit++;
    }

    if( !hit )
        tell_object(me, "這口火終究沒能傷到誰。\n");
}

int help(object me)
{
    write(@HELP
指令格式：spitfire   (吐火)

厭火一族天生火氣旺盛，可以張口吐出熊熊烈火，將四周交手的對手盡數燒傷。

這口烈火會傷及房間裡所有正與你交戰的敵人，傷害力隨你的膂力與神而提升，
但每次吐火都得消耗不少神，而且體內火種需要時間重新蓄積，不能連續施放。

只有厭火種族能使用這項本事；對火有抗性的對手所受的傷害會大幅降低。
HELP
    );
    return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
