// reactor.c -- 青銅丹鼎：盛裝配方藥料、結成丹藥的密封反應器。
//
// 來源：docs/02-遊戲系統與機制/06-煉丹與書本系統.md
//   L31「青銅丹鼎 (Bronze reactor) 250 文」、
//   L56「conjure green seal on reactor（封丹鼎）」、
//   L59「put mixture in reactor（一個 reactor 最多塞 5 份）」、
//   L60「put reactor in furnace（鼎放爐）」、
//   L65「get all from reactor / prepare mixture（結丹）」、
//   L66「conjure green dispel on reactor（解丹鼎）」、
//   L79-80「一個 reactor 只能塞 5 份；混錯 -> 不知名配方、火候失控 -> 燒焦」。
//
// 狀態機（query("sealed")）：
//   未封(sealed=0)：可 put mixture in reactor（最多 5 份）、可 get all from reactor、
//                    可 put reactor in furnace。
//   已封(sealed=1)：由 daemon/skill/alchemy-medication.c::conjure green seal 設定。
//                    密封後內容物鎖死（hold_object 擋 get、accept_object 擋再投料）﹐
//                    爐火得以煉化﹔conjure green dispel 解封(set_sealed(0))後方能取丹。
//
// 不知名配方旗標(query("unknown_mix"))：鼎內混入兩種以上「對應丹種不同」的 mixture
//   即標記﹐火候門檻錯亂﹐爐子煉之必過熱燒焦（docs L79-80）。投料時即時判定。
//
// 結丹(do_prepare)：對齊 docs L65「prepare mixture」。須鼎已解封、火候達標
//   (query("heat_ok")﹐由 furnace 煉足後 set)﹐則內含 N 份 mixture -> N 粒對應丹藥。
//   過熱(query("overheated"))或不知名配方 -> 燒焦(毀內容)。
//
// 容器機制沿用 CONTAINER_ITEM（/std/item/container﹐見 obj/bottle.c）﹕
//   accept_object 控投料、hold_object 控取料。put/get 指令(cmds/std/put.c、get.c)
//   分別呼 dest->accept_object(me,obj)、from->hold_object(obj)。
//
// runtime 鐵則：丹鼎為死物﹐destruct 僅及鼎內死物 mixture(燒焦時)﹐不涉 living
//   die/destruct(#10)﹔非 NPC﹐不 include <weapon.h>(#12)。前置宣告自訂函式(#12)。

#include <ansi.h>

inherit CONTAINER_ITEM;

// === 丹鼎參數(docs L79：一鼎最多 5 份配方) ===
#define REACTOR_MAX_MIX     5       // 一個丹鼎最多容納的 mixture 份數總和。

// 前置宣告(lesson #12)。
int set_sealed(int flag);
int query_sealed();
int count_mixture();
void recheck_unknown_mix();
int receive_object(object ob, int from_inventory);
int do_prepare(string arg);

void create()
{
    set_name("青銅丹鼎", ({ "bronze reactor", "reactor", "丹鼎", "鼎" }));
    set_weight(8000);
    set_max_encumbrance(60000);     // 容得下 5 份配方(每份 base_weight 100)綽綽有餘。
    if( !clonep() ) {
        set("unit", "座");
        set("value", 250);          // docs L31：青銅丹鼎 250 文。
        set("long",
            "一座古樸的青銅丹鼎﹐鼎身斑駁泛著銅綠﹐三足兩耳﹐鼎腹寬深可盛藥料。\n"
            "煉丹時須先以「green seal」封住鼎口聚住藥氣﹐置入丹爐受火煉化﹐\n"
            "火候煉足後解封﹐再 prepare 結成丹藥。\n");
        // query("reactor")：供丹爐辨識「這是丹鼎」用。
        set("reactor", 1);
    }
    // 丹鼎是「盛料的容器」而非「可進入的房間」。CONTAINER_ITEM::setup 會在
    // query("exits") 為空時自動補上 exits/out(使之可 enter / go out)﹐這對丹鼎並
    // 不合理﹐故先擺一個空 exits 佔位﹐令其 setup 不再加 out(do_look 的 go out 提示
    // 亦隨之消失)。容器的 put/get 語意(accept_object/hold_object/receive_object)不受影響。
    set("exits", ([ ]));
    setup();
}

