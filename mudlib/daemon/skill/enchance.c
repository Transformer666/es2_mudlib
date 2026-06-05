// 強化之術 enchance -- 劍甲門(兩派方士共通進階)的武器強化法術
//
// 來源(docs/03-門派與武功/07-方士-龍圖武陀.md §劍甲門 L78~L86)：
//   強化之術由陳學亮 @ 風城傳授(習得條件﹕法術 60 + lv 10 + 兵刃精熟 50000﹐
//   由教學端把關﹐此處只看玩家是否已習得)。兩式祭煉﹕
//     golden_bless：每次消 2.5 兩黃金改武器品質﹐不消神 / 不得 exp / 不損毀。
//     silver_bless：消神(sen)改品質﹐非獨一無二之物有機會損毀。
//
// === 派發路徑(本檔走 magic 槽 + conjure 指令) ===
// 強化之術是一門「法術」(docs L93 習得條件即 法術 60)﹐故掛在 magic 槽﹐由
// conjure 指令(cmds/std/conjure.c)派發﹐而非攻擊咒的 spells 槽(cast)﹕
//   玩家 `enable magic with enchance` 後﹐`conjure golden_bless`(或 silver_bless)。
//   conjure.c 取 me->skill_mapped("magic")﹐呼 SKILL_D(magic)->conjure_magic(me,
//   spl, target)——本檔實作之。此乃天師駕雲 daemon/skill/taoism-cloud.c(同走
//   magic 槽 + conjure + override conjure_magic/valid_enable)的同型結構﹐照其範式建立。
//   (注意﹕conjure.c 會把 spl 中的空白換成底線﹐故口訣以底線命名 golden_bless。)
//
// === 武器品質機制(沿用已驗範式) ===
// 武器以 set("damage/"+skill, dp) 存一個 class damage_parameter(欄位 multipler/
// range/bonus/roll﹐見 include/combat.h 與 feature/equip.c::init_damage)。每把
// clone 各自 new() 一份 dp(dbase 每物件獨立)﹐故直接改 clone 的 dp 是「逐把武器」
// 生效﹐不污染樣板/他 clone﹔inflict_damage() 每次攻擊讀 dp 算傷害(equip.c L238~)﹐
// 改 dp 任一欄即時反映於傷害與 identify 顯示。
//
// 強化的上限表與「每級依序推進 range -> bonus -> multipler」之進階法﹐與既有
// cmds/std/enchant.c(劍甲門傳人 NPC 服務式強化)完全一致(同一 docs 05 強化上限表)﹐
// 本檔把同一機制接到「玩家自行 conjure 施法」的派發路徑上。
//
// === by-reference 陷阱(鏡 enchant.c 之防範) ===
// dp(class damage_parameter)在本 driver 傳參考﹐直接寫 dp->range 等欄位會即時改到
// 兵器所存的同一份 dp。故只把「強化後新值」算進 new_range/new_bonus/new_mult 三個
// 區域變數﹐等到付款(黃金)/耗神(神力)成功後才真正寫回 dp。否則付不起錢/神不足而
// 中途 return 的失敗祭煉也會把兵器白白練上去(免費強化破綻)。
//
// runtime 鐵則：本式不涉 ::die()/destruct() 玩家﹐destruct 僅施於毀器之兵器
// (silver_bless 失敗﹐鏡 enchant.c)﹔不 replace_program﹔inherit /std/magic(magic
// daemon 基底)。lesson #12：所有自訂函式一律檔頭前置宣告﹐免「定義前引用」。

#include <ansi.h>
#include <combat.h>

inherit "/std/magic";

// === 黃金祭煉(golden_bless)：每次固定 2.5 兩黃金。1 兩黃金 = 10000 文(見
// obj/money/gold.c base_value 10000)﹐故 25000 文。只升不毀﹐無風險﹐不耗神。
#define GOLDEN_COST     25000

// === 神力祭煉(silver_bless)：耗「神」(sen)與少量銀錢﹐較廉﹔非獨一兵器有毀器風險。
#define SILVER_SEN      30      // 每次祭煉耗神
#define BASE_SILVER     3       // 神力祭煉基礎銀兩
#define STEP_SILVER     2       // 每強化一級遞增的銀兩
#define SILVER_FAIL_PCT 20      // 神力祭煉失敗(毀器)機率(%)

