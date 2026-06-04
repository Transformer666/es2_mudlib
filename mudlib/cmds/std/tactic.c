// tactic.c -- 振武軍營軍人「戰術兵法 strategy」的施展指令
//
// 來歷(docs/03-門派與武功/06-軍人-振武大內.md L29「`tactic <戰術> (<目標>)`」、
// L33-37/L53-62/L119-130 各戰術)：軍人在五十斤大石處 train 戰術兵法後﹐以本指令
// 施展急救/虎襲/大急救/補給/錢糧/賦予等戰術(後勤一路)。
//
// 派發結構鏡 cmds/std/exert.c：exert 取玩家所掛內功(skill_mapped("force"))呼其
// daemon 的 exert_function﹔本指令取玩家的兵法技能 daemon(戰術兵法 strategy)呼其
// tactic_function(me, 戰術名, target)。具體戰術邏輯與消耗/效果一律在
// daemon/skill/strategy.c 內處理(數值依 docs)﹐本檔只負責解析指令、找技能、找目標、
// 守衛(guard)與 notify_fail。
//
// 找技能：優先取 me->skill_mapped("strategy")(若玩家把 strategy 映射到別的 key)﹐
// 退而求其次直接用 "strategy"。SKILL_D("strategy") 取得已登錄的兵法 daemon
// (見 daemon/skill/strategy.c::create register_skill_daemon("strategy"))。
//
// runtime 鐵則：不涉 ::die()/destruct()(#10)、不 replace_program(#11)。

#include <ansi.h>

inherit F_CLEAN_UP;

private void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    string func, dest, skill;
    object target, daemon;

    // 須先學會戰術兵法方能施展(鏡 berserk.c::main 的 query_learn 守衛)。
    if( !me->query_learn("strategy", 1) )
        return notify_fail("你並不會戰術兵法。\n");

    if( me->is_busy() )
        return notify_fail("你必須先用 halt 停止你正在做的事﹗\n");

    if( !arg || arg == "" )
        return notify_fail("指令格式﹕tactic <戰術> [目標]\n");

    // 解析「<戰術> <目標>」(目標可省)。鏡 exert.c 之 present 找目標﹐
    // 先找環境再找身上。
    if( sscanf(arg, "%s %s", func, dest) == 2 ) {
        target = present(dest, environment(me));
        if( !target ) target = present(dest, me);
        if( !target )
            return notify_fail("這裡並沒有這個目標。\n");
    } else {
        func = arg;
    }

    // 取玩家所掛/慣用的兵法技能 key﹐退而求其次用 "strategy" 本身。
    skill = me->skill_mapped("strategy");
    if( !stringp(skill) || skill == "" ) skill = "strategy";

    daemon = SKILL_D(skill);
    if( !objectp(daemon) ) daemon = SKILL_D("strategy");
    if( !objectp(daemon) )
        return notify_fail("戰術兵法尚未開啟﹐無法施展。\n");

    notify_fail("你並不會這一式兵法。\n");
    return daemon->tactic_function(me, func, target);
}

int help(object me)
{
    write(@TEXT
指令格式﹕tactic <戰術> [目標]

振武軍營軍人在「戰術兵法 (strategy)」上的造詣﹐可調度戰場後勤、運籌帷幄。
先在五十斤大石處勤練戰術兵法﹐而後以此指令施展各式戰術﹕

    first_aid   急救  ：消耗神識﹐迅速為自己療傷回補精氣。
    charge      虎襲  ：消耗部分精力﹐如猛虎撞向目標﹐令其短暫遲滯。
    mass_aid    大急救：消耗戰功﹐恢復房間內所有人的氣血與形體。
    supply      補給  ：消耗戰功﹐運出大量饅頭分發給在場眾人。
    money       錢糧  ：消耗戰功﹐運出大量白銀入懷。
    wis         賦予  ：消耗戰功﹐提升房間內所有人的慧根與護甲。

部分戰術(如虎襲)需指定目標。各戰術的消耗與效果隨你戰術兵法的火候而異﹐
進階「軍師」一脈更可使戰術受法術強度額外加成。
TEXT
    );
    return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
