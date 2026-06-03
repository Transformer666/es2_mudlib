// enchant.c -- 劍甲門「強化」武器服務（強化之術 enchance）
//
// 玩家手持武器、站在劍甲門傳人面前、且已習得強化之術時，可用 enchant
// （或中文 強化）替手中兵器開鋒淬煉。每強化一級，依序把兵器的傷害上界、
// 力量修正、乘數等級往該武器種類的上限推進，到三項皆滿為止。
//
// 兩種祭煉（見 docs/02-遊戲系統與機制/05-裝備與強化.md）：
//   * golden  黃金祭煉：每次耗 2.5 兩黃金（= 25000 文）。只升不毀，無風險。
//   * silver  神力祭煉：耗「神」(sen) 改品質，較廉；但兵器若非獨一無二
//             (unique / no_drop)，失敗時有機會毀器。
//   無參數時 = golden（向後相容；原指令即黃金行為）。
//
// 設計與來源：docs 05「強化上限表」、docs 06 強化之術習得條件。
// 上限三欄對應 identify.c 所顯示的三項數值：
//   傷害力     = dp->roll + dp->multipler        ～ dp->roll + dp->multipler*dp->range
//   力量修正   = dp->bonus  (%)
//   乘數等級   = dp->multipler
// 故 cap 表三欄 ({傷害上界, 力修上界, 乘數上界}) 分別夾住
//   roll+multipler*range、bonus、multipler。
//
// 武器傷害資料模型（已讀 feature/equip.c + include/combat.h 確認）：
//   武器以 set("damage/"+skill, dp) 存一個 class damage_parameter，
//   欄位 multipler/range/bonus/roll。每個 clone 在 create() 內各自
//   new() 一份（dbase 為每物件獨立，見 feature/dbase.c），故直接改
//   clone 上的 dp 是「逐把武器」生效，不會污染樣板或其他 clone。
//   inflict_damage() 每次攻擊讀 dp 算傷害（equip.c），改 dp 任一欄
//   會立即反映在傷害與 identify 顯示上。

#include <ansi.h>
#include <combat.h>

inherit F_CLEAN_UP;

private void create() { seteuid(getuid()); }

