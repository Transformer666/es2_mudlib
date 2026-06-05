// 丹陽神功 sun force -- 天師派朱衣弟子的入門內功
//
// 天師派以火證道的根本吐納之術，溫煦火氣蒸騰、如烈焰焚天而藏護體罡正。
// 修煉與 valid_enable 等共用機制由 FORCE(/std/force.c)基底提供；本檔在此之上
// override cultivate_msg() 提供天師派朱衣自家的打坐氣象，並 override
// exert_function 以實作 docs 載明的三式運功：remedy / recover / sun fire。
//
// === docs(docs/03-門派與武功/02-道士-天師與茅山.md「丹陽神功 (sun force)」L88) ===
//   - 內功、等級 >= 15。
//   - remedy           ：消飲水回精氣神當前值。
//   - recover (lv 30)  ：提升疲勞恢復最大值。
//   - sun fire (lv 90) ：聚日術﹐僅日間可用﹐消 150 sen﹐暫提慧根、定力、咒文能力。
// remedy / recover 兩式與同門姊妹篇「明道心法 dao force」同型(docs 亦載二式)﹐惟
// 門檻不同：sun force 之 remedy 不分階(lv>=15 入門即可)、recover lv30﹔dao force
// 則 recover lv30、remedy lv60。故本檔 remedy / recover 完全鏡 daemon/skill/
// dao_force.c::do_remedy / do_recover 之已驗機制(只調門檻等級)。
//
//   remedy(門檻 lv>=15﹐消飲水 water 當前值)：
//     以體內水氣為引﹐化津為氣﹐回補精(gin)、氣(kee)、神(sen)三圍之「當前值」。
//     扣 water 以 consume_stat("water", N, me)(只削 current﹐見 statistic.c)﹔
//     回三圍當前值以 supplement_stat(自動封頂於各圍 heal/max﹐不溢出)。飲水不足
//     則 notify_fail 說明(渴而無津﹐化氣無源)。
//
//   recover(門檻 lv>=30﹐本式不耗三圍/飲水﹐純運功固本)：
//     運轉丹陽神功把疲勞的「恢復最大值」(stats_max["fatigue"])往上推﹐使日後能
//     承受更多研讀/施術而不致過勞。以 advance_stat("fatigue", +N) 改 max(見
//     feature/statistic.c::advance_stat 只動 stats_max)。
//
//   sun fire 聚日術(門檻 lv>=90﹐僅日間可用﹐消 150 sen)：
//     朱衣道士聚天地日精灌注己身﹐暫時大幅提升「慧根、定力、咒文能力」。
//       慧根   -> add_temp("apply/wis",   +N)(query_attr 讀 apply/<attr>﹐見
//                 feature/attribute.c:29)。
//       定力   -> add_temp("apply/cps",   +N)(同上)。
//       咒文能力-> add_temp("apply/spell", +N)(法力 query_ability("spell") 直接
//                 讀 apply/spell﹐見 feature/char/combat.c:117)。
//     即時 add_temp 上 buff、call_out 到期後以 add_temp(-N) 復原(不可 delete_temp﹐
//     會抹掉其他來源的同鍵加成)﹐完全鏡 daemon/skill/strategy.c::do_wis / end_wis
//     之 buff/復原模型。以 set_temp 旗標防重複疊加(避免無限延長)。
//     日間判定：localtime(time())[LT_HOUR] 取現實時辰﹐白晝 06:00-18:00 方可聚日﹐
//     完全鏡 cmds/std/sunpray.c(人類族「太陽神祈禱」聚陽光)之 daylight 判定。
//
// 派發路徑(cmds/std/exert.c::main)：玩家鍵入 `exert remedy` / `exert recover` /
// `exert sun fire`。exert.c 取 me->skill_mapped("force")(= 已掛上的內功 key﹐此處
// 為 "sun force")﹐呼 SKILL_D("sun force")->exert_function(me, func, target)。本檔
// 接到 func ∈ {remedy, recover, sun fire} 即自行處理﹔其餘 func(含 "sun force" 本身
// 打坐修煉)落回 ::exert_function 由 FORCE 基底處理。此乃 daemon/skill/dao_force.c、
// dragon_force.c、zushang.c override 具名功能、其餘落回基底的同型結構。
//
// runtime 鐵則：本式不涉 ::die()/destruct()(#10)﹐亦不 replace_program(#11)﹔
// 為內功 daemon(inherit FORCE)﹐非 F_VILLAGER NPC﹐不 include <weapon.h>。

