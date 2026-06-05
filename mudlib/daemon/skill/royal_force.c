// 大內心法 royal force -- 大內巡院「大內供奉/大內都統」進階(二轉)所授的上乘內功
//
// 大內心法為 docs 明列的大內巡院核心技能(見 docs/03-門派與武功/06-軍人-振武大內.md
// §2 大內巡院 soldier.royal-核心技能「大內心法 royal force」﹐並載其 lv10 起有
// refresh(消氣回精)/recover(消神回精氣)/royal(神威狀態提升護甲傷害)三式)。入門大內
// 巡院授的是大內罡氣(danei force)﹐進階「大內供奉」「大內都統」二脈方兼修這套更上乘
// 的大內心法。
//
// 修煉與 valid_enable 等共用機制由 FORCE(/std/force.c)基底提供﹔本檔註冊心法名、
// 登錄中文名「大內心法」、override cultivate_msg() 提供大內供奉一脈的打坐氣象﹐並
// 在此之上 override exert_function 以實作 docs L93-97 載明的 lv10 三式 refresh /
// recover / royal。字典 data/chinese.o 查無此 key﹐以 CHINESE_D->add_translate()
// 自行登錄。
//
// === lv10 三式(docs/03-門派與武功/06-軍人-振武大內.md L93-97) ===
// 精=gin、氣=kee、神=sen(見 feature/statistic.c)。三式比照龍圖丹派姊妹篇
// daemon/skill/zushang.c::exert_function(override 具名功能﹐消一態回另一態)建檔：
//   exert refresh -> 消氣回精：consume kee﹐折算回補 gin(當前 + 可癒上限)。
//   exert recover -> 消神回精氣：consume sen﹐折算回補 gin 與 kee。
//   exert royal   -> 神威狀態：暫時提升護甲(apply/armor)與傷害(apply/damage)﹐
//                    call_out 到期後以 add_temp(-N) 復原(鏡 cmds/std/wardance.c、
//                    daemon/skill/strategy.c::do_wis 之 add_temp + call_out -N 模型﹐
//                    不可 delete_temp﹐以保住其他來源的同鍵加成)。
//
// 門檻(docs L93「大內心法詳細(lv 10)」)：等級 >= 10 方能運使這三式。
//
// 派發路徑(cmds/std/exert.c::main L46)：玩家鍵入 `exert refresh`(或 recover/royal)。
// exert.c 取 me->skill_mapped("force")(= 已掛上的內功 key﹐此處為 "royal force")﹐
// 呼 SKILL_D("royal force")->exert_function(me, func, target)。本檔接到 func ∈
// {refresh,recover,royal} 即自行處理﹔其餘 func(含 "royal force" 本身打坐修煉)落回
// ::exert_function 由 FORCE 基底處理。此乃 zushang.c / dragon_force.c 的同型結構。
//
// runtime 鐵則：本式不涉 ::die()/destruct()(#10)﹐亦不 replace_program(#11)﹔
// 為內功 daemon(inherit FORCE)﹐非 F_VILLAGER NPC﹐不 include <weapon.h>。

#include <ansi.h>

inherit FORCE;

// === 三式門檻與消耗/效果參數(數值依 docs﹐未明者取合理可驗值)。集中於此便於調校。===
#define RF_MIN_LEVEL    10      // 三式門檻：等級下限(docs L93 lv 10)。

#define RF_REFRESH_KEE  40      // refresh：消氣(kee)量。
#define RF_RECOVER_SEN  40      // recover：消神(sen)量。

#define RF_ROYAL_ARMOR  30      // royal 神威：護甲(apply/armor)加成。
#define RF_ROYAL_DAMAGE 15      // royal 神威：傷害(apply/damage)加成。
#define RF_ROYAL_KEE    50      // royal 神威：入神威狀態所耗的氣(kee)。
#define RF_ROYAL_DURATION 30    // royal 神威：持續秒數(call_out 以秒計)。

// 前置宣告(lesson #12：自訂函式一律先前置宣告﹐免「定義前引用」編譯 Undefined
//   function﹐進而導致 daemon lazy-load 靜默失敗、exert 指令靜默回 0)。
varargs int exert_function(object me, string func, object target);
private int rf_gate(object me);
int rf_refresh(object me);
int rf_recover(object me);
int rf_royal(object me);
void rf_end_royal(object me);

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("royal force");
    // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
    CHINESE_D->add_translate("royal force", "大內心法");
    setup();
}

// 大內供奉/都統打坐運轉大內心法時所現的內功氣象。
string cultivate_msg()
{
    return WHT "$N閉目盤膝﹐緩緩運轉大內心法﹐周身似有一層神威護體真氣流轉﹐"
               "森嚴肅穆之中暗蘊宿衛禁中、護駕克敵的凜然煞氣。\n" NOR;
}

// 三式共用門檻：須等級達標(docs L93 lv 10)。通過回 1﹐否則 notify_fail 後回 0。
private int
rf_gate(object me)
{
    if( me->query_level() < RF_MIN_LEVEL ) {
        notify_fail(sprintf(
            "你大內心法火候未到(需等級 %d)﹐運轉不起這上乘的調息功夫。\n",
            RF_MIN_LEVEL));
        return 0;
    }
    return 1;
}