// === 前置宣告(lesson #12：自訂函式一律先前置宣告﹐免「定義前引用」編譯失敗) ===
int valid_enable(string usage);
varargs int conjure_magic(object me, string spl, object target);
mapping query_enchant_cap();
int can_enchance(object me);
mixed find_wielded(object me);
private mixed plan_advance(string skill, class damage_parameter dp);
int golden_bless(object me, object weapon, string skill, class damage_parameter dp);
int silver_bless(object me, object weapon, string skill, class damage_parameter dp);

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("enchance");
    // 登錄中文名﹐使 enable / skills 等顯示「強化之術」而非英文代號 enchance。
    CHINESE_D->add_translate("enchance", "強化之術");
    setup();
}

// 本技能掛在 magic 槽(強化施法)﹐而非 spells 槽(攻擊咒)。
// 覆寫 /std/magic.c 的 valid_enable(原本只認 "spells")﹐鏡 taoism-cloud.c。
int valid_enable(string usage)
{
    return usage == "magic";
}

// 各武器種類的強化上限。key = damage/<skill> 的 skill 名(與 query_temp("weapon")
// 之鍵一致)。值為三元組 ({ 傷害上界, 力修上界(%), 乘數上界 })﹐取自 docs 05
//「強化上限表」﹐與 cmds/std/enchant.c 同表(同一來源)。
mapping query_enchant_cap()
{
    return ([
        //                       傷害   力修  乘數
        "axe"               : ({ 135,   200,  5 }),
        "secondhand axe"    : ({ 135,   200,  5 }),
        "twohanded axe"     : ({ 260,   300,  5 }),
        "blade"             : ({ 110,   200,  4 }),
        "secondhand blade"  : ({ 110,   200,  4 }),
        "twohanded blade"   : ({ 210,   300,  4 }),
        "blunt"             : ({ 100,   300,  6 }),
        "secondhand blunt"  : ({ 100,   300,  6 }),
        "twohanded blunt"   : ({ 190,   450,  6 }),
        "dagger"            : ({  75,   100,  3 }),
        "secondhand dagger" : ({  75,   100,  3 }),
        "needle"            : ({  75,   100,  3 }),
        "secondhand needle" : ({  75,   100,  3 }),
        "sword"             : ({ 110,   150,  5 }),
        "secondhand sword"  : ({ 110,   150,  5 }),
        "twohanded sword"   : ({ 210,   225,  5 }),
        "pike"              : ({ 176,   150,  6 }),
        "secondhand pike"   : ({ 176,   150,  6 }),
        "twohanded pike"    : ({ 176,   150,  6 }),
        "staff"             : ({ 158,   375,  4 }),
        "secondhand staff"  : ({ 158,   375,  4 }),
        "twohanded staff"   : ({ 158,   375,  4 }),
        "whip"              : ({ 110,   100,  6 }),
    ]);
}

// 是否習得強化之術。gate 於「會這門手藝」即可(法術60+lv10+精熟50000 是陳學亮
//『傳授』時的條件﹐由教學端把關)﹔此處只看玩家是否已學或為劍甲門門人。
// 鏡 cmds/std/enchant.c::can_enchant。
int can_enchance(object me)
{
    return me->query_skill("enchance", 1) > 0
        || me->query("family/family_name") == "劍甲門";
}

// 從玩家身上找出正手持的武器(query_temp("weapon") 是 skill->ob 映射﹐見
// feature/equip.c L199 set_temp("weapon/"+skill, this_object()))。
// 回傳 ({ weapon_object, skill })﹐找不到回 0。鏡 enchant.c::find_wielded。
mixed find_wielded(object me)
{
    mapping weapon;
    string skill;
    object ob;

    if( !mapp(weapon = me->query_temp("weapon")) || !sizeof(weapon) )
        return 0;

    // 取第一把(一般玩家同時間單一主手武器即可)。
    foreach(skill, ob in weapon)
        if( objectp(ob) ) return ({ ob, skill });
    return 0;
}

