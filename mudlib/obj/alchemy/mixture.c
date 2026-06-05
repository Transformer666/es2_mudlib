// mixture.c -- 配方（丹方藥料）：投入青銅丹鼎、結成丹藥的「半成品藥料」。
//
// 來源：docs/02-遊戲系統與機制/06-煉丹與書本系統.md
//   L60「去濟生藥鋪找藥鋪掌櫃 buy mixture for minor heal pill（92兩50文/份）」、
//   L62「put mixture in reactor（一個 reactor 最多塞 5 份）」、
//   L65「prepare mixture（結丹）」、L79-80「混錯會變不知名配方﹐火候失控 -> 燒焦」。
//
// 機制：mixture 是「對應某丹種的藥料」。玩家向藥鋪 buy mixture for <丹種> 時﹐
//   藥鋪 clone 本物件並 set_pill(<丹藥檔>) 指定它對應哪一爐丹。投入丹鼎、爐火
//   達標後 prepare 即結成該丹。本檔只管「我對應哪一丹、火候門檻多少」﹐實際結丹
//   流程由 obj/alchemy/reactor.c::do_prepare 主導。
//
// 「不知名配方」：reactor 內混入兩種以上「對應丹種不同」的 mixture﹐即標記不知名
//   旗標﹐火候門檻錯亂 -> 過熱燒焦（docs L79-80）。set_pill / query_pill 供 reactor
//   逐份比對。
//
// 火候門檻來源：直接讀對應丹藥（obj/medication/alchemist/*.c）既有的
//   query("produce_param")（min_heat/max_heat/min_heat_power/max_heat_power﹐
//   小還丹為 800-820 kJ / 130-150 kW﹐見 minor_heal_pill.c）。本檔不另造數值﹐
//   一律向成品丹藥藍本問﹐確保與 docs L75、refine.c 一致、單一真相源。
//
// runtime 鐵則：mixture 為死物﹐不涉 living die/destruct(#10)﹔非 NPC﹐不
//   include <weapon.h>(#12)。前置宣告自訂查詢函式(#12)。

inherit COMBINED_ITEM;

// 前置宣告(lesson #12：定義前引用之函式一律先宣告)。
string query_pill();
mapping query_produce_param();

void create()
{
    set_name("丹方藥料", ({ "mixture", "配方", "丹方" }));
    if( !clonep() ) {
        set("unit", "份");
        set("long",
            "一份依丹方配齊、研磨調勻的藥料﹐尚未經爐火煉化。\n"
            "投入丹鼎、以丹爐文武火候煉足﹐方能結成丹藥。\n");
        set("base_unit", "份");
        set("base_value", 9250);    // docs L60/L72：小還丹方 9250 文/份(預設)。
        set("base_weight", 100);
        // query("mixture"):供丹鼎辨識「這是配方藥料」用。
        set("mixture", 1);
        // 預設對應小還丹(docs 通篇示範丹)﹔藥鋪售出時可 set_pill 覆寫。
        set("pill", "/obj/medication/alchemist/minor_heal_pill");
    }
    set_amount(1);
    setup();
}

// set_pill -- 指定本份配方對應的成品丹藥藍本路徑。
//   藥鋪 buy mixture for <丹種> 時呼叫﹐如 set_pill("/obj/medication/alchemist/
//   minor_heal_pill")。同時依該丹的 base_value / mixture_value 微調本配方價值
//   （若丹藍本有 mixture_value 則採之﹐否則保留預設）。
void set_pill(string pill_path)
{
    mixed err;
    object blueprint;
    int mv;

    if( !stringp(pill_path) ) return;
    set("pill", pill_path);

    // 試載成品藍本﹐同步配方價值與顯示名(載不起則靜默保留預設﹐不中斷)。
    err = catch(blueprint = load_object(pill_path));
    if( err || !objectp(blueprint) ) return;

    mv = (int)blueprint->query("mixture_value");
    if( mv > 0 ) set("base_value", mv * 37);    // mixture_value 250 -> 約 9250 文。

    set("long",
        "一份照「" + (blueprint->query("name") || "丹方") + "」配齊調勻的藥料﹐\n"
        "尚未經爐火煉化。投入丹鼎、以丹爐文武火候煉足﹐方能結成此丹。\n");
}

// query_pill -- 本配方對應的成品丹藥藍本路徑（reactor 比對 / 結丹用）。
string query_pill()
{
    return query("pill");
}

// query_produce_param -- 向對應成品丹藥問其火候參數(min/max heat & power)。
//   reactor 判定火候是否達標時呼叫。載不起則回 0﹐由呼叫端優雅處理。
mapping query_produce_param()
{
    mixed err;
    object blueprint;
    string pill;

    pill = query("pill");
    if( !stringp(pill) ) return 0;

    err = catch(blueprint = load_object(pill));
    if( err || !objectp(blueprint) ) return 0;

    return blueprint->query("produce_param");
}

// vim: set ts=4 sw=4 syntax=lpc
