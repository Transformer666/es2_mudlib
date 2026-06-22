// perform.c -- 戰鬥「絕招(perform)」的施放指令
//
// 來歷(docs/03-門派與武功/04-書生-步玄玄天.md §9/2 平衡 L100-104「perform >6 點
// delay 2」)：各門派絕招需於戰鬥中以本指令手動施放。原開源 perform.c 僅有一段
// 分派骨架﹐且分派條件寫反(原作 `martial_skill != me->skill_mapped(martial_skill)`
// 恆真致永不正確派發)﹐且全 mudlib 無任何 perform_action 實作、亦無絕招點累積
// 機制。本檔改為派發至中央絕招總機 daemon/skill/perform.c(PERFORM_D)﹐由其處理
// 累點、查點、三式通用絕招(無視防禦/定人/連擊)與 docs「>6 點 delay 2」。
//
// 派發結構鏡 cmds/std/exert.c / cmds/std/tactic.c：本指令解析 `perform
// <技能:絕招> [on <目標>]`﹐找目標﹐呼 SKILL_D("perform")->perform_action(
// me, 技能名, 絕招名, target)。具體絕招邏輯與門檻/效果一律在 daemon/skill/
// perform.c 內處理(數值依 docs﹐未明者取合理可驗預設)﹐本檔只負責解析、找目標、
// 戰鬥前置守衛與 notify_fail。
//
// runtime 鐵則：不涉 ::die()/destruct()(#10)、不 replace_program(#11)。

#include <ansi.h>
#include <skill.h>

inherit F_CLEAN_UP;

private void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    string martial_skill, act, trg;
    object target, daemon;

    if( me->is_busy() )
        return notify_fail("你現在沒有空﹗\n");

    if( environment(me)->query("no_fight") )
        return notify_fail("這裡不准戰鬥。\n");

    if( !me->is_fighting() )
        return notify_fail("你必須在戰鬥中才能使用絕招！\n");

    if( !arg || arg == "" )
        return notify_fail("指令格式﹕perform <技能:絕招> [on <目標>]\n");

    // 解析「<技能>:<絕招> on <目標>」或「<技能>:<絕招>」(目標可省﹐省略時取
    // 當前交手對象 query_opponent)。
    if( sscanf(arg, "%s:%s on %s", martial_skill, act, trg) != 3
    &&  sscanf(arg, "%s:%s", martial_skill, act) != 2 )
        return notify_fail("指令格式﹕perform <技能:絕招> [on <目標>]\n");

    if( trg ) {
        target = present(trg, environment(me));
        if( !target ) return notify_fail("你要對誰使用絕招？\n");
        if( !living(target) )
            return notify_fail("你可以直接宰了這個昏迷不醒的傢伙，不需要用絕招。\n");
    } else {
        // 未指定目標：取當前交手對象。
        target = me->query_opponent();
        if( !target )
            return notify_fail("你要對誰施展絕招？請用 perform <技能:絕招> on <目標>。\n");
    }

    // 取中央絕招總機 daemon(daemon/skill/perform.c﹐create 時已 register)。
    daemon = SKILL_D("perform");
    if( !objectp(daemon) )
        return notify_fail("絕招系統尚未開啟﹐無法施展。\n");

    notify_fail("你並不會這一招絕招。\n");
    return daemon->perform_action(me, martial_skill, act, target);
}

int help(object me)
{
    write(@HELP
指令格式﹕perform <技能:絕招> [on <施招對象>]

在戰鬥中以絕招迎敵。絕招需消耗「絕招點」——戰鬥中每回合會自動累積絕招點
(出招、受擊皆會累積)﹐點數足夠時方能施放對應的絕招。

通用絕招(各門派招式日後可另行擴充自家專屬絕招)﹕

    ignoredef  無視防禦：傾盡功力的必殺一擊﹐封死對手所有閃避拆解之機﹐
                         直接造成高額傷害。
    hold       定人    ：點中對手大穴﹐令其短暫無法行動。
    combo      連擊    ：連環追擊對手數招﹐攻勢綿綿不絕。

門派專屬絕招(僅該門弟子可施展)﹕

    diepying   蝶影幻步：瑯夷派脫身絕技。身形如蝶影幻動﹐瞬間脫離當前一切
                         纏鬥﹐竄入鄰處斂息藏匿(耗神、氣)。

例如﹕ perform sword:ignoredef on guard
      perform dodge:diepying          (瑯夷派以身法施展蝶影幻步脫身)

      就是以你所使用的劍法﹐對 guard 施展「無視防禦」絕招。

省略 on <目標> 時﹐預設對你當前交手的對象施展。

註﹕一次施放消耗逾六點絕招點的絕招(如連擊)﹐施招者自身會有短暫的硬直(delay)。
HELP
    );
    return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
