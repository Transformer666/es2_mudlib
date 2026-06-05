// 丹道【黃白之術】 alchemy-wealth -- 龍圖丹派(alchemist.dragon)方士的點石成金之術
//
// 來歷(docs/03-門派與武功/07-方士-龍圖武陀.md L34、docs/02-遊戲系統與機制/
// 06-煉丹與書本系統.md L88-91)：黃白之術為龍圖方士的「煉金」祕法﹐以金印(gold
// seal)、銀印(silver seal)封物﹐將身上一件物品就地化作等值的真金白銀。docs 明載
// 此為龍圖方士「賺錢好門路」之一﹐典型玩家 Vvcheng 黃白之術練至 200(+3)﹐以神農 /
// 黃白之術為主收益。
//
// === 機制(docs L89 載明) ===
//   conjure gold seal on <物品>   -> 化物為黃金(/obj/money/gold)。
//   conjure silver seal on <物品> -> 化物為碎銀(/obj/money/silver)。
//   * 物品價值(query("value")﹐單位「文」)滿 500 文者﹐須技能等級 > 物品價/10000﹐
//     方鎮得住其「物性」而不反噬(高價之物難化﹐火候不足點不動)。
//   * 每次施術消 15 神(sen)﹐不論成敗門檻﹐通過檢查正式行法時才扣。
//   * 化成的錢額 = 物品價值(文)﹐折成對應幣別的「枚數」(set_amount)：
//       gold  base_value 10000 文/枚 -> amount = value/10000(不足一枚者進一)。
//       silver base_value  100 文/枚 -> amount = value/100  (不足一枚者進一)。
//     原物 destruct(化去)。
//
// === 派發路徑(cmds/std/conjure.c) ===
// 黃白之術掛在 magic 槽(非 spells)﹐走 conjure 指令﹐與本門 dragon force(force 槽、
// exert)、神農之術(magic 槽、conjure)各行其道。玩家 `enable magic with alchemy-wealth`
// 後﹐`conjure gold seal on <物品>`(或 silver seal)。conjure.c::main 將咒名中的空白
// 換成底線(故收到 "gold_seal" / "silver_seal")﹐取 me->skill_mapped("magic")(= 已掛
// 上的 magic key﹐此處為 "alchemy-wealth")﹐呼 SKILL_D("alchemy-wealth")->
// conjure_magic(me, spl, target)——本檔實作之。target 為 conjure.c 以 present() 在環境
// /身上解出的物品(conjure <咒> on <目標>)。此乃龍圖丹派姊妹篇 taoism-cloud.c::
// conjure_magic(亦 magic 槽、override valid_enable 認 "magic") 的同型結構。
//
// runtime 鐵則：本式不涉 ::die()/destruct() 於 living(#10)﹐亦不 replace_program
// (#11)﹔僅 destruct 被點化的「死物」物品(非 living)。為 magic daemon(inherit
// /std/magic)﹐非 F_VILLAGER NPC﹐不 include <weapon.h>。

#include <ansi.h>

inherit "/std/magic";

// === 黃白之術參數(docs L89 載明) ===
#define AW_SEN_COST     15      // 每次施術消耗的神(sen)。
#define AW_GATE_VALUE   500     // 物品價值門檻(文)：滿此值者才需技能等級檢定。
#define AW_GATE_DIV     10000   // 高價物門檻除數：須 技能等級 > 物品價/AW_GATE_DIV。

// === 化成幣別的藍本路徑與每枚面值(文) ===
// gold/silver 為既有貨幣物件(obj/money/gold.c base_value 10000、silver.c 100)。
// gold 無 globals.h 巨集(只有 COIN_OB/SILVER_OB)﹐故此處直書路徑﹐集中於此便於調校。
#define AW_GOLD_OB      "/obj/money/gold"
#define AW_GOLD_FACE    10000   // 黃金每枚 10000 文(1 兩黃金)。
#define AW_SILVER_OB    "/obj/money/silver"
#define AW_SILVER_FACE  100     // 碎銀每枚 100 文(1 兩白銀)。

