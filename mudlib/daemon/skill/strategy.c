// 戰術兵法 strategy -- 振武軍營(soldier.ber)軍人「戰場後勤」的兵法技能
//
// 來歷(docs/03-門派與武功/06-軍人-振武大內.md L29、L33-37、L53-62、L119-130)：
// 戰術兵法是振武軍營三大核心技能之一(berserk / powerblow / strategy)﹐在五十斤大石
// 處 train﹐以 `tactic <戰術> (<目標>)` 施展。docs 把軍人定位為「物理戰士 + 戰場後勤」
// 的雙路線設計﹐而 strategy 正是後勤一路的看家本事：可一人補給整個團隊(mass_aid)、
// 送糧(supply)、送錢(money)、送 buff(wis)﹐進階「軍師」線更受法術強度額外加成。
//
// docs 載明的各戰術消耗/效果(本檔即照此實作)：
//   first_aid 急救  ：消 50 神(sen)→回補施術者自身的精氣(gin/kee)。docs L35。
//   charge    虎襲  ：消 5% 精氣(gin)→撞擊目標﹐令其 delay 1(短暫遲滯)。docs L36/L127。
//   mass_aid  大急救：消 500 戰功(score military service)→恢復房間內所有人「氣與形體」
//                     (gin/kee/sen/HP)。docs L58/L126。
//   supply    補給  ：消 500 戰功→運出大量饅頭(/obj/food/manto)給房內隊友。docs L59/L128。
//   money     錢糧  ：消 1000 戰功→運出大量白銀(/obj/money/silver)給施術者。docs L60/L128。
//   wis       賦予  ：消 250 戰功→提升房間內所有人「慧根(wis)與護甲(armor)」(暫時 buff﹐
//                     持續數心跳後復原)。docs L61/L129。
// 數值一律照 docs﹔docs 未明給之細節(回補量、饅頭/白銀數量、buff 量與秒數)取合理且可驗值。
//
// 派發路徑(cmds/std/tactic.c)：玩家鍵入 `tactic <戰術> [目標]`。tactic.c::main 取
// me->skill_mapped("strategy")(或退而取 "strategy" 本身)﹐呼
// SKILL_D("strategy")->tactic_function(me, 戰術名, target)。本檔依 func 分派各戰術﹐
// 不識者落回 notify_fail。鏡 daemon/skill/zushang.c 之 exert_function 建檔模型。
//
// 機制對齊(已驗範式)：
//   * 狀態消耗/回補：consume_stat(削 current)、supplement_stat(補 current 封頂 heal/max)、
//     heal_stat(補可癒上限封頂 max)、query_stat_current/maximum(見 feature/statistic.c)。
//     精氣 = gin(精)+kee(氣)﹔「氣與形體」= gin/kee/sen/HP。
//   * 戰功軸：gain_score("military service", N) 加分(soldier.c::brother_praise 用同 key)﹔
//     消耗即 gain_score(course, -cost)(add 負值﹐見 feature/char/score.c::gain_score →
//     add("score/"+course, xp))。query_score("military service") 讀現值。
//   * delay(charge)：對 target->start_busy(N) 施加硬直﹐鏡 berserk/wardance 之 start_busy。
//   * 暫時 buff(wis)：add_temp("apply/wis", N)(query_attr 讀 apply/<attr>﹐feature/
//     attribute.c:29)+ add_temp("apply/armor", N)(resist_damage 讀 apply/armor﹐
//     feature/char/combat.c:277)﹐call_out 後以 add_temp(-N) 復原﹐**不可 delete_temp**
//     (會抹掉其他來源的同鍵加成)﹐完全鏡 cmds/std/wardance.c 之 buff/復原模型。
//   * 給物：new(藍本)->set_amount(N)->move(對象)﹐滿載則 move(environment)(鏡
//     d/zhaoyin/npc/farmer.c、d/capital/npc/zhaoxiaojiu.c)。
//
// runtime 鐵則：本檔不涉 ::die()/destruct()(#10)、不 replace_program(#11)﹔為技能 daemon
// (inherit SKILL﹐非 F_VILLAGER NPC)﹐不 include <weapon.h>(無 nomask 衝突之虞)。

#include <ansi.h>

inherit SKILL;

// ── 戰術消耗/效果參數(數值依 docs﹐未明者取合理可驗值)。集中於此便於平衡微調。──
#define SCORE_COURSE        "military service"  // 戰功軸 key(同 daemon/class/soldier.c)。