void init()
{
    // prepare：結丹（docs L65）。掛在丹鼎上﹐玩家身邊有鼎即可用。
    // 注意：init() 在玩家進入丹鼎所在環境(房間 / 玩家身上)時觸發﹐故須先
    // get reactor from furnace（火候煉足、熄火後 hold_object 即放行）把鼎取到
    // 房間 / 身上﹐方得 prepare。此正合 docs L65「get all from reactor; prepare」。
    add_action("do_prepare", "prepare");
}

// === 狀態查詢 / 設定 ===

// set_sealed -- 由 daemon/skill/alchemy-medication.c 的 green seal/dispel 呼叫。
//   1 = 封印(鎖內容、可受火)﹐0 = 解封(可取丹)。回傳新狀態。
int set_sealed(int flag)
{
    set("sealed", flag ? 1 : 0);
    // CONTAINER_ITEM::hold_object 看的是 query("closed")﹐封印即等同「閉合」﹐
    // 借其既有機制鎖死取料(get from reactor)。
    set("closed", flag ? 1 : 0);
    return query("sealed");
}

int query_sealed() { return query("sealed") ? 1 : 0; }

// 數鼎內 mixture 的「份數」總和(COMBINED_ITEM 累加 query_amount())。
int count_mixture()
{
    int total = 0;
    object ob;

    foreach(ob in all_inventory(this_object())) {
        if( ob->query("mixture") )
            total += (int)ob->query_amount();
    }
    return total;
}

// 重判「不知名配方」旗標：鼎內若混入兩種以上對應丹種不同的 mixture﹐即標記。
// 每次投料(accept_object 成功後)與取料皆重算﹐保持即時。
void recheck_unknown_mix()
{
    object ob;
    string pill, first = 0;
    int mixed_kinds = 0;

    foreach(ob in all_inventory(this_object())) {
        if( !ob->query("mixture") ) continue;
        pill = ob->query_pill();
        if( !stringp(pill) ) { mixed_kinds = 1; break; }
        if( !first ) first = pill;
        else if( pill != first ) { mixed_kinds = 1; break; }
    }
    set("unknown_mix", mixed_kinds);
}

// === 容器守則 ===

// accept_object -- put X in reactor 時 put.c 呼叫。回 1 准、0 拒。
//   只准投 mixture(配方)﹐且封印後不得再投﹐且總份數不得逾 REACTOR_MAX_MIX。
int accept_object(object player, object ob)
{
    int adding;

    if( !objectp(ob) ) return 0;

    if( query("sealed") ) {
        notify_fail("丹鼎已被封住﹐投不進東西了。先解封(conjure green dispel on reactor)。\n");
        return 0;
    }

    if( !ob->query("mixture") ) {
        notify_fail("丹鼎只盛得下煉丹的配方藥料(mixture)。\n");
        return 0;
    }

    // 投入後總份數不得超過 5（docs L79）。ob 自帶 amount﹐預判加總。
    adding = (int)ob->query_amount();
    if( adding < 1 ) adding = 1;
    if( count_mixture() + adding > REACTOR_MAX_MIX ) {
        notify_fail(sprintf("一座丹鼎最多只盛得下 %d 份配方﹐再多便溢出來了。\n",
            REACTOR_MAX_MIX));
        return 0;
    }

    // 准入。不知名旗標待物件實際移入後由 receive_object 重算（此時 ob 尚未在鼎內）。
    return 1;
}

// receive_object -- 物件移入鼎內前由 feature/move.c::move 回呼(回 0 則拒收)。
//   先讓 base(F_MOVE) 做完重量 / 件數守則﹐再排一次延後的不知名配方重判——
//   move.c 在本函式回 1「之後」才真正 move_object(ob)﹐故須 call_out(...,0) 延到
//   下一輪 ob 已在鼎內方統計得準(不可在此即時 recheck﹐那時 ob 尚未入鼎)。
int receive_object(object ob, int from_inventory)
{
    if( !::receive_object(ob, from_inventory) ) return 0;
    call_out("recheck_unknown_mix", 0);
    return 1;
}

// hold_object -- get X from reactor 時 get.c 呼叫。回 1 表「鎖住、拿不出」。
//   封印中一律鎖死(沿用 closed)﹔解封後可自由取料﹐取完重算不知名旗標。
int hold_object(object ob)
{
    if( query("sealed") ) {
        notify_fail("丹鼎封著﹐裡頭的東西取不出來。先解封(conjure green dispel on reactor)。\n");
        return 1;
    }
    // 解封狀態：允許取出﹐取後旗標待下一動作重算(此處延後 call_out 重算﹐免取料當下統計到自己)。
    call_out("recheck_unknown_mix", 0);
    return 0;
}