// conjure_magic(me, spl, [target])
//   玩家：cmds/std/conjure.c 傳 (me, 口訣, 對象或0)。本式對手中兵器施法﹐target 無用。
//   NPC ：std/char/npc.c::conjure_magic 傳 (me, magic)﹐target 省略。
// spl ∈ { golden_bless, silver_bless }(conjure.c 已把空白換底線)。
// 失敗回 0(並 notify_fail 給玩家路徑)﹐成功回 1。
varargs int
conjure_magic(object me, string spl, object target)
{
    object weapon;
    string skill;
    class damage_parameter dp;
    mixed wielded;

    if( !objectp(me) || !stringp(spl) ) return 0;

    // 只認 golden_bless / silver_bless 兩道口訣(亦容中文同義)。
    if( spl != "golden_bless" && spl != "silver_bless"
    &&  spl != "黃金祭煉" && spl != "神力祭煉" )
    {
        notify_fail("強化之術只有 golden_bless(黃金祭煉)與 silver_bless(神力祭煉)"
            "兩道口訣。\n");
        return 0;
    }
    if( spl == "黃金祭煉" ) spl = "golden_bless";
    if( spl == "神力祭煉" ) spl = "silver_bless";

    // 須已習得強化之術(或為劍甲門門人)。
    if( !can_enchance(me) ) {
        notify_fail("你並未習得「強化之術」﹐運使不了這劍甲門的祭煉法。\n");
        return 0;
    }

    // 非施法之地不可施展(鏡 conjure.c 的 no_magic 守則)。
    if( !objectp(environment(me)) ) {
        notify_fail("你身處虛無之地﹐無從施法。\n");
        return 0;
    }
    if( environment(me)->query("no_magic") ) {
        notify_fail("這裡不准施展法術﹐強化之術亦運使不得。\n");
        return 0;
    }
    // 交戰中心神不寧﹐不可分神祭煉兵器。
    if( me->is_fighting() ) {
        notify_fail("你正自纏鬥﹐心神不寧﹐難以分神祭煉兵刃。\n");
        return 0;
    }

    // 須手持一把可強化的兵器。
    wielded = find_wielded(me);
    if( !wielded ) {
        notify_fail("你得先手持一把想要強化的兵器。\n");
        return 0;
    }
    weapon = wielded[0];
    skill  = wielded[1];

    if( !classp(dp = weapon->query("damage/" + skill)) ) {
        notify_fail("這把兵器似乎無法強化。\n");
        return 0;
    }

    if( spl == "golden_bless" )
        return golden_bless(me, weapon, skill, dp);
    return silver_bless(me, weapon, skill, dp);
}

// 依強化上限表算出「下一級」的 new_range/new_bonus/new_mult﹐並判定是否還能再進。
// 每級只進一步(依序逼近三項上限)﹕range(傷害上界) -> bonus(力修) -> multipler(乘數)。
// 回傳 ({ advanced, new_range, new_bonus, new_mult })﹔advanced==0 表已臻化境。
// 與 cmds/std/enchant.c 之推進法完全一致(同一 docs 05 強化上限表)。
private mixed plan_advance(string skill, class damage_parameter dp)
{
    mapping caps;
    mixed cap;
    int dmg_cap, bonus_cap, mult_cap;
    int cur_top, max_range, step;
    int new_range, new_bonus, new_mult, advanced;

    caps = query_enchant_cap();
    if( !arrayp(cap = caps[skill]) ) return 0;     // 此種兵刃不在上限表
    dmg_cap   = cap[0];
    bonus_cap = cap[1];
    mult_cap  = cap[2];

    cur_top   = dp->roll + dp->multipler * dp->range;
    new_range = dp->range;
    new_bonus = dp->bonus;
    new_mult  = dp->multipler;
    advanced  = 0;

    // 步驟 1：傷害上界 +1 級(range +1)﹐夾住不超過 dmg_cap。
    if( cur_top < dmg_cap && dp->multipler > 0 ) {
        max_range = (dmg_cap - dp->roll) / dp->multipler;
        if( new_range + 1 <= max_range ) {
            new_range = new_range + 1;
            advanced = 1;
        } else if( new_range < max_range ) {
            new_range = max_range;
            advanced = 1;
        }
    }

    // 步驟 2：傷害已到頂﹐改提升力量修正。
    if( !advanced && dp->bonus < bonus_cap ) {
        step = bonus_cap / 10;                      // 每級約進上限的一成
        if( step < 5 ) step = 5;
        new_bonus = dp->bonus + step;
        if( new_bonus > bonus_cap ) new_bonus = bonus_cap;
        advanced = 1;
    }

    // 步驟 3：傷害與力修皆到頂﹐改提升乘數等級(連帶夾住傷害上界)。
    if( !advanced && dp->multipler < mult_cap ) {
        new_mult = dp->multipler + 1;
        if( new_mult > 0 ) {
            max_range = (dmg_cap - dp->roll) / new_mult;
            if( max_range < 1 ) max_range = 1;
            if( new_range > max_range ) new_range = max_range;
        }
        advanced = 1;
    }

    return ({ advanced, new_range, new_bonus, new_mult });
}