// 前置宣告(lesson #12：自訂函式一律先前置宣告﹐免「定義前引用」編譯失敗﹐
// 並免 daemon lazy-load 靜默失敗)。
varargs int conjure_magic(object me, string spl, object target);
int aw_transmute(object me, object target, string money_ob, int face, string metal);

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("alchemy-wealth");
    // 自行登錄中文名﹐字典查無此 key 時 to_chinese()/enable/skills 仍可工整顯示。
    CHINESE_D->add_translate("alchemy-wealth", "黃白之術");
    setup();
}

// 黃白之術掛在 magic 槽(走 conjure)﹐而非 spells 槽(走 cast)。
// 覆寫 /std/magic.c 的 valid_enable(原本只認 "spells")﹐鏡 taoism-cloud.c。
int valid_enable(string usage)
{
    return usage == "magic";
}

// conjure_magic(me, spl, [target])
//   玩家：cmds/std/conjure.c 傳 (me, 咒名(空白已換底線), 以 present 解出的物品或 0)。
// 咒名解析：gold_seal / gold seal -> 黃金﹔silver_seal / silver seal -> 碎銀。
// 失敗回 0(並 notify_fail 給玩家路徑)﹐成功回 1。
varargs int
conjure_magic(object me, string spl, object target)
{
    if( !objectp(me) || !stringp(spl) ) return 0;

    // 須已習得黃白之術(鏡 taoism-cloud 的習得檢定)。
    if( me->query_skill("alchemy-wealth", 1) <= 0
    &&  !me->query_learn("alchemy-wealth") ) {
        notify_fail("你並未習得「黃白之術」。\n");
        return 0;
    }

    // 解析金印 / 銀印(conjure.c 已把空白換成底線﹐兩式皆容)。
    switch( spl ) {
        case "gold_seal":
        case "gold seal":
            return aw_transmute(me, target, AW_GOLD_OB, AW_GOLD_FACE, "黃金");
        case "silver_seal":
        case "silver seal":
            return aw_transmute(me, target, AW_SILVER_OB, AW_SILVER_FACE, "白銀");
    }

    notify_fail("黃白之術只有金印(gold seal)、銀印(silver seal)兩道印訣。\n");
    return 0;
}