#define FIRST_AID_SEN       50      // 急救：消 50 神(docs L35)。
#define FIRST_AID_DELAY     1       // 急救：delay 1(docs L35)。

#define CHARGE_GIN_PCT      5       // 虎襲：消 5% 精氣現值(docs L36)。
#define CHARGE_DELAY        1       // 虎襲：撞擊目標 delay 1(docs L36)。

#define MASS_AID_SCORE      500     // 大急救：消 500 戰功(docs L58)。

#define SUPPLY_SCORE        500     // 補給：消戰功運大量饅頭(docs L59﹐取與大急救同階 500)。
#define SUPPLY_BASE         50      // 補給：基礎饅頭數(再加兵法火候加成)。

#define MONEY_SCORE         1000    // 錢糧：消 1000 戰功運大量白銀(docs L60)。
#define MONEY_BASE          50      // 錢糧：基礎白銀「兩」數(再加兵法火候加成)。

#define WIS_SCORE           250     // 賦予：消 250 戰功(docs L61)。
#define WIS_BUFF            5       // 賦予：慧根(wis)加成量。
#define WIS_ARMOR           20      // 賦予：護甲(apply/armor)加成量。
#define WIS_DURATION        30      // 賦予：buff 持續秒數(call_out 以秒計)。

// 前置宣告：本檔多個函式於定義前先被引用(enough_score 用 query_score_of、tactic_function
// 之 switch 用各 do_*)，LPC 須先宣告否則「Undefined function」編譯失敗(已驗踩坑)。
private int enough_score(object me, int cost);
private int query_score_of(object me);
private void spend_score(object me, int cost);
int do_first_aid(object me, object target);
int do_charge(object me, object target);
int do_mass_aid(object me, object target);
int do_supply(object me, object target);
int do_money(object me, object target);
int do_wis(object me, object target);

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("strategy");
    // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示(字典已有則覆寫同值)。
    CHINESE_D->add_translate("strategy", "戰術兵法");
    setup();
}

// 戰術兵法為主動施展的後勤兵法﹐不佔 enable(內功/武功)槽﹐故 valid_enable 回 0。
int
valid_enable(string usage)
{
    return 0;
}

// 戰功不足的共用檢查。course 即 SCORE_COURSE﹐cost 為所需戰功。
private int
enough_score(object me, int cost)
{
    return query_score_of(me) >= cost;
}

private int
query_score_of(object me)
{
    return (int)me->query_score(SCORE_COURSE);
}

// 扣戰功：gain_score 加負值即扣(見 feature/char/score.c::gain_score)。
private void
spend_score(object me, int cost)
{
    me->gain_score(SCORE_COURSE, -cost);
}

// ── tactic_function(me, func, target) ──
// tactic.c::main 派發至此。依 func 施展各戰術﹔不識之 func 落回 notify_fail。
varargs int
tactic_function(object me, string func, object target)
{
    if( !objectp(me) ) me = this_player();
    if( !objectp(me) ) return 0;
    if( !stringp(func) )
        return notify_fail("你要施展哪一式兵法﹖\n");

    switch( func ) {
    case "first_aid": return do_first_aid(me, target);
    case "charge":    return do_charge(me, target);
    case "mass_aid":  return do_mass_aid(me, target);
    case "supply":    return do_supply(me, target);
    case "money":     return do_money(me, target);
    case "wis":       return do_wis(me, target);
    default:
        return notify_fail("你並不會「" + func + "」這一式兵法。\n");
    }
}

// ── first_aid 急救：消 50 神→回補自身精氣(gin/kee)。docs L35 ──
// docs「回精氣」未明給回補量﹐取隨兵法火候成長之合理值(消去的神識折為氣血)。
int
do_first_aid(object me, object target)
{
    int heal;

    if( me->query_stat_current("sen") < FIRST_AID_SEN )
        return notify_fail("你神識不足﹐無力施展急救之術。\n");

    me->consume_stat("sen", FIRST_AID_SEN, me);

    // 回補量：神識折為氣血﹐隨戰術兵法火候提高(docs 軍師線「受法術技巧影響」之基礎版)。
    heal = FIRST_AID_SEN + me->query_skill("strategy", 1);
    if( heal < 1 ) heal = 1;

    // 回精(gin)與氣(kee)當前值﹔supplement_stat 自動封頂於 heal/max。
    me->supplement_stat("gin", heal);
    me->supplement_stat("kee", heal);

    message_vision(HIG
        "$N按兵書所載急救之法﹐取出金創藥草為自己迅速包紮療傷。\n" NOR, me);
    tell_object(me, sprintf(HIW
        "你依兵法急救﹐氣血為之一振。(消 sen %d﹐回 gin/kee 各 %d)\n" NOR,
        FIRST_AID_SEN, heal));

    me->start_busy(FIRST_AID_DELAY);
    return 1;
}

