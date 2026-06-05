// 龍圖心經 dragon force -- 龍圖丹派醫師門下的入門內功
//
// 內功(force)是被動的「力道乘數」：戰鬥時 COMBAT_D->fight() 讀 query_skill("force")
// 與 skill_mapped("force")，藉氣(kee)與功力百分比(force_ratio)放大攻擊力道，故內功
// daemon 不需攻擊招式表。玩家以 `enable force with dragon force` 掛上本心法後，再用
// `exert dragon force` 盤膝打坐修煉（見 /std/force.c 與 cmds/std/exert.c）。
//
// 修煉與 valid_enable 等共用機制一律由 FORCE(/std/force.c)基底提供；本檔在此之上
// override exert_function 以實作 docs 載明的「主動生丹」施法。
//
// === 主動生丹(docs/02-煉丹與書本系統.md L93、docs/03-方士-龍圖武陀.md L36) ===
// 龍圖心經練至火候後﹐方士可不動丹爐、不費藥材﹐純以心法「憑空生成」對應丹藥﹐
// 所耗者乃帳上的真金白銀(銀行存款)。四式：
//   exert refresh  -> 金鎖固精丸(refresh_pill)：澀精補氣。
//   exert heal     -> 小還丹    (minor_heal_pill)：療形傷、回 HP/kee。
//   exert mana     -> 醒神丹    (mana_pill)：提神回神(sen)。
//   exert relax    -> 養心丹    (relax_pill)：補精解疲勞(gin/fatigue)。
//
// 門檻(docs 載明)：等級 >= 30、悟性(int) >= 30、內功(force/dragon force) >= 90。
// 三者任一不足即 notify_fail 說明﹐不予生丹。
//
// 派發路徑(cmds/std/exert.c::main L46)：玩家鍵入 `exert refresh`(或 heal/mana/
// relax)。exert.c 取 me->skill_mapped("force")(= 已掛上的內功 key﹐此處為
// "dragon force")﹐呼 SKILL_D("dragon force")->exert_function(me, func, target)。
// 本檔接到 func ∈ {refresh,heal,mana,relax} 即自行生丹﹔其餘 func(含 "dragon force"
// 本身打坐修煉)落回 ::exert_function 由 FORCE 基底處理。此乃龍圖丹派姊妹篇
// daemon/skill/zushang.c::exert_function(override 具名功能 regenerate)的同型結構。
//
// 扣款機制(沿用既有錢莊系統 std/room/bank.c + obj/bankbond.c﹐不臆造)：
//   存款額存於 me->query("bank_account")(單位「文」﹐1 兩白銀 = 100 文)﹐
//   權威帳本為玩家隨身攜帶的「錢莊金契」bankbond(present("bankbond", me))。
//   扣款一律走 bond->transact(-cost)：該函式僅在 bank_account==bond.balance 時
//   生效﹐並同步更新二者﹐故扣後帳目仍相符﹐日後到錢莊 deposit/withdraw 不會被
//   判「帳目不對」而沒收金契。未隨身帶金契、或存款不足者﹐notify_fail 說明。
//
// runtime 鐵則：本式不涉 ::die()/destruct()(#10)﹐亦不 replace_program(#11)﹔
// 為內功 daemon(inherit FORCE)﹐非 F_VILLAGER NPC﹐不 include <weapon.h>。

#include <ansi.h>

inherit FORCE;

// === 生丹門檻(docs 載明) ===
#define DF_MIN_LEVEL    30      // 等級下限。
#define DF_MIN_INT      30      // 悟性(int)下限。
#define DF_MIN_FORCE    90      // 內功(force/dragon force)火候下限。

// === 各式生丹的藍本路徑與耗費的銀行存款(單位「文」) ===
// 額度比照各丹 base_value(憑空生成之「真材實料」成本)﹐docs 未明定故取此可驗值﹐
// 集中於此便於日後調校。1 兩 = 100 文。
#define DF_REFRESH_PILL "/obj/medication/alchemist/refresh_pill"
#define DF_REFRESH_COST 1000    // 金鎖固精丸 base_value 1000 ->  10 兩。
#define DF_HEAL_PILL    "/obj/medication/alchemist/minor_heal_pill"
#define DF_HEAL_COST    6000    // 小還丹       base_value 6000 ->  60 兩。
#define DF_MANA_PILL    "/obj/medication/alchemist/mana_pill"
#define DF_MANA_COST    300     // 醒神丹       base_value  260 ->   3 兩。
#define DF_RELAX_PILL   "/obj/medication/alchemist/relax_pill"
#define DF_RELAX_COST   500     // 養心丹       base_value  480 ->   5 兩。

// 前置宣告(lesson #12：自訂函式一律先前置宣告﹐免「定義前引用」編譯失敗)。
varargs int exert_function(object me, string func, object target);
int df_can_conjure(object me);
int df_conjure(object me, string blueprint, int cost);

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("dragon force");
    setup();
}

