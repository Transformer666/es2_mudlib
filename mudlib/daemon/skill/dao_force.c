// 明道心法 dao force -- 茅山派/天師玄衣弟子的入門內功
//
// 茅山道士存神養氣、以通鬼神的根本吐納之術，神台澄澈、五氣朝元。修煉與
// valid_enable 等共用機制由 FORCE(/std/force.c)基底提供；本檔在此之上 override
// cultivate_msg() 提供茅山派自家的打坐氣象，並 override exert_function 以實作
// docs 載明的兩式運功補益 recover / remedy。
//
// === docs(docs/03-門派與武功/02-道士-天師與茅山.md「明道心法 (dao force)」L115) ===
//   - 內功、lv >= 20。
//   - recover (lv 30)：提升疲勞恢復最大值。
//   - remedy  (lv 60)：消飲水恢復(精氣神)當前值。
// 與天師朱衣「丹陽神功 sun force」同型(亦載 recover/remedy)﹐惟門檻等級不同：
// sun force 為 remedy 不分階、recover lv30﹔明道則 recover lv30、remedy lv60。
//
//   recover(消耗：本式不耗三圍/飲水﹐純運功固本)：
//     運轉明道心法把疲勞的「恢復最大值」(stats_max["fatigue"])往上推﹐使日後能
//     承受更多研讀/施術而不致過勞。以 advance_stat("fatigue", +N) 改 max(見
//     feature/statistic.c::advance_stat 只動 stats_max)。fatigue 的 current 由
//     supplement_stat 累積、其上限即此 max(見 feature/study.c::L88、
//     daemon/skill/recovery-needle.c)﹐故抬高 max 即「提升疲勞恢復最大值」。
//
//   remedy(消耗：飲水 water 當前值)：
//     以體內水氣為引﹐化津為氣﹐回補精(gin)、氣(kee)、神(sen)三圍之「當前值」。
//     扣 water 以 consume_stat("water", N, me)(只削 current﹐見 statistic.c)﹔
//     回三圍當前值以 supplement_stat(自動封頂於各圍 heal/max﹐不溢出)。飲水不足
//     則 notify_fail 說明﹐不予施為(渴而無津﹐化氣無源)。
//
// 派發路徑(cmds/std/exert.c::main L46)：玩家鍵入 `exert recover` 或 `exert remedy`。
// exert.c 取 me->skill_mapped("force")(= 已掛上的內功 key﹐此處為 "dao force")﹐
// 呼 SKILL_D("dao force")->exert_function(me, func, target)。本檔接到
// func ∈ {recover, remedy} 即自行處理﹔其餘 func(含 "dao force" 本身打坐修煉)落回
// ::exert_function 由 FORCE 基底處理。此乃 daemon/skill/dragon_force.c、zushang.c
// override 具名功能、其餘落回基底的同型結構。
//
// runtime 鐵則：本式不涉 ::die()/destruct()(#10)﹐亦不 replace_program(#11)﹔
// 為內功 daemon(inherit FORCE)﹐非 F_VILLAGER NPC﹐不 include <weapon.h>。

#include <ansi.h>

inherit FORCE;

// === 兩式運功補益的門檻與消耗/效果參數(docs 載明等級﹐量值為本次設計值) ===
#define DAO_RECOVER_LEVEL   30      // recover 門檻：內功(force/dao force) >= 30。
#define DAO_RECOVER_GAIN    20      // recover 每次抬升疲勞恢復最大值的量。

#define DAO_REMEDY_LEVEL    60      // remedy  門檻：內功(force/dao force) >= 60。
#define DAO_REMEDY_WATER    30      // remedy  每次消耗的飲水(water)當前值。
#define DAO_REMEDY_HEAL     30      // remedy  每圍(精/氣/神)回補的當前值量。

// 前置宣告(lesson #12：凡「定義前引用」之自訂函式一律先前置宣告﹐免編譯
// Undefined function、daemon lazy-load 失敗、SKILL_D 靜默回 0)。
varargs int exert_function(object me, string func, object target);
int dao_force_level(object me);
int do_recover(object me);
int do_remedy(object me);

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("dao force");
    setup();
}

// 茅山弟子打坐運功時所現的內功氣象。
string cultivate_msg()
{
    return WHT "$N閉目盤膝﹐緩緩運轉明道心法﹐周身真氣流轉﹐心神漸入空明之境﹐"
               "神台澄澈如鏡﹐隱隱與天地鬼神之氣相通。\n" NOR;
}