// golden_bless -- 黃金祭煉：消 2.5 兩黃金改武器品質。不耗神 / 不得 exp / 不損毀。
// 付款成功後才寫回 dp 新值(by-reference 陷阱)。回 1 成功﹐0 失敗(均 notify_fail)。
int golden_bless(object me, object weapon, string skill, class damage_parameter dp)
{
    mixed plan;
    int new_range, new_bonus, new_mult, level;

    plan = plan_advance(skill, dp);
    if( !arrayp(plan) ) {
        notify_fail("你端詳半晌﹐這種兵刃強化之術也施展不上。\n");
        return 0;
    }
    if( !plan[0] ) {
        message_vision("$N凝視手中兵器﹐微微一歎﹕此器已臻化境﹐再強也是徒勞了。\n", me);
        return 1;
    }
    new_range = plan[1];
    new_bonus = plan[2];
    new_mult  = plan[3];

    // 黃金祭煉：固定 2.5 兩黃金(25000 文)﹐只升不毀﹐不耗神。
    switch( me->can_afford(GOLDEN_COST) ) {
    case 0:
        notify_fail("黃金祭煉一次需要二兩半黃金﹐你身上的黃金不夠。\n");
        return 0;
    case 2:
        notify_fail("你沒有足夠的零錢湊出這二兩半黃金。\n");
        return 0;
    }
    me->pay_money(GOLDEN_COST);

    // 付款成功後才寫回新值(dp 傳參考﹐提前寫會造成免費強化破綻)。
    dp->range     = new_range;
    dp->bonus     = new_bonus;
    dp->multipler = new_mult;
    weapon->set("damage/" + skill, dp);
    level = weapon->query("enchant");
    if( !intp(level) ) level = 0;
    weapon->set("enchant", level + 1);

    message_vision(HIY
        "$N取出二兩半黃金為引﹐凝神運起強化之術﹐周身金光流轉灌注於手中"
        + weapon->name() + HIY + "之上。\n" NOR, me);
    message_vision("$N手中的" + weapon->name() + NOR
        + "金光斂去﹐似乎較先前更為鋒利了﹗(消 2.5 兩黃金)\n", me);

    return 1;
}

// silver_bless -- 神力祭煉：消神(sen)改品質﹐較廉﹔非獨一無二之物失敗有機會損毀。
// 耗神/付款成功後才寫回 dp 新值(by-reference 陷阱)。回 1 成功(含毀器)﹐0 失敗。
int silver_bless(object me, object weapon, string skill, class damage_parameter dp)
{
    mixed plan;
    int new_range, new_bonus, new_mult, level, price;
    string wname;

    plan = plan_advance(skill, dp);
    if( !arrayp(plan) ) {
        notify_fail("你端詳半晌﹐這種兵刃強化之術也施展不上。\n");
        return 0;
    }
    if( !plan[0] ) {
        message_vision("$N凝視手中兵器﹐微微一歎﹕此器已臻化境﹐再強也是徒勞了。\n", me);
        return 1;
    }
    new_range = plan[1];
    new_bonus = plan[2];
    new_mult  = plan[3];

    level = weapon->query("enchant");
    if( !intp(level) ) level = 0;

    // 神力祭煉：耗神(sen)與少量銀錢﹐較廉﹔非獨一兵器有毀器風險。
    if( me->query_stat("sen") < SILVER_SEN ) {
        notify_fail("你的精神不足以引動神力祭煉。\n");
        return 0;
    }
    price = (BASE_SILVER + STEP_SILVER * level) * 100;   // 兩 -> 文(1 兩銀 = 100 文)
    switch( me->can_afford(price) ) {
    case 0:
        notify_fail(sprintf("神力祭煉這把兵器需要 %d 兩銀子﹐你身上的錢不夠。\n",
            price / 100));
        return 0;
    case 2:
        notify_fail("你沒有足夠的零錢﹐湊不齊這筆銀兩。\n");
        return 0;
    }
    me->consume_stat("sen", SILVER_SEN);
    me->pay_money(price);

    message_vision(HIC
        "$N凝神運起強化之術﹐將神力灌注於手中" + weapon->name() + HIC + "之中。\n" NOR,
        me);

    // 失敗判定：唯有「非獨一無二」(unique / no_drop)的兵器才可能在祭煉中毀去。
    if( !weapon->query("unique") && !weapon->query("no_drop")
    &&  random(100) < SILVER_FAIL_PCT )
    {
        wname = weapon->name();     // 先存名字﹐毀器後物件即不可讀。
        message_vision(HIR "$N手中的" + wname + HIR
            "受神力反噬﹐「噹」地一聲應聲碎裂﹐化作齏粉散落滿地﹗\n" NOR, me);
        destruct(weapon);
        return 1;
    }

    // 祭煉成功(未毀器)：付神付錢都過了才寫回新值(dp 傳參考)。
    dp->range     = new_range;
    dp->bonus     = new_bonus;
    dp->multipler = new_mult;
    weapon->set("damage/" + skill, dp);
    weapon->set("enchant", level + 1);

    message_vision("神力流轉﹐$N將手中" + weapon->name() + NOR
        + "淬鍊一新﹐似乎較先前更為鋒利了﹗\n", me);

    return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