#include <ansi.h>
#include <localtime.h>

inherit FORCE;

// === 三式運功的門檻與消耗/效果參數(docs 載明等級﹐量值為本次設計值﹐集中便調校) ===
#define SF_REMEDY_LEVEL     15      // remedy  門檻：內功(force/sun force) >= 15(docs：內功 lv>=15)。
#define SF_REMEDY_WATER     30      // remedy  每次消耗的飲水(water)當前值。
#define SF_REMEDY_HEAL      30      // remedy  每圍(精/氣/神)回補的當前值量。

#define SF_RECOVER_LEVEL    30      // recover 門檻：內功(force/sun force) >= 30(docs lv30)。
#define SF_RECOVER_GAIN     20      // recover 每次抬升疲勞恢復最大值的量。

#define SF_SUNFIRE_LEVEL    90      // sun fire 門檻：內功(force/sun force) >= 90(docs lv90)。
#define SF_SUNFIRE_SEN      150     // sun fire 消耗的神(sen)(docs：消 150 sen)。
#define SF_SUNFIRE_WIS      5       // sun fire 暫提慧根(apply/wis)的量。
#define SF_SUNFIRE_CPS      5       // sun fire 暫提定力(apply/cps)的量。
#define SF_SUNFIRE_SPELL    20      // sun fire 暫提咒文能力(法力 apply/spell)的量。
#define SF_SUNFIRE_DURATION 60      // sun fire buff 持續秒數(call_out 以秒計)。

// 前置宣告(lesson #12：凡「定義前引用」之自訂函式一律先前置宣告﹐免編譯
// Undefined function、daemon lazy-load 失敗、SKILL_D 靜默回 0→指令靜默回 0)。
varargs int exert_function(object me, string func, object target);
int sun_force_level(object me);
int do_remedy(object me);
int do_recover(object me);
int do_sun_fire(object me);
void end_sun_fire(object me);

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("sun force");
    setup();
}

// 天師派朱衣弟子打坐運功時所現的內功氣象。
string cultivate_msg()
{
    return HIR "$N閉目盤膝﹐緩緩運轉丹陽神功﹐周身似有一股溫煦的火氣蒸騰不息﹐"
               "丹田之中一輪赤日冉冉升起﹐熾熱之中自有一股護體的罡正。\n" NOR;
}

// 內功火候：取 force 槽自身與所掛「sun force」心法二者之高者(同 dao_force /
// dragon_force 之門檻取法)﹐作為 remedy / recover / sun fire 等級門檻的判準。
int sun_force_level(object me)
{
    int lv;

    lv = me->query_skill("force", 1);
    if( me->query_skill("sun force", 1) > lv )
        lv = me->query_skill("sun force", 1);
    return lv;
}