// ── charge 虎襲：消 5% 精氣→撞擊目標令其 delay 1。docs L36/L127 ──
int
do_charge(object me, object target)
{
    int cost;

    if( !objectp(target) || !target->is_character() )
        return notify_fail("你要虎襲哪一個目標﹖\n");
    if( target == me )
        return notify_fail("你總不能拿自己來撞罷﹖\n");
    if( environment(target) != environment(me) )
        return notify_fail("這裡並沒有這個目標。\n");

    // 消耗現值的 5% 精(gin)。
    cost = me->query_stat_current("gin") * CHARGE_GIN_PCT / 100;
    if( cost < 1 ) cost = 1;
    if( me->query_stat_current("gin") < cost )
        return notify_fail("你的精力不足以發動虎襲。\n");

    me->consume_stat("gin", cost, me);

    message_vision(HIR
        "$N低喝一聲﹐肩頭一沉﹐如猛虎下山般狠狠撞向$n﹗\n" NOR, me, target);
    tell_object(target, HIR "你被狠狠撞了個踉蹌﹐一時手忙腳亂﹗\n" NOR);

    // 撞擊令目標短暫遲滯(delay 1)：對 target 施加硬直﹐鏡 berserk/wardance 之 start_busy。
    target->start_busy(CHARGE_DELAY);

    me->start_busy(1);
    return 1;
}

// ── mass_aid 大急救：消 500 戰功→恢復房間內所有人「氣與形體」(gin/kee/sen/HP)。docs L58/L126 ──
int
do_mass_aid(object me, object target)
{
    object env, ob;
    int heal, n;

    if( !enough_score(me, MASS_AID_SCORE) )
        return notify_fail(sprintf("你的戰功不足(需 %d)﹐無力統籌這場大急救。\n",
            MASS_AID_SCORE));

    env = environment(me);
    if( !objectp(env) )
        return notify_fail("你身在虛空﹐無從施展。\n");

    spend_score(me, MASS_AID_SCORE);

    // 回補量隨兵法火候成長。對房內每個活物回 gin/kee/sen 當前值與 HP。
    heal = 50 + me->query_skill("strategy", 1);
    if( heal < 1 ) heal = 1;

    message_vision(HIY
        "$N展開行軍兵書﹐調度有方﹐喝令隨軍醫官為全場將士療傷止血﹗\n" NOR, me);

    foreach(ob in all_inventory(env)) {
        if( !objectp(ob) || !ob->is_character() ) continue;
        ob->supplement_stat("gin", heal);
        ob->supplement_stat("kee", heal);
        ob->supplement_stat("sen", heal);
        ob->supplement_stat("HP", heal);
        n++;
    }

    tell_object(me, sprintf(HIW
        "你統籌大急救﹐全場 %d 人氣血形體俱有起色。(消 %d 戰功﹐每人回約 %d)\n" NOR,
        n, MASS_AID_SCORE, heal));
    me->start_busy(1);
    return 1;
}

// ── supply 補給：消 500 戰功→運出大量饅頭給房內隊友。docs L59/L128 ──
int
do_supply(object me, object target)
{
    object env, ob, manto;
    int count, n;

    if( !enough_score(me, SUPPLY_SCORE) )
        return notify_fail(sprintf("你的戰功不足(需 %d)﹐調不動這批糧秣。\n",
            SUPPLY_SCORE));

    env = environment(me);
    if( !objectp(env) )
        return notify_fail("你身在虛空﹐無從運糧。\n");

    spend_score(me, SUPPLY_SCORE);

    // 饅頭數量隨兵法火候成長(docs 範例「軍師 supply 可達 400~420 顆」之基礎版)。
    count = SUPPLY_BASE + me->query_skill("strategy", 1);
    if( count < 1 ) count = 1;

    message_vision(HIY
        "$N展開兵書一揮手﹐後方輜重隊推來一車冒著熱氣的饅頭﹐分發給在場眾人﹗\n" NOR, me);

    // 給房內每個活物各一堆饅頭(COMBINED_ITEM﹐set_amount 後 move﹔滿載落地)。
    foreach(ob in all_inventory(env)) {
        if( !objectp(ob) || !ob->is_character() ) continue;
        manto = new("/obj/food/manto");
        manto->set_amount(count);
        if( !manto->move(ob) ) manto->move(env);
        n++;
    }

    tell_object(me, sprintf(HIW
        "你調度補給﹐運出饅頭分發給在場 %d 人(每份 %d 個)。(消 %d 戰功)\n" NOR,
        n, count, SUPPLY_SCORE));
    me->start_busy(1);
    return 1;
}