// 內功火候：取 force 槽自身與所掛「dao force」心法二者之高者(同 dragon_force 之
// 門檻取法)﹐作為 recover/remedy 等級門檻的判準。
int dao_force_level(object me)
{
    int lv;

    lv = me->query_skill("force", 1);
    if( me->query_skill("dao force", 1) > lv )
        lv = me->query_skill("dao force", 1);
    return lv;
}

// exert recover -- 提升疲勞的「恢復最大值」(stats_max["fatigue"])﹐固本培元。
//   門檻：內功(force/dao force) >= DAO_RECOVER_LEVEL。
//   消耗：無(純運功固本)。效果：advance_stat("fatigue", +DAO_RECOVER_GAIN)。
int do_recover(object me)
{
    int before, after;

    if( dao_force_level(me) < DAO_RECOVER_LEVEL )
        return notify_fail(sprintf(
            "你明道心法火候未到(需內功 %d)﹐運不起這固本培元的功夫。\n",
            DAO_RECOVER_LEVEL));

    // fatigue 須已是有效屬性(max 已設)方能往上推。
    before = me->query_stat_maximum("fatigue");
    if( before <= 0 )
        return notify_fail("你體內並無疲勞可固﹐此式無從施為。\n");

    after = me->advance_stat("fatigue", DAO_RECOVER_GAIN);

    message_vision(HIW
        "$N閉目盤膝﹐運轉明道心法固本培元﹐周身真氣徐徐流轉滋養筋骨﹐"
        "舉手投足間隱隱透出一股不易困乏的精悍之氣。\n" NOR, me);
    tell_object(me, sprintf(HIW
        "你運轉明道心法固本培元﹐筋骨為之一壯。(疲勞恢復最大值 %d -> %d)\n" NOR,
        before, after));

    return 1;
}

// exert remedy -- 消飲水(water)化津為氣﹐回補精(gin)、氣(kee)、神(sen)當前值。
//   門檻：內功(force/dao force) >= DAO_REMEDY_LEVEL。
//   消耗：飲水 DAO_REMEDY_WATER 當前值。效果：三圍各 supplement_stat 當前值。
int do_remedy(object me)
{
    int gin_healed, kee_healed, sen_healed, drank;

    if( dao_force_level(me) < DAO_REMEDY_LEVEL )
        return notify_fail(sprintf(
            "你明道心法火候未到(需內功 %d)﹐化津為氣的功夫運轉不起。\n",
            DAO_REMEDY_LEVEL));

    // 飲水不足則化氣無源。query_stat 取當前值(= query_stat_current)。
    if( me->query_stat("water") < DAO_REMEDY_WATER )
        return notify_fail("你體內水氣不足﹐運轉明道心法化津為氣無從著手。\n");

    // 精氣神俱已飽滿(當前達可癒上限)則毋須回補﹐免白費飲水。
    if( me->query_stat_current("gin") >= me->query_stat_effective("gin")
    &&  me->query_stat_current("kee") >= me->query_stat_effective("kee")
    &&  me->query_stat_current("sen") >= me->query_stat_effective("sen") )
        return notify_fail("你精氣神俱已飽滿﹐此刻運轉明道心法並無增益。\n");

    // 消耗飲水當前值(consume_stat 只削 current)。
    drank = me->consume_stat("water", DAO_REMEDY_WATER, me);

    // 化津為氣：回補精氣神三圍當前值(supplement_stat 自動封頂於各圍 heal/max)。
    gin_healed = me->supplement_stat("gin", DAO_REMEDY_HEAL);
    kee_healed = me->supplement_stat("kee", DAO_REMEDY_HEAL);
    sen_healed = me->supplement_stat("sen", DAO_REMEDY_HEAL);

    message_vision(HIC
        "$N閉目盤膝﹐運轉明道心法化津為氣﹐周身水氣蒸騰內斂﹐"
        "化作絲絲清純真元注入丹田﹐精氣神為之一充。\n" NOR, me);
    tell_object(me, sprintf(HIW
        "你運轉明道心法化津為氣。(消飲水 %d﹐回精 %d、氣 %d、神 %d)\n" NOR,
        drank, gin_healed, kee_healed, sen_healed));

    return 1;
}

// exert recover/remedy -- 明道心法兩式運功補益。
// 其餘 func(含 "dao force" 本身打坐修煉)落回 FORCE 基底(打坐 / notify_fail)。
varargs int exert_function(object me, string func, object target)
{
    if( !objectp(me) ) me = this_player();
    if( !objectp(me) ) return 0;

    switch( func ) {
        case "recover": return do_recover(me);
        case "remedy":  return do_remedy(me);
    }

    return ::exert_function(me, func, target);
}

// vim: set ts=4 sw=4 syntax=lpc