// 各武器種類的強化上限。key = damage/<skill> 的 skill 名
//（武器物件 init_damage 設定的名稱，與 query_temp("weapon") 的鍵一致）。
// 值為三元組 ({ 傷害上界, 力修上界(%), 乘數上界 })，數值取自 docs 05
//「強化上限表」。傷害上界即 identify 顯示的傷害力上界 roll+multipler*range。
private mapping enchant_cap = ([
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

// 黃金祭煉：每次固定 2.5 兩黃金。1 兩黃金 = 10000 文，故 25000 文。
#define GOLDEN_COST     25000

// 神力祭煉：耗「神」(sen) 與少量銀錢。較廉，但非獨一兵器有毀器風險。
#define SILVER_SEN      30      // 每次祭煉耗神
#define BASE_SILVER     3       // 神力祭煉基礎銀兩
#define STEP_SILVER     2       // 每強化一級遞增的銀兩
#define SILVER_FAIL_PCT 20      // 神力祭煉失敗（毀器）機率（%）

// 找出此房間裡的劍甲門傳人（NPC 以 set("enchant_master", 1) 標記）。
private object find_master(object me)
{
    object ob;

    foreach(ob in all_inventory(environment(me)))
        if( ob != me && living(ob) && ob->query("enchant_master") )
            return ob;
    return 0;
}

// 從玩家身上找出正在手持的武器（query_temp("weapon") 是 skill->ob 映射）。
// 回傳 ({ weapon_object, skill })，找不到回傳 0。
private mixed find_wielded(object me)
{
    mapping weapon;
    string skill;
    object ob;

    if( !mapp(weapon = me->query_temp("weapon")) || !sizeof(weapon) )
        return 0;

    // 取第一把（一般玩家同時間單一主手武器即可）。
    foreach(skill, ob in weapon)
        if( objectp(ob) ) return ({ ob, skill });
    return 0;
}

// 是否習得強化之術。gate 於「會這門手藝」即可（法術60+lv10+精熟50000 是
// 陳學亮『傳授』時的條件，由教學端把關；此處只看玩家是否已學）。
// 兼容劍甲門門人（family/family_name 目前未填即回 0，不會誤放他人）。
private int can_enchant(object me)
{
    return me->query_skill("enchance") > 0
        || me->query("family/family_name") == "劍甲門";
}

int main(object me, string arg)
{
    object master, weapon;
    string skill, mode;
    class damage_parameter dp;
    mixed wielded, cap;
    int dmg_cap, bonus_cap, mult_cap;
    int cur_top, max_range, level, price, advanced;
    int new_range, new_bonus, new_mult;

    if( me->is_busy() ) return notify_fail("你現在沒有空﹗\n");

    master = find_master(me);
    if( !master )
        return notify_fail("這裡沒有能替你強化兵刃的師傅。\n");

    if( master->is_fighting() )
        return notify_fail(master->name() + "正忙著﹐沒空理你。\n");

    // 技能門檻：須習得強化之術（或為劍甲門門人）。
    if( !can_enchant(me) )
        return notify_fail(master->name()
            + "搖頭道﹕你未習得強化之術﹐老朽幫不上忙。\n");

    // 祭煉方式：golden（黃金，預設、不毀）或 silver（神力，較廉、可能毀器）。
    mode = arg ? lower_case(arg) : "golden";
    if( mode != "golden" && mode != "silver" )
        return notify_fail("祭煉之法只有 golden（黃金）與 silver（神力）兩種。\n");

    wielded = find_wielded(me);
    if( !wielded )
        return notify_fail("你得先手持一把想要強化的兵器。\n");
    weapon = wielded[0];
    skill  = wielded[1];

    if( !classp(dp = weapon->query("damage/" + skill)) )
        return notify_fail("這把兵器似乎無法強化。\n");

    if( !arrayp(cap = enchant_cap[skill]) )
        return notify_fail(master->name() + "端詳半晌﹐搖頭道﹕這種兵刃我可強化不來。\n");
    dmg_cap   = cap[0];
    bonus_cap = cap[1];
    mult_cap  = cap[2];

    // 推進方案（每級只進一步，依序逼近三項上限）：
    //   1. 傷害上界 roll+multipler*range 未滿 -> range +1（夾住不超過 dmg_cap）。
    //   2. 傷害已逼近上限、力修未滿 -> bonus +N（夾住不超過 bonus_cap）。
    //   3. 力修已滿、乘數未滿 -> multipler +1；乘數一升傷害上界亦升，
    //      故同時夾住 roll+multipler*range <= dmg_cap（必要時連帶調降 range）。
    //   三項皆滿 -> 已臻化境，拒絕不收費。
    //
    // 重要（by-reference 陷阱）：dp(class damage_parameter) 在本 driver 是傳參考﹐
    // 直接寫 dp->range 等欄位會即時改到兵器所存的同一份 dp。故此處只把「強化後的
    // 新值」算進 new_range/new_bonus/new_mult 三個區域變數﹐等到付款(黃金)或耗神
    // (神力)成功後才真正寫回 dp(見下方兩處)。否則付不起錢/神不足而中途 return 的
    // 失敗祭煉﹐也會把兵器白白練上去——等於免費強化(spam 失敗即可練滿)的破綻。
    cur_top   = dp->roll + dp->multipler * dp->range;
    new_range = dp->range;
    new_bonus = dp->bonus;
    new_mult  = dp->multipler;
    advanced  = 0;

    // 步驟 1：傷害上界 +1 級（range +1），夾住不超過 dmg_cap。
    if( cur_top < dmg_cap && dp->multipler > 0 ) {
        max_range = (dmg_cap - dp->roll) / dp->multipler;   // 不超過 cap 的最大 range
        if( new_range + 1 <= max_range ) {
            new_range = new_range + 1;
            advanced = 1;
        } else if( new_range < max_range ) {
            new_range = max_range;
            advanced = 1;
        }
    }

    // 步驟 2：傷害已到頂，改提升力量修正。
    if( !advanced && dp->bonus < bonus_cap ) {
        int step = bonus_cap / 10;                          // 每級約進上限的一成
        if( step < 5 ) step = 5;
        new_bonus = dp->bonus + step;
        if( new_bonus > bonus_cap ) new_bonus = bonus_cap;
        advanced = 1;
    }

    // 步驟 3：傷害與力修皆到頂，改提升乘數等級（連帶夾住傷害上界）。
    if( !advanced && dp->multipler < mult_cap ) {
        new_mult = dp->multipler + 1;
        // 乘數升高使傷害上界 roll+multipler*range 跟著漲，夾回 dmg_cap 之內。
        if( new_mult > 0 ) {
            max_range = (dmg_cap - dp->roll) / new_mult;
            if( max_range < 1 ) max_range = 1;
            if( new_range > max_range ) new_range = max_range;
        }
        advanced = 1;
    }

    if( !advanced ) {
        message_vision("$N拿起$n手中的兵器細看﹐讚道﹕此器已臻化境﹐"
            "再強也是徒勞了。\n", master, me);
        return 1;
    }

    level = weapon->query("enchant");
    if( !intp(level) ) level = 0;

    if( mode == "golden" ) {
        // 黃金祭煉：固定 2.5 兩黃金（25000 文），只升不毀。
        price = GOLDEN_COST;
        switch( me->can_afford(price) ) {
        case 0:
            return notify_fail("黃金祭煉一次需要二兩半黃金﹐你身上的黃金不夠。\n");
        case 2:
            return notify_fail("你沒有足夠的零錢﹐師傅也找不開。\n");
        }
        me->pay_money(price);

        // 付款成功後才寫回新值（dp 為傳參考，提前寫會造成免費強化破綻）。
        dp->range     = new_range;
        dp->bonus     = new_bonus;
        dp->multipler = new_mult;
        weapon->set("damage/" + skill, dp);
        weapon->set("enchant", level + 1);

        message_vision("$N接過$n手中的" + weapon->name() + NOR + "﹐",
            master, me);
        message_vision("$N以黃金為引祭入爐火﹐取出後在鐵砧上叮叮噹噹一陣猛打﹐"
            "復又淬火開鋒﹐遞還給$n。\n", master, me);
        message_vision("$n手中的" + weapon->name() + NOR + "似乎較先前更為鋒利了﹗\n",
            me, master);
        return 1;
    }

    // 神力祭煉：耗「神」(sen) 與少量銀錢；較廉，但非獨一兵器有毀器風險。
    if( me->query_stat("sen") < SILVER_SEN )
        return notify_fail("你的精神不足以引動神力祭煉。\n");

    price = (BASE_SILVER + STEP_SILVER * level) * 100;       // 兩 -> 文（1 兩銀 = 100 文）
    switch( me->can_afford(price) ) {
    case 0:
        return notify_fail(sprintf("神力祭煉這把兵器需要 %d 兩銀子﹐你身上的錢不夠。\n",
            price / 100));
    case 2:
        return notify_fail("你沒有足夠的零錢﹐師傅也找不開。\n");
    }
    me->consume_stat("sen", SILVER_SEN);
    me->pay_money(price);

    message_vision("$N接過$n手中的" + weapon->name() + NOR + "﹐"
        "凝神運起神力灌注其中。\n", master, me);

    // 失敗判定：唯有「非獨一無二」(unique / no_drop) 的兵器才可能在祭煉中毀去。
    if( !weapon->query("unique") && !weapon->query("no_drop")
    &&  random(100) < SILVER_FAIL_PCT )
    {
        string wname = weapon->name();      // 先存名字，毀器後物件即不可讀。

        message_vision(HIR "$N手中的" + wname + HIR
            "受神力反噬﹐「噹」地一聲應聲碎裂﹐化作齏粉散落滿地﹗\n" NOR, master);
        destruct(weapon);
        return 1;
    }

    // 祭煉成功（未毀器）：付神付錢都過了才寫回新值（dp 為傳參考）。
    dp->range     = new_range;
    dp->bonus     = new_bonus;
    dp->multipler = new_mult;
    weapon->set("damage/" + skill, dp);
    weapon->set("enchant", level + 1);

    message_vision("神力流轉﹐$N將兵刃淬鍊一新﹐遞還給$n。\n", master, me);
    message_vision("$n手中的" + weapon->name() + NOR + "似乎較先前更為鋒利了﹗\n",
        me, master);
    return 1;
}

int help(object me)
{
    write(@HELP
指令格式﹕enchant            （中文﹕強化）
          enchant golden     （黃金祭煉﹐預設）
          enchant silver     （神力祭煉）

當你習得劍甲門的強化之術﹐站在劍甲門傳人面前、手持一把兵器時﹐可用此
指令請師傅替你的兵刃開鋒強化。每強化一級﹐兵器會依序在傷害、力量修正、
乘數等級三項上往該種兵器的上限推進﹐三項皆滿之後便無法再強。

兩種祭煉之法﹕
  golden（黃金祭煉）─ 每次耗二兩半黃金﹐只升不毀﹐儘可放心﹔不帶參數時即此法。
  silver（神力祭煉）─ 耗損精神與少許銀兩﹐較為省錢﹔但兵器若非獨一無二之物﹐
                      祭煉失手時有可能當場毀去﹐慎用。

強化前後可用 wield 手持兵器、再用 identify <兵器> 檢視傷害力、力量修正、
乘數等級的變化。
HELP
    );
    return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
