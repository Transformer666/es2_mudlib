// wardance.c -- 刑天種族主動技能「祭舞」(戰舞)
//
// 刑天 (headless) 以乳為目、以臍為口，持干戚而舞，至死不屈。其族可藉一段
// 祭祀戰舞激揚血氣，短時間內大幅提升戰力。
// 見 docs/01-世界觀與劇情/03-種族設定.md：刑天 主動「祭祀舞蹈提升能力」。
//
// 本指令放在 /cmds/std/ ，用 query_race() 鎖死成只有刑天能用，其他種族
// 得到「你不會這種本事」（同 spitfire.c / surge.c 的做法──race daemon 的
// setup() 在 daemon context 跑，無法替玩家 add_action，見 content-race-active.md）。
//
// 機制摘要（暫時性 buff，比照戰鬥讀數的真正機制）：
//   * 鎖定：query_race()=="headless"，否則 notify_fail。
//   * 效果：對戰鬥相關的 apply/* 暫時加成。戰鬥迴圈讀的就是這些鍵──
//       query_ability("intimidate") 讀 apply/intimidate（攻勢），
//       query_ability("wittiness") 讀 apply/wittiness（守勢），
//       query_ability("attack")    讀 apply/attack   （攻擊技巧），
//       query_ability("defense")   讀 apply/defense  （防禦技巧），
//       見 feature/char/combat.c:69-139；wiz analyze 指令亦直接顯示這四項。
//     所以 add_temp("apply/<key>", N) 即為「暫時提升能力」的正解
//     （add_temp 累加既有值，見 feature/dbase.c:146）。
//   * 移除：以 call_out 定時呼叫 end_wardance，用 add_temp("apply/<key>", -N)
//     把先前加的量「減回去」（**不可用 delete_temp**，否則會連同刑天的被動
//     加成 apply/attack +50、apply/defense +100 一併抹掉）。同時清掉 buff 旗標。
//   * 重複施放：以 temp 旗標 "wardance_active" 記錄是否仍在 buff 中，正在
//     舞威時拒絕再舞。
//   * 冷卻：set_temp("wardance_cooldown", time()+N) + time() 判定。
//   * 硬直：起舞需要時間，start_busy。

#include <ansi.h>

inherit F_CLEAN_UP;

// 冷卻秒數、加成量與持續時間，集中在此方便調整平衡。
// 刻意壓低、且為暫時性──這是一段戰舞 buff，不是永久強化。
#define WARDANCE_COOLDOWN   60      // 兩次祭舞之間的冷卻秒數
#define WARDANCE_DURATION   25      // buff 持續秒數（call_out 以秒計）
#define WARDANCE_INTIM      20      // 攻勢 (apply/intimidate) 加成
#define WARDANCE_WIT        15      // 守勢 (apply/wittiness) 加成
#define WARDANCE_ATK        15      // 攻擊技巧 (apply/attack) 加成
#define WARDANCE_DEF        15      // 防禦技巧 (apply/defense) 加成
#define WARDANCE_BUSY       2       // 起舞後的硬直 (heart beat 數)

void do_wardance(object me);
void end_wardance(object me);

private void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    int left;

    // 只有刑天會跳這祭祀戰舞，其他種族不會這種本事。
    if( me->query_race() != "headless" )
        return notify_fail("你不會這種本事。\n");

    if( me->query("life_form") == "ghost" )
        return notify_fail("人死了就一了百了, 快去找城隍復活吧!!\n");

    if( me->is_busy() )
        return notify_fail("請先用 halt 停止你正在做的事。\n");

    // buff 仍在身上時不可再舞（避免疊加無限延長）。
    if( me->query_temp("wardance_active") )
        return notify_fail("你周身戰意正酣，這股舞威尚未消退。\n");

    // 冷卻檢查：set_temp 存下次可用的時間戳。
    left = me->query_temp("wardance_cooldown") - time();
    if( left > 0 )
        return notify_fail("你方才舞罷力消，氣血未復，還得再歇 " + left + " 秒。\n");

    do_wardance(me);
    return 1;
}

void do_wardance(object me)
{
    // 再次確認狀態（do_wardance 與 main 之間若有變化）。
    if( !me ) return;

    // 先設旗標、冷卻、進入硬直（無論如何只付一次代價）。
    me->set_temp("wardance_active", 1);
    me->set_temp("wardance_cooldown", time() + WARDANCE_COOLDOWN);
    me->start_busy(WARDANCE_BUSY);

    message_vision(HIR
        "\n$N以乳為目、以臍為口，揮舞干戚踏起一段悲烈的祭祀戰舞，週身殺氣如潮翻湧！\n" NOR,
        me);

    // 暫時提升戰力：直接加在戰鬥迴圈會讀到的 apply/* 上
    // （見檔頭說明與 feature/char/combat.c:69-139）。
    me->add_temp("apply/intimidate", WARDANCE_INTIM);
    me->add_temp("apply/wittiness",  WARDANCE_WIT);
    me->add_temp("apply/attack",     WARDANCE_ATK);
    me->add_temp("apply/defense",    WARDANCE_DEF);

    tell_object(me, HIR "你只覺血氣翻騰、勇力倍增，舞威加身！\n" NOR);

    // 定時讓 buff 消退：call_out("funcname", 秒數, 參數)（同 combat.c:374 / steal.c:124）。
    // 用字串名形式（與 combat.c/steal.c 的慣例一致）。
    me->set_temp("wardance_callout",
        call_out("end_wardance", WARDANCE_DURATION, me));
}

// buff 到期：把先前加的量逐一「減回去」，並清掉旗標。
// 用 add_temp(key, -N) 而非 delete_temp，以保住刑天的被動 apply 加成。
void end_wardance(object me)
{
    if( !me ) return;

    me->add_temp("apply/intimidate", -WARDANCE_INTIM);
    me->add_temp("apply/wittiness",  -WARDANCE_WIT);
    me->add_temp("apply/attack",     -WARDANCE_ATK);
    me->add_temp("apply/defense",    -WARDANCE_DEF);

    me->delete_temp("wardance_active");
    me->delete_temp("wardance_callout");

    tell_object(me, NOR "你舞步漸歇，那股翻湧的舞威也隨之力消而散。\n");
}

int help(object me)
{
    write(@HELP
指令格式：wardance   (祭舞、戰舞)

刑天一族至死不屈，能踏起一段悲烈的祭祀戰舞，激揚血氣，於短時間內大幅提升
自身的攻勢、守勢與攻防技巧。

這股舞威只能維持一陣子，時間一到便會力消而散；舞罷之後氣血耗竭，須得歇上
好一會兒才能再舞，舞威未退之前也無法重複施放。

只有刑天種族能使用這項本事。
HELP
    );
    return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