// exert remedy -- 消飲水(water)化津為氣﹐回補精(gin)、氣(kee)、神(sen)當前值。
//   門檻：內功(force/sun force) >= SF_REMEDY_LEVEL(docs：內功 lv>=15)。
//   消耗：飲水 SF_REMEDY_WATER 當前值。效果：三圍各 supplement_stat 當前值。
//   鏡 daemon/skill/dao_force.c::do_remedy 之已驗機制。
int do_remedy(object me)
{
    int gin_healed, kee_healed, sen_healed, drank;

    if( sun_force_level(me) < SF_REMEDY_LEVEL )
        return notify_fail(sprintf(
            "你丹陽神功火候未到(需內功 %d)﹐化津為氣的功夫運轉不起。\n",
            SF_REMEDY_LEVEL));

    // 飲水不足則化氣無源。query_stat 取當前值(= query_stat_current)。
    if( me->query_stat("water") < SF_REMEDY_WATER )
        return notify_fail("你體內水氣不足﹐運轉丹陽神功化津為氣無從著手。\n");

    // 精氣神俱已飽滿(當前達可癒上限)則毋須回補﹐免白費飲水。
    if( me->query_stat_current("gin") >= me->query_stat_effective("gin")
    &&  me->query_stat_current("kee") >= me->query_stat_effective("kee")
    &&  me->query_stat_current("sen") >= me->query_stat_effective("sen") )
        return notify_fail("你精氣神俱已飽滿﹐此刻運轉丹陽神功並無增益。\n");

    // 消耗飲水當前值(consume_stat 只削 current)。
    drank = me->consume_stat("water", SF_REMEDY_WATER, me);

    // 化津為氣：回補精氣神三圍當前值(supplement_stat 自動封頂於各圍 heal/max)。
    gin_healed = me->supplement_stat("gin", SF_REMEDY_HEAL);
    kee_healed = me->supplement_stat("kee", SF_REMEDY_HEAL);
    sen_healed = me->supplement_stat("sen", SF_REMEDY_HEAL);

    message_vision(HIR
        "$N閉目盤膝﹐運轉丹陽神功化津為氣﹐周身水氣蒸騰內斂﹐丹田赤日溫煦﹐"
        "化作絲絲清純真元注入經脈﹐精氣神為之一充。\n" NOR, me);
    tell_object(me, sprintf(HIW
        "你運轉丹陽神功化津為氣。(消飲水 %d﹐回精 %d、氣 %d、神 %d)\n" NOR,
        drank, gin_healed, kee_healed, sen_healed));

    return 1;
}

// exert recover -- 提升疲勞的「恢復最大值」(stats_max["fatigue"])﹐固本培元。
//   門檻：內功(force/sun force) >= SF_RECOVER_LEVEL(docs lv30)。
//   消耗：無(純運功固本)。效果：advance_stat("fatigue", +SF_RECOVER_GAIN)。
//   鏡 daemon/skill/dao_force.c::do_recover 之已驗機制。
int do_recover(object me)
{
    int before, after;

    if( sun_force_level(me) < SF_RECOVER_LEVEL )
        return notify_fail(sprintf(
            "你丹陽神功火候未到(需內功 %d)﹐運不起這固本培元的功夫。\n",
            SF_RECOVER_LEVEL));

    // fatigue 須已是有效屬性(max 已設)方能往上推。
    before = me->query_stat_maximum("fatigue");
    if( before <= 0 )
        return notify_fail("你體內並無疲勞可固﹐此式無從施為。\n");

    after = me->advance_stat("fatigue", SF_RECOVER_GAIN);

    message_vision(HIR
        "$N閉目盤膝﹐運轉丹陽神功固本培元﹐丹田赤日的溫煦火氣徐徐流轉滋養筋骨﹐"
        "舉手投足間隱隱透出一股不易困乏的精悍之氣。\n" NOR, me);
    tell_object(me, sprintf(HIW
        "你運轉丹陽神功固本培元﹐筋骨為之一壯。(疲勞恢復最大值 %d -> %d)\n" NOR,
        before, after));

    return 1;
}