// aw_transmute -- 點石成金本體：把 target 物品化作 money_ob 幣別等值之錢。
//   money_ob：化成的貨幣藍本(AW_GOLD_OB / AW_SILVER_OB)。
//   face    ：該幣每枚面值(文)﹐用以折算 set_amount 枚數。
//   metal   ：中文幣名(訊息用)。
// gate/消耗/效果一律對齊 docs L89：
//   - 須指定物品﹐且不得為「錢」(money_id)、不得為 living。
//   - 物品須有正價值(value>0)﹐且不得標 no_sell(不可變賣之物亦不可化錢)。
//   - 物品價 >= 500 文者﹐須 技能等級 > 物品價/10000﹐否則火候不足點不動。
//   - 通過後消 15 神﹐new 對應錢 set_amount(value 折枚﹐不足一枚進一)﹐destruct 原物。
// 成功回 1﹔任何不足回 0(均經 notify_fail 說明﹐且未扣神)。
int aw_transmute(object me, object target, string money_ob, int face, string metal)
{
    int value, amount;
    object here, coin;

    // 須指定要點化的物品(conjure <咒> on <物品>)。
    if( !objectp(target) )
        return notify_fail("你要對什麼物品施展黃白之術﹖(conjure "
            + (money_ob == AW_GOLD_OB ? "gold" : "silver")
            + " seal on <物品>)\n");

    // 非施法之地不可行法(鏡 conjure.c 的 no_magic 守則﹐conjure.c 已先擋一道﹐
    // 此處再護﹐免 NPC / 旁路觸發繞過)。
    here = environment(me);
    if( !objectp(here) ) {
        notify_fail("你身處虛無之地﹐無從施展黃白之術。\n");
        return 0;
    }
    if( here->query("no_magic") ) {
        notify_fail("這裡不准施展法術﹐黃白之術亦運使不得。\n");
        return 0;
    }

    // 不可點化「錢」本身﹐亦不可點化活物(living)。
    if( target->query("money_id") )
        return notify_fail("這已是現成的錢﹐何須再點﹖\n");
    if( living(target) )
        return notify_fail("黃白之術點的是死物﹐豈能拿活生生的"
            + target->name() + "來化錢﹖\n");

    // 物品須在你身上(化的是「身上物品」﹐docs L89)。
    if( environment(target) != me )
        return notify_fail("你得先把" + target->name() + "拿在身上﹐才好施展黃白之術。\n");

    // 估值(query 自動解出物件的 value 閉包﹐回傳「文」)。一文不值者不化。
    value = target->query("value");
    if( value <= 0 )
        return notify_fail(target->name() + "本就一文不值﹐黃白之術也化不出錢來。\n");

    // 不可變賣之物(no_sell)亦不可化錢(鏡 hockshop.c::do_pawn 的 no_sell 守則)。
    if( target->query("no_sell") )
        return notify_fail(target->name() + "靈性已附﹐黃白之術點它不動。\n");

    // 高價物門檻：價值 >= 500 文者﹐須 技能等級 > 物品價/10000。
    if( value >= AW_GATE_VALUE
    &&  me->query_skill("alchemy-wealth") <= value / AW_GATE_DIV )
        return notify_fail(sprintf(
            "%s物性深重(價值%d文)﹐你黃白之術火候未到(需技能等級高於 %d)﹐"
            "鎮它不住﹐點化不得。\n",
            target->name(), value, value / AW_GATE_DIV));

    // 神(sen)消耗檢查：須足 15 神。
    if( me->query_stat("sen") < AW_SEN_COST )
        return notify_fail(sprintf(
            "你神識不足(需 %d 神)﹐運不起黃白之術。\n", AW_SEN_COST));

    // 折算枚數：value(文) / face(每枚面值)﹐不足一枚者進一﹐至少一枚。
    amount = value / face;
    if( value % face ) amount += 1;
    if( amount < 1 ) amount = 1;

    // ── 通過所有檢查﹐正式行法(之後不再失敗)──
    me->consume_stat("sen", AW_SEN_COST);

    // 生錢：new 對應幣別藍本﹐set_amount 折枚﹐move 給玩家﹔滿載則落地於環境
    //(鏡 hockshop.c::pay_player 的給錢殼)。
    coin = new(money_ob);
    if( !objectp(coin) ) {
        // 生錢失敗(藍本載入異常)：把扣去的神補回﹐免玩家平白損神。
        me->supplement_stat("sen", AW_SEN_COST);
        return notify_fail("你心神一散﹐金光潰而不成﹐這錢化不出來。\n");
    }
    coin->set_amount(amount);

    message_vision(HIY
        "$N捏訣於" + target->name() + "上輕輕一點﹐一道金光裹住此物﹐"
        "霎時化作一團爛漫" + metal + "﹗\n" NOR, me);
    tell_object(me, sprintf(HIW
        "你施展黃白之術﹐將%s點化成%s。(消神 %d)\n" NOR,
        target->name(), coin->name(), AW_SEN_COST));

    // 化去原物(死物﹐非 living﹐合 runtime 鐵則 #10)﹐再把錢交到手上。
    destruct(target);
    if( !coin->move(me) )
        coin->move(environment(me));

    // 練技(僅玩家﹔NPC 技能固定)。
    if( userp(me) )
        me->improve_skill("alchemy-wealth", 1 + random(2));

    return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