// ── money 錢糧：消 1000 戰功→運出大量白銀給施術者。docs L60/L128 ──
int
do_money(object me, object target)
{
    object silver;
    int amount;

    if( !enough_score(me, MONEY_SCORE) )
        return notify_fail(sprintf("你的戰功不足(需 %d)﹐調不出這批餉銀。\n",
            MONEY_SCORE));

    spend_score(me, MONEY_SCORE);

    // 白銀「兩」數隨兵法火候成長。
    amount = MONEY_BASE + me->query_skill("strategy", 1);
    if( amount < 1 ) amount = 1;

    silver = new("/obj/money/silver");
    silver->set_amount(amount);
    if( !silver->move(me) ) silver->move(environment(me));

    message_vision(HIY
        "$N展開兵書一聲令下﹐軍需官抬來一箱沉甸甸的雪花白銀。\n" NOR, me);
    tell_object(me, sprintf(HIW
        "你調度錢糧﹐運出白銀 %s兩入懷。(消 %d 戰功)\n" NOR,
        chinese_number(amount), MONEY_SCORE));
    me->start_busy(1);
    return 1;
}

// ── wis 賦予：消 250 戰功→提升房間內所有人慧根(wis)與護甲(armor)。docs L61/L129 ──
// 暫時 buff：add_temp("apply/wis"/"apply/armor", N)﹐call_out 後以 add_temp(-N) 復原。
// 完全鏡 cmds/std/wardance.c：用 add_temp(-N) 而非 delete_temp(以保住其他來源的同鍵加成)。
int
do_wis(object me, object target)
{
    object env, ob;
    int n;

    if( !enough_score(me, WIS_SCORE) )
        return notify_fail(sprintf("你的戰功不足(需 %d)﹐無力為全軍賦予。\n",
            WIS_SCORE));

    env = environment(me);
    if( !objectp(env) )
        return notify_fail("你身在虛空﹐無從賦予。\n");

    spend_score(me, WIS_SCORE);

    message_vision(HIC
        "$N誦讀兵書韜略﹐一席運籌帷幄的方略灌注全場將士心神﹐眾人但覺神智清明、護體生輝﹗\n" NOR,
        me);

    foreach(ob in all_inventory(env)) {
        if( !objectp(ob) || !ob->is_character() ) continue;
        // 已在賦予 buff 中者不重複疊加(避免無限延長)。
        if( ob->query_temp("strategy_wis_active") ) continue;
        ob->set_temp("strategy_wis_active", 1);
        ob->add_temp("apply/wis", WIS_BUFF);
        ob->add_temp("apply/armor", WIS_ARMOR);
        ob->set_temp("strategy_wis_callout",
            call_out("end_wis", WIS_DURATION, ob));
        tell_object(ob, HIC "你只覺慧根頓開、護體之氣大盛。\n" NOR);
        n++;
    }

    tell_object(me, sprintf(HIW
        "你為全場 %d 人賦予慧根與護甲。(消 %d 戰功﹐持續 %d 秒)\n" NOR,
        n, WIS_SCORE, WIS_DURATION));
    me->start_busy(1);
    return 1;
}

// 賦予 buff 到期：把先前加的量「減回去」並清旗標。用 add_temp(-N)﹐不可 delete_temp。
void
end_wis(object ob)
{
    if( !objectp(ob) ) return;
    ob->add_temp("apply/wis", -WIS_BUFF);
    ob->add_temp("apply/armor", -WIS_ARMOR);
    ob->delete_temp("strategy_wis_active");
    ob->delete_temp("strategy_wis_callout");
    tell_object(ob, NOR "你方才那股清明的賦予之力漸漸消退了。\n");
}

// vim: set ts=4 sw=4 syntax=lpc