// === 結丹 ===

// do_prepare -- prepare [mixture]：把鼎內煉足火候的配方結成丹藥(docs L65)。
//   守則(動手毀料前全部查完)：
//     1. 須認得 prepare 的對象是本鼎(arg 比對 id﹐或不帶參數時就近本鼎)。
//     2. 鼎須已解封(封著取不出丹﹐也結不了)。
//     3. 鼎內須有 mixture。
//     4. 不知名配方 / 過熱 -> 燒焦(毀內容)﹐不出丹。
//     5. 火候須達標(query("heat_ok")﹐由丹爐煉足後 set)。未達 -> 拒絕、不毀料。
//   通過後：每份 mixture -> 一粒對應丹藥﹐移到玩家身上(COMBINED_ITEM 自動合併)。
int do_prepare(string arg)
{
    object me = this_player();
    object ob, pill_ob, *mixes;
    string pill_path, cname;
    int made = 0, burnt = 0;

    if( !objectp(me) ) return 0;

    // 認得對象：prepare 不帶參數﹐或 prepare mixture / prepare 丹鼎 皆收。
    if( arg && arg != "" && arg != "mixture" && arg != "配方" && arg != "丹方"
    &&  !id(arg) )
        return 0;

    // 鼎須解封。
    if( query("sealed") )
        return notify_fail("丹鼎還封著﹐先 conjure green dispel on reactor 解封﹐才好結丹。\n");

    // 鼎內須有料。
    if( count_mixture() < 1 )
        return notify_fail("丹鼎空空如也﹐沒有配方可結丹。\n");

    // 不知名配方 / 過熱 -> 燒焦(docs L79-80)。
    if( query("unknown_mix") || query("overheated") ) {
        mixes = filter_array(all_inventory(this_object()),
            (: $1->query("mixture") :));
        foreach(ob in mixes) destruct(ob);
        set("heat_ok", 0);
        set("overheated", 0);
        set("unknown_mix", 0);
        message_vision(HIR
            "$N揭開丹鼎﹐只見鼎中藥料早已焦黑成一團﹐火候失了分寸﹐這一爐算是廢了。\n"
            NOR, me);
        return 1;
    }

    // 火候須達標(由丹爐煉足後 set("heat_ok",1))。
    if( !query("heat_ok") )
        return notify_fail("鼎中藥料火候未足﹐結不成丹。須先置入丹爐﹐生火煉足火候。\n");

    // ── 通過所有檢查﹐正式結丹 ──
    mixes = filter_array(all_inventory(this_object()),
        (: $1->query("mixture") :));

    foreach(ob in mixes) {
        int n = (int)ob->query_amount();
        if( n < 1 ) n = 1;
        pill_path = ob->query_pill();
        if( !stringp(pill_path) ) { burnt += n; destruct(ob); continue; }

        pill_ob = new(pill_path);
        if( !objectp(pill_ob) ) { burnt += n; destruct(ob); continue; }

        // 成品丹藥皆為 COMBINED_ITEM(有 set_amount/amount﹐見 obj/medication/
        // alchemist/*.c)﹐一次結 n 粒﹔保險起見以 function_exists 守一道﹐
        // 無 set_amount 的異種藍本則逐粒 clone。
        if( function_exists("set_amount", pill_ob) ) {
            pill_ob->set_amount(n);
            pill_ob->move(me);
        } else {
            int i;
            pill_ob->move(me);
            for(i = 1; i < n; i++) new(pill_path)->move(me);
        }
        cname = (string)pill_ob->query("name");
        made += n;
        destruct(ob);
    }

    // 火候用盡﹐重置鼎狀態。
    set("heat_ok", 0);
    set("overheated", 0);
    set("unknown_mix", 0);

    if( made > 0 )
        message_vision(HIY
            "$N揭開煉足火候的丹鼎﹐一陣藥香撲鼻﹐鼎中凝成" + chinese_number(made)
            + "粒" + (cname || "丹藥") + "﹗\n" NOR, me);
    if( burnt > 0 )
        tell_object(me, "(有 " + burnt + " 份配方來路不明﹐結丹時化為烏有。)\n");
    return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