// ── refresh 消氣回精：consume kee﹐折算回補 gin 當前值與可癒上限。docs L94 ──
int
rf_refresh(object me)
{
    int gain;

    if( !rf_gate(me) ) return 0;

    if( me->query_stat_current("kee") < RF_REFRESH_KEE )
        return notify_fail("你體內真氣不足﹐無力運轉大內心法調息養精。\n");

    me->consume_stat("kee", RF_REFRESH_KEE, me);

    // 化氣為精：折算回補的 gin﹐隨大內心法火候提高。
    gain = RF_REFRESH_KEE + me->query_skill("royal force", 1) / 4;
    if( gain < 1 ) gain = 1;

    me->supplement_stat("gin", gain);   // 回 gin 當前值(自動封頂 heal/max)。
    me->heal_stat("gin", gain);         // 回 gin 可癒上限(自動封頂 max)。

    message_vision(WHT
        "$N凝神運轉大內心法﹐周身真氣內斂沉降﹐緩緩化作一縷精元歸入丹田。\n" NOR, me);
    tell_object(me, sprintf(HIW
        "你運轉大內心法調息養精。(消 kee %d﹐回 gin %d)\n" NOR,
        RF_REFRESH_KEE, gain));
    return 1;
}

// ── recover 消神回精氣：consume sen﹐折算回補 gin 與 kee。docs L95 ──
int
rf_recover(object me)
{
    int gain;

    if( !rf_gate(me) ) return 0;

    if( me->query_stat_current("sen") < RF_RECOVER_SEN )
        return notify_fail("你神識不足﹐無力運轉大內心法歸元復氣。\n");

    me->consume_stat("sen", RF_RECOVER_SEN, me);

    // 化神為精氣：折算回補的 gin 與 kee﹐隨大內心法火候提高。
    gain = RF_RECOVER_SEN + me->query_skill("royal force", 1) / 4;
    if( gain < 1 ) gain = 1;

    me->supplement_stat("gin", gain);   // 回精(gin)當前值。
    me->heal_stat("gin", gain);         // 回精(gin)可癒上限。
    me->supplement_stat("kee", gain);   // 回氣(kee)當前值。
    me->heal_stat("kee", gain);         // 回氣(kee)可癒上限。

    message_vision(WHT
        "$N閉目凝神﹐運轉大內心法歸元復氣﹐神識內收化作精氣周流百脈。\n" NOR, me);
    tell_object(me, sprintf(HIW
        "你運轉大內心法歸元復氣。(消 sen %d﹐回 gin/kee 各 %d)\n" NOR,
        RF_RECOVER_SEN, gain));
    return 1;
}

// ── royal 神威狀態：暫時提升護甲(apply/armor)與傷害(apply/damage)。docs L96-97 ──
// add_temp buff + call_out -N 復原﹐完全鏡 cmds/std/wardance.c 與
// daemon/skill/strategy.c::do_wis(用 add_temp(-N) 而非 delete_temp﹐保住其他來源
// 的同鍵加成)。護甲 apply/armor 由 resist_damage 讀(feature/char/combat.c:277)﹐
// 傷害 apply/damage 由 equip.c:259/combat.c:261 讀。
int
rf_royal(object me)
{
    if( !rf_gate(me) ) return 0;

    // 神威狀態尚在身上時不可重複進入(避免無限延長)。
    if( me->query_temp("royal_force_active") )
        return notify_fail("你神威護體之氣正盛﹐這股威勢尚未消退。\n");

    if( me->query_stat_current("kee") < RF_ROYAL_KEE )
        return notify_fail("你體內真氣不足﹐運不起這神威護體之勢。\n");

    me->consume_stat("kee", RF_ROYAL_KEE, me);

    me->set_temp("royal_force_active", 1);
    me->add_temp("apply/armor", RF_ROYAL_ARMOR);
    me->add_temp("apply/damage", RF_ROYAL_DAMAGE);
    me->set_temp("royal_force_callout",
        call_out("rf_end_royal", RF_ROYAL_DURATION, me));

    message_vision(HIW
        "$N運轉大內心法至極﹐周身驟然騰起一層森然神威﹐護體真氣如鐵壁環身﹐"
        "舉手投足間殺氣凜然﹗\n" NOR, me);
    tell_object(me, sprintf(HIW
        "你進入神威狀態﹐護甲與傷害大盛。(消 kee %d﹐持續 %d 秒)\n" NOR,
        RF_ROYAL_KEE, RF_ROYAL_DURATION));
    return 1;
}

// 神威狀態到期：把先前加的量「減回去」並清旗標。用 add_temp(-N)﹐不可 delete_temp。
void
rf_end_royal(object me)
{
    if( !objectp(me) ) return;
    me->add_temp("apply/armor", -RF_ROYAL_ARMOR);
    me->add_temp("apply/damage", -RF_ROYAL_DAMAGE);
    me->delete_temp("royal_force_active");
    me->delete_temp("royal_force_callout");
    tell_object(me, NOR "你周身那股森然神威漸漸消退了。\n");
}

// exert refresh/recover/royal -- 大內心法 lv10 三式(docs L93-97)。
// 其餘 func(含 "royal force" 本身)落回 FORCE 基底(打坐修煉 / notify_fail)。
varargs int exert_function(object me, string func, object target)
{
    if( !objectp(me) ) me = this_player();
    if( !objectp(me) ) return 0;

    switch( func ) {
    case "refresh": return rf_refresh(me);
    case "recover": return rf_recover(me);
    case "royal":   return rf_royal(me);
    }

    return ::exert_function(me, func, target);
}

// vim: set ts=4 sw=4 syntax=lpc