// 龍圖丹派弟子打坐運功時所現的內功氣象。
string cultivate_msg()
{
    return WHT "$N閉目盤膝﹐緩緩運轉龍圖心經﹐周身似有一股溫醇平和之氣循經流轉﹐"
               "默運吐納﹐溫養經脈。\n" NOR;
}

// 生丹門檻判定：等級、悟性、內功火候三者俱足方可。不足則 notify_fail 說明後回 0。
// 內功火候取 force 槽與 dragon force 心法二者之高者(docs：force/dragon force >= 90)。
int df_can_conjure(object me)
{
    int force_level;

    if( me->query_level() < DF_MIN_LEVEL )
        return notify_fail(sprintf(
            "你修為尚淺(需等級 %d)﹐龍圖心經運轉不起這生丹之力。\n", DF_MIN_LEVEL));

    if( me->query_attr("int") < DF_MIN_INT )
        return notify_fail(sprintf(
            "你悟性不足(需悟性 %d)﹐參不透龍圖心經憑空生丹的玄機。\n", DF_MIN_INT));

    force_level = me->query_skill("force", 1);
    if( me->query_skill("dragon force", 1) > force_level )
        force_level = me->query_skill("dragon force", 1);
    if( force_level < DF_MIN_FORCE )
        return notify_fail(sprintf(
            "你龍圖心經火候未到(需內功 %d)﹐丹氣凝而不聚﹐生不出丹來。\n",
            DF_MIN_FORCE));

    return 1;
}

// 生丹本體：扣銀行存款 cost(文)﹐成功則 new(blueprint) 一粒丹藥入懷。
//   - 扣款走隨身金契 bond->transact(-cost)(同步 bank_account﹐帳目不致失衡)。
//   - 滿載則 move(environment())(鏡 daemon/skill/strategy.c::do_money 之給物殼)。
// 成功回 1﹔任何不足回 0(均經 notify_fail 說明)。
int df_conjure(object me, string blueprint, int cost)
{
    object bond, pill;

    if( !df_can_conjure(me) )
        return 0;

    // 權威帳本：玩家須隨身攜帶錢莊金契﹐方能動帳上的存款。
    bond = present("bankbond", me);
    if( !objectp(bond) )
        return notify_fail("你身上沒帶著錢莊金契﹐動不了帳上的存款來生丹。\n");

    // 金契帳目須與存款相符(否則 transact 不生效)﹐並確認存款足夠。
    if( bond->query_balance() != me->query("bank_account") )
        return notify_fail("你的金契帳目對不上﹐快到錢莊重新核對。\n");
    if( me->query("bank_account") < cost )
        return notify_fail(sprintf(
            "你帳上的存款不足(需 %d 兩白銀)﹐生不起這爐丹。\n", cost / 100));

    // 先扣款：transact 在 bank_account==balance 時同步扣去 cost(文)。
    bond->transact(-cost);

    // 後生丹：new 藍本﹐move 給玩家﹔滿載則落地於環境。
    pill = new(blueprint);
    if( !objectp(pill) ) {
        // 生丹失敗(藍本載入異常)：把扣去的存款補回﹐免玩家平白損財。
        bond->transact(cost);
        return notify_fail("你心神一散﹐丹氣潰而不成﹐這爐丹生不出來。\n");
    }
    if( !pill->move(me) )
        pill->move(environment(me));

    message_vision(HIC
        "$N閉目掐訣﹐周身溫醇丹氣翻湧凝練﹐隨即化作一粒晶瑩丹藥﹐悄然落入掌心。\n"
        NOR, me);
    tell_object(me, sprintf(HIW
        "你運轉龍圖心經﹐憑空煉出一粒%s。(消存款 %d 兩白銀)\n" NOR,
        pill->name(), cost / 100));

    return 1;
}

// exert refresh/heal/mana/relax -- 龍圖心經主動生丹﹐消銀行存款生成對應丹藥。
// 其餘 func(含 "dragon force" 本身)落回 FORCE 基底(打坐修煉 / notify_fail)。
varargs int exert_function(object me, string func, object target)
{
    if( !objectp(me) ) me = this_player();
    if( !objectp(me) ) return 0;

    switch( func ) {
        case "refresh": return df_conjure(me, DF_REFRESH_PILL, DF_REFRESH_COST);
        case "heal":    return df_conjure(me, DF_HEAL_PILL,    DF_HEAL_COST);
        case "mana":    return df_conjure(me, DF_MANA_PILL,    DF_MANA_COST);
        case "relax":   return df_conjure(me, DF_RELAX_PILL,   DF_RELAX_COST);
    }

    return ::exert_function(me, func, target);
}

// vim: set ts=4 sw=4 syntax=lpc