// exert sun fire -- 聚日術：僅日間可用﹐消 150 sen﹐暫提慧根、定力、咒文能力。
//   門檻：內功(force/sun force) >= SF_SUNFIRE_LEVEL(docs lv90) 且 現實時辰白晝。
//   消耗：神(sen) SF_SUNFIRE_SEN。效果：add_temp 上三項 buff﹐SF_SUNFIRE_DURATION
//         秒後 call_out end_sun_fire 以 add_temp(-N) 復原(鏡 strategy.c::do_wis)。
//   日間判定：localtime(time())[LT_HOUR] 白晝 06:00-18:00(鏡 cmds/std/sunpray.c)。
int do_sun_fire(object me)
{
    int hour;

    if( sun_force_level(me) < SF_SUNFIRE_LEVEL )
        return notify_fail(sprintf(
            "你丹陽神功火候未到(需內功 %d)﹐聚不起這聚日的功夫。\n",
            SF_SUNFIRE_LEVEL));

    // 聚日術須借天上日精﹐僅日間(白晝 06:00-18:00)可施(鏡 cmds/std/sunpray.c)。
    hour = localtime(time())[LT_HOUR];
    if( hour < 6 || hour >= 18 )
        return notify_fail("此刻金烏西沉﹐天無日精可聚﹐丹陽神功的聚日術無從施展。\n");

    // 神識不足以引聚日精。
    if( me->query_stat("sen") < SF_SUNFIRE_SEN )
        return notify_fail(sprintf(
            "你神識不足(需神 %d)﹐運不起聚日的功夫。\n", SF_SUNFIRE_SEN));

    // 已在聚日 buff 中者不重複疊加(避免無限延長)。
    if( me->query_temp("sun_fire_active") )
        return notify_fail("你身上的日精尚熾﹐此刻無須再聚。\n");

    // 消耗神(sen)當前值(consume_stat 只削 current)。
    me->consume_stat("sen", SF_SUNFIRE_SEN, me);

    // 上 buff：慧根(apply/wis)、定力(apply/cps)、咒文能力(法力 apply/spell)。
    me->set_temp("sun_fire_active", 1);
    me->add_temp("apply/wis", SF_SUNFIRE_WIS);
    me->add_temp("apply/cps", SF_SUNFIRE_CPS);
    me->add_temp("apply/spell", SF_SUNFIRE_SPELL);
    me->set_temp("sun_fire_callout",
        call_out("end_sun_fire", SF_SUNFIRE_DURATION, me));

    message_vision(HIR
        "$N仰首向天﹐運轉丹陽神功聚日之術﹐周身赤焰大盛﹐天上日精如萬縷金線垂落"
        "灌注己身﹐霎時神台澄明、定力如山、咒法之力暴漲﹗\n" NOR, me);
    tell_object(me, sprintf(HIW
        "你聚天地日精灌注己身﹐慧根、定力與咒文能力大為精進。"
        "(消神 %d﹐慧根 +%d、定力 +%d、咒文能力 +%d﹐持續 %d 秒)\n" NOR,
        SF_SUNFIRE_SEN, SF_SUNFIRE_WIS, SF_SUNFIRE_CPS, SF_SUNFIRE_SPELL,
        SF_SUNFIRE_DURATION));

    return 1;
}

// 聚日術 buff 到期：把先前加的量「減回去」並清旗標。用 add_temp(-N)﹐不可
// delete_temp(會抹掉其他來源的同鍵加成)。鏡 strategy.c::end_wis。
void end_sun_fire(object me)
{
    if( !objectp(me) ) return;
    me->add_temp("apply/wis", -SF_SUNFIRE_WIS);
    me->add_temp("apply/cps", -SF_SUNFIRE_CPS);
    me->add_temp("apply/spell", -SF_SUNFIRE_SPELL);
    me->delete_temp("sun_fire_active");
    me->delete_temp("sun_fire_callout");
    tell_object(me, NOR "你身上灌注的日精漸漸消散﹐慧根、定力與咒法之力復歸於常。\n");
}

// exert remedy/recover/sun fire -- 丹陽神功三式運功。
// 其餘 func(含 "sun force" 本身打坐修煉)落回 FORCE 基底(打坐 / notify_fail)。
varargs int exert_function(object me, string func, object target)
{
    if( !objectp(me) ) me = this_player();
    if( !objectp(me) ) return 0;

    switch( func ) {
        case "remedy":   return do_remedy(me);
        case "recover":  return do_recover(me);
        case "sun fire": return do_sun_fire(me);
    }

    return ::exert_function(me, func, target);
}

// vim: set ts=4 sw=4 syntax=lpc
