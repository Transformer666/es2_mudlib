// enchant.c -- 劍甲門「強化」武器服務
//
// 玩家手持武器、站在劍甲門傳人面前時，可用 enchant（或中文 強化）把
// 手中武器的「傷害上限」往上提升一級，每級花費銀兩，到該武器種類的
// 上限為止。比照黃金祭煉（golden_bless）：v1 只升不毀，無損毀風險。
//
// 設計與來源：memory/specs/combat-formulas.md「武器強化上限」表。
// 各武器種類的傷害上限對應 identify.c 顯示的「傷害力」上界，
// 即 dp->roll + dp->multipler * dp->range。本指令以 +1 dp->range
// 為一級，逼近但不超過該種類上限。乘數（dp->multipler）不動，
// 留在原 setup_*() 範圍內。
//
// 武器傷害資料模型（已讀 feature/equip.c + include/combat.h 確認）：
//   武器以 set("damage/"+skill, dp) 存一個 class damage_parameter，
//   欄位 multipler/range/bonus/roll。每個 clone 在 create() 內各自
//   new() 一份（dbase 為每物件獨立，見 feature/dbase.c），故直接改
//   clone 上的 dp 是「逐把武器」生效，不會污染樣板或其他 clone。
//   inflict_damage() 每次攻擊讀 dp 算傷害（equip.c:255），改 range
//   會立即反映在傷害與 identify 顯示上。

#include <ansi.h>
#include <combat.h>

inherit F_CLEAN_UP;

private void create() { seteuid(getuid()); }

// 各武器種類的傷害上限（identify 顯示的傷害力上界）與一次強化的銀兩花費。
// key = damage/<skill> 的 skill 名（武器物件 init_damage 設定的名稱）。
// 數值取自 combat-formulas.md「武器強化上限」表的「傷害」上界欄。
private mapping damage_cap = ([
    "axe"               : 135,
    "secondhand axe"    : 135,
    "twohanded axe"     : 260,
    "blade"             : 110,
    "secondhand blade"  : 110,
    "twohanded blade"   : 210,
    "blunt"             : 100,
    "secondhand blunt"  : 100,
    "twohanded blunt"   : 190,
    "dagger"            : 75,
    "secondhand dagger" : 75,
    "needle"            : 75,
    "secondhand needle" : 75,
    "sword"             : 110,
    "secondhand sword"  : 110,
    "twohanded sword"   : 210,
    "pike"              : 176,
    "secondhand pike"   : 176,
    "twohanded pike"    : 176,
    "staff"             : 158,
    "secondhand staff"  : 158,
    "twohanded staff"   : 158,
    "whip"              : 110,
]);

// 一次強化花費的銀兩（兩）。價錢隨已強化次數遞增，避免無腦堆滿。
#define BASE_SILVER     5
#define STEP_SILVER     3

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

int main(object me, string arg)
{
    object master, weapon;
    string skill;
    class damage_parameter dp;
    mixed wielded;
    int cap, cur_top, max_range, new_range, level, price;

    if( me->is_busy() ) return notify_fail("你現在沒有空﹗\n");

    master = find_master(me);
    if( !master )
        return notify_fail("這裡沒有能替你強化兵刃的師傅。\n");

    if( master->is_fighting() )
        return notify_fail(master->name() + "正忙著﹐沒空理你。\n");

    wielded = find_wielded(me);
    if( !wielded )
        return notify_fail("你得先手持一把想要強化的兵器。\n");
    weapon = wielded[0];
    skill  = wielded[1];

    if( !classp(dp = weapon->query("damage/" + skill)) )
        return notify_fail("這把兵器似乎無法強化。\n");

    if( undefinedp(cap = damage_cap[skill]) )
        return notify_fail(master->name() + "端詳半晌﹐搖頭道﹕這種兵刃我可強化不來。\n");

    // 目前的傷害上界 = identify 顯示的傷害力上界 = roll + multipler*range。
    // 一級 = range +1，但夾住使上界不超過 cap。先算出強化後的 range，
    // 若無法再升（已達/逼近上限）就拒絕、不收錢。
    cur_top = dp->roll + dp->multipler * dp->range;
    max_range = (cap - dp->roll) / dp->multipler;       // 不超過 cap 的最大 range
    new_range = dp->range + 1;
    if( new_range > max_range ) new_range = max_range;
    if( new_range <= dp->range || cur_top >= cap ) {
        message_vision("$N拿起$n手中的兵器細看﹐讚道﹕此器已臻化境﹐"
            "再強也是徒勞了。\n", master, me);
        return 1;
    }

    // 計價：依已強化次數遞增。
    level = weapon->query("enchant");
    if( !intp(level) ) level = 0;
    price = (BASE_SILVER + STEP_SILVER * level) * 100;   // 兩 -> 文（1 兩銀 = 100 文）

    switch( me->can_afford(price) ) {
    case 0:
        return notify_fail(sprintf("強化這把兵器需要 %d 兩銀子﹐你身上的錢不夠。\n",
            price / 100));
    case 2:
        return notify_fail("你沒有足夠的零錢﹐師傅也找不開。\n");
    }
    me->pay_money(price);

    // 強化：每個 clone 各自一份 dp（已於 feature/equip.c init_damage 每次 new() +
    // feature/dbase.c 每物件獨立 dbase 確認），直接改寫是「逐把武器」生效。
    dp->range = new_range;
    weapon->set("damage/" + skill, dp);
    weapon->set("enchant", level + 1);

    message_vision("$N接過$n手中的" + weapon->name() + NOR + "﹐",
        master, me);
    message_vision("$N將兵器架上爐火中燒得通紅﹐取出後在鐵砧上叮叮噹噹一陣猛打﹐"
        "復又淬火開鋒﹐遞還給$n。\n", master, me);
    message_vision("$n手中的" + weapon->name() + NOR + "似乎較先前更為鋒利了﹗\n",
        me, master);

    return 1;
}

int help(object me)
{
    write(@HELP
指令格式﹕enchant     （中文﹕強化）

當你站在劍甲門傳人面前﹐手持一把兵器時﹐可用此指令請師傅替你的兵刃
開鋒強化。每強化一級﹐兵器的傷害上限便會提高一些﹐並收取若干銀兩﹔
強化次數越多﹐收費越貴。各種兵器都有其強化上限﹐到頂之後便無法再強。

強化前後可用 wield 手持兵器、再用 identify <兵器> 檢視傷害力數值的變化。
此服務只升不毀﹐儘可放心。
HELP
    );
    return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
