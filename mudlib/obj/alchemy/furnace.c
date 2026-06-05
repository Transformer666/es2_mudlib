// furnace.c -- 青銅丹爐：盛丹鼎、燃松柴、隨時間累積火候煉丹的爐具。
//
// 來源：docs/02-遊戲系統與機制/06-煉丹與書本系統.md
//   L33「青銅丹爐 (Bronze furnace) 1 兩黃金」、
//   L60「put reactor in furnace（鼎放爐）」、
//   L61「setup furnace toward south（設定爐位）」、
//   L62「ignite firewood / put firewood in furnace（依 kW 範圍 13-15 根松柴）」、
//   L63「維持火力直到火候達 10 分」、
//   L75 小還丹「火候：800-820 kJ，130-150 kW」、
//   L79-80「混錯 -> 火候失控 -> 燒焦」。
//   火候目標值另見 obj/medication/alchemist/minor_heal_pill.c::produce_param
//   (min_heat 800 / max_heat 820 / min_heat_power 130 / max_heat_power 150)。
//
// === 狀態機 ===
//   query("direction")  -- setup <方位> 設定爐位後方可點火(docs L61)。
//   query("lit")        -- ignite 點火後 1﹔每 TICK 由 burn() 累積火候。
//   query("heat")       -- 已累積火候(kJ﹐對齊 produce_param min/max_heat)。
//   query("power")      -- 當前供火功率(kW)﹐= 爐中松柴總根數 * kw_each。
//   進程：put reactor in furnace -> setup furnace toward <方位> -> ignite firewood
//         -> put firewood in furnace(13-15 根)-> 隨 call_out("burn") 累積火候 ->
//         火候落 [min_heat, max_heat] 且功率落 [min_power, max_power]：鼎 set("heat_ok",1)﹔
//         火候衝過 max_heat 仍燒：過熱 -> 鼎 set("overheated",1)﹐燒焦(docs L79-80)。
//
// === 火候累積模型(數值來源見上﹐未明處集中於此 #define 並標明) ===
//   docs：130-150 kW(13-15 根松柴)維持「10 分」-> 火候落 800-820 kJ。
//   以 TICK_SECONDS 秒一跳的 call_out 累積﹕10 分 = 600 秒 = 600/TICK_SECONDS 跳。
//   每跳火候增量 dHeat = power(kW) * TICK_SECONDS / HEAT_DIVISOR。
//   令 135 kW(功率窗中值) 跑滿 600 秒(10 分)恰達 810 kJ(火候窗中值)﹐反解：
//     810 = 135 * 600 / HEAT_DIVISOR  ->  HEAT_DIVISOR = 100。
//   故 TICK=15 時﹐130kW -> 19.5/跳、150kW -> 22.5/跳﹐約 40 跳(10 分)逼近窗。
//
//   「準確落窗」之關鍵(否則一跳就可能從 798 衝到 820 以上)：burn() 在「火候尚
//   未達 min_h、但加一跳會衝過 max_h」時﹐把火候「收」到恰落窗中(min_h..max_h)﹐
//   模擬方士臨門收火。如此只要功率落在 [min_power,max_power](13-15 根)﹐火候
//   必穩穩落窗 -> 成丹﹔功率過大(根數逾窗)時收火失準﹐才會過熱燒焦。
//   此 HEAT_DIVISOR / 收火邏輯為「docs 未明示的換算與控火細節」﹐集中於此便於校調。
//
// === 可驗(wiz/debug)途徑 ===
//   火候須真火慢熬 10 分﹐不利測試。故加：
//     setup furnace heat <值>   -- 僅 wizardp 可用﹐直接設火候(query("heat"))﹐
//                                  並立即跑一次 check_heat 判定﹐供驗收快速達標。
//   非巫師玩家走正規流程(ignite + 松柴 + 等火候)。
//
// 容器機制沿用 CONTAINER_ITEM(/std/item/container)﹕accept_object 控放鼎/投柴。
//
// runtime 鐵則：丹爐為死物﹐destruct 僅及燒焦時的死物配方(透過鼎)﹐不涉 living
//   die/destruct(#10)﹔非 NPC﹐不 include <weapon.h>(#12)。前置宣告自訂函式(#12)。

#include <ansi.h>

inherit CONTAINER_ITEM;

// === 火候/功率參數 ===
#define TICK_SECONDS    15      // call_out("burn") 心跳間隔(秒)。
#define HEAT_DIVISOR    100     // 火候換算係數(見檔頭推導)：dHeat = kW*sec/此值。
#define DEFAULT_MIN_HEAT    800 // 後備火候窗(無 produce_param 時)：docs 小還丹值。
#define DEFAULT_MAX_HEAT    820
#define DEFAULT_MIN_POWER   130
#define DEFAULT_MAX_POWER   150
#define OVERHEAT_SLACK      40  // 火候超過 max_heat 此餘量仍續燒 -> 判過熱燒焦。

// 合法爐位(docs L61：setup furnace toward south)。八方皆收﹐供爐位設定。
#define VALID_DIRS ({ "north","south","east","west", \
                      "northeast","northwest","southeast","southwest", \
                      "東","南","西","北","東北","西北","東南","西南" })

// 前置宣告(lesson #12)。
private object reactor_in();
private int total_firewood_kw();
private int *heat_window();
int do_setup(string arg);
int do_ignite(string arg);
void burn();
void check_heat();
private void stop_fire();

void create()
{
    set_name("青銅丹爐", ({ "bronze furnace", "furnace", "丹爐", "爐" }));
    set_weight(20000);
    set_max_encumbrance(80000);     // 容得下丹鼎 + 數十根松柴。
    if( !clonep() ) {
        set("unit", "座");
        set("value", 10000);        // docs L33：1 兩黃金 = 10000 文。
        set("long",
            "一座厚重的青銅丹爐﹐爐膛深廣﹐爐壁焦黑﹐底下留著進柴的爐口。\n"
            "煉丹時把封好的丹鼎置於爐膛(put reactor in furnace)﹐設定爐位\n"
            "(setup furnace toward <方位>)﹐點火(ignite firewood)後投入松柴﹐\n"
            "守爐文武﹐待火候煉足﹐便能結丹。\n");
        // query("furnace")：供丹鼎 / put 指令辨識「這是丹爐」用。
        set("furnace", 1);
    }
    // 丹爐是「盛鼎燃柴的爐具」而非「可進入的房間」。同 reactor.c：擺空 exits 佔位﹐
    // 抑制 CONTAINER_ITEM::setup 自動補的 exits/out（免玩家 enter furnace）。
    set("exits", ([ ]));
    setup();
}

void init()
{
    add_action("do_setup", "setup");
    add_action("do_ignite", "ignite");
}

// === 內部查詢 ===

// reactor_in -- 爐中的丹鼎(若有)。否則回 0。
private object reactor_in()
{
    object ob;
    foreach(ob in all_inventory(this_object()))
        if( ob->query("reactor") ) return ob;
    return 0;
}

// total_firewood_kw -- 爐中松柴提供的總供火功率(kW)= Σ(根數 * 每根 kw_each)。
private int total_firewood_kw()
{
    object ob;
    int kw = 0, n;

    foreach(ob in all_inventory(this_object())) {
        if( !ob->query("firewood") ) continue;
        n = (int)ob->query_amount();
        if( n < 1 ) n = 1;
        kw += n * (int)ob->query("kw_each");
    }
    return kw;
}

// heat_window -- 取本爐當前所煉丹方的火候/功率窗 ({ min_h, max_h, min_p, max_p })。
//   來源：鼎內任一份 mixture 對應成品的 produce_param(見 mixture.c / 各丹藥檔)。
//   找不到(空鼎 / 載不起)則回 docs 小還丹後備值 DEFAULT_*。burn() 收火與
//   check_heat() 判定共用此窗﹐確保兩處數值一致(單一真相源)。
private int *heat_window()
{
    object reactor, ob;
    mapping pp = 0;
    int min_h, max_h, min_p, max_p;

    reactor = reactor_in();
    if( reactor ) {
        foreach(ob in all_inventory(reactor)) {
            if( ob->query("mixture") ) { pp = ob->query_produce_param(); break; }
        }
    }
    min_h = (pp && pp["min_heat"])       ? pp["min_heat"]       : DEFAULT_MIN_HEAT;
    max_h = (pp && pp["max_heat"])       ? pp["max_heat"]       : DEFAULT_MAX_HEAT;
    min_p = (pp && pp["min_heat_power"]) ? pp["min_heat_power"] : DEFAULT_MIN_POWER;
    max_p = (pp && pp["max_heat_power"]) ? pp["max_heat_power"] : DEFAULT_MAX_POWER;
    return ({ min_h, max_h, min_p, max_p });
}

// === 容器守則 ===
// 只准放丹鼎與松柴。丹鼎一座為限。點火中不得再放鼎(只能添柴)。
int accept_object(object player, object ob)
{
    if( !objectp(ob) ) return 0;

    if( ob->query("reactor") ) {
        if( reactor_in() ) {
            notify_fail("爐膛裡已經架著一座丹鼎了。\n");
            return 0;
        }
        if( !ob->query_sealed() ) {
            notify_fail("丹鼎沒封好就入爐﹐藥氣要散。先 conjure green seal on reactor。\n");
            return 0;
        }
        return 1;
    }

    if( ob->query("firewood") )
        return 1;

    notify_fail("丹爐裡只放得下丹鼎與松柴。\n");
    return 0;
}

// 點火中不准把鼎/柴取出(避免半途破壞火候統計)。熄火後自由取放。
int hold_object(object ob)
{
    if( query("lit") && (ob->query("reactor") || ob->query("firewood")) ) {
        notify_fail("爐火正旺﹐這時候動爐裡的東西太危險了。先讓火滅了再說。\n");
        return 1;
    }
    return 0;
}

// === 爐位設定 ===
// setup furnace toward <方位>   -- 設定爐位(docs L61)。
// setup furnace heat <值>       -- 僅 wizardp：直接設火候供測試(見檔頭可驗途徑)。
int do_setup(string arg)
{
    object me = this_player();
    string what, val, dir;
    int hv;

    if( !objectp(me) ) return 0;
    if( !arg || arg == "" )
        return notify_fail("用法：setup furnace toward <方位>（如 setup furnace toward south）。\n");

    // 先認得是對本爐 setup(arg 須含本爐 id)。
    // 形式一：setup furnace toward south / setup 丹爐 朝 南
    if( sscanf(arg, "%s toward %s", what, val) == 2
    ||  sscanf(arg, "%s 朝 %s", what, val) == 2
    ||  sscanf(arg, "%s 向 %s", what, val) == 2 ) {
        if( !id(what) ) return 0;
        dir = val;
        if( member_array(dir, VALID_DIRS) < 0 )
            return notify_fail("「" + dir + "」不是個正經爐位。試 south / 南 等八方。\n");
        set("direction", dir);
        message_vision("$N仔細地將" + name() + "的爐口轉向" + dir + "﹐安頓妥當。\n", me);
        return 1;
    }

    // 形式二(wiz/debug)：setup furnace heat <值>
    // 字串轉整數沿用本庫慣例 sscanf(s,"%d",v)（非 to_int﹐to_int 本庫只用於數值運算）。
    if( sscanf(arg, "%s heat %d", what, hv) == 2
    ||  sscanf(arg, "%s 火候 %d", what, hv) == 2 ) {
        if( !id(what) ) return 0;
        if( !wizardp(me) )
            return notify_fail("凡人煉丹須老老實實生火守爐﹐哪能憑空調火候。\n");
        set("heat", hv);
        tell_object(me, sprintf("(debug)火候直接設為 %d kJ﹐隨即判定。\n", hv));
        check_heat();
        return 1;
    }

    return notify_fail("用法：setup furnace toward <方位>（如 setup furnace toward south）。\n");
}

// === 點火 ===
// ignite firewood / ignite furnace -- 點燃爐火(docs L62)。
//   須已設爐位、爐中已架封好的丹鼎、爐中已有松柴。點著後啟動 burn() 心跳。
int do_ignite(string arg)
{
    object me = this_player();
    object reactor;

    if( !objectp(me) ) return 0;

    // 認得對象(ignite firewood / furnace / 丹爐 / 柴皆收)。
    if( arg && arg != "" && arg != "firewood" && arg != "furnace"
    &&  arg != "松柴" && arg != "柴" && arg != "丹爐" && arg != "爐"
    &&  !id(arg) )
        return 0;

    if( query("lit") )
        return notify_fail("爐火正旺著呢。\n");

    if( !query("direction") )
        return notify_fail("先設定爐位(setup furnace toward <方位>)再點火。\n");

    reactor = reactor_in();
    if( !reactor )
        return notify_fail("爐膛裡還沒架丹鼎﹐點火也是空燒。先 put reactor in furnace。\n");

    if( total_firewood_kw() <= 0 )
        return notify_fail("爐裡沒有松柴﹐點不著火。先 put firewood in furnace。\n");

    set("lit", 1);
    set("heat", query("heat") || 0);
    set("overheated", 0);
    remove_call_out("burn");
    call_out("burn", TICK_SECONDS);
    message_vision(HIR "$N點燃爐中松柴﹐火舌舔著鼎底﹐丹爐熊熊燒了起來。\n" NOR, me);
    return 1;
}

// === 火候心跳 ===
// burn -- 每 TICK_SECONDS 跑一次：依當前松柴功率累積火候﹐判定達標/過熱/燒盡。
void burn()
{
    object reactor;
    int power, dheat, heat;
    int *win, min_h, max_h, min_p, max_p;

    if( !query("lit") ) return;

    reactor = reactor_in();
    if( !reactor ) {                // 鼎不在了(被取走)﹐熄火。
        stop_fire();
        return;
    }

    power = total_firewood_kw();
    if( power <= 0 ) {              // 柴燒盡了(或被取走)﹐火滅。
        if( environment(this_object()) )
            tell_room(environment(this_object()),
                name() + "的柴火漸漸燒盡﹐爐火熄了。\n");
        stop_fire();
        return;
    }
    set("power", power);

    win = heat_window();
    min_h = win[0]; max_h = win[1]; min_p = win[2]; max_p = win[3];

    // 累積火候：dHeat = power(kW) * TICK_SECONDS / HEAT_DIVISOR(見檔頭推導)。
    heat  = (query("heat") || 0);
    dheat = power * TICK_SECONDS / HEAT_DIVISOR;
    heat += dheat;

    // 臨門收火：功率落窗(13-15 根)且這一跳會從「未達 min_h」直接衝過 max_h﹐
    // 表方士此時收火﹐把火候恰收進窗中(取窗中值)﹐確保穩穩成丹而非過頭。
    // 功率不在窗(根數逾窗)時不收火﹐任其衝過 -> check_heat 判過熱燒焦。
    if( power >= min_p && power <= max_p
    &&  (query("heat") || 0) < min_h && heat > max_h )
        heat = (min_h + max_h) / 2;

    set("heat", heat);

    check_heat();

    // 若 check_heat 已熄火(達標或過熱)﹐不再排下一跳。
    if( query("lit") )
        call_out("burn", TICK_SECONDS);
}

// check_heat -- 判定當前火候/功率落點﹐驅動鼎的 heat_ok / overheated。
//   火候窗 [min_heat,max_heat] 與功率窗 [min_power,max_power] 取自鼎內配方對應
//   成品的 produce_param(找不到則用 DEFAULT_*﹐即 docs 小還丹值)。
//   - 火候在窗內且功率在窗內 -> 鼎 set("heat_ok",1)﹐熄火(可解封結丹)。
//   - 火候衝破 max_heat + OVERHEAT_SLACK -> 鼎 set("overheated",1)﹐熄火(燒焦)。
//   - 其餘 -> 續燒。
void check_heat()
{
    object reactor;
    int heat, power;
    int *win, min_h, max_h, min_p, max_p;

    reactor = reactor_in();
    if( !reactor ) return;

    win = heat_window();        // 與 burn() 收火共用同一火候/功率窗(單一真相源)。
    min_h = win[0]; max_h = win[1]; min_p = win[2]; max_p = win[3];

    heat  = query("heat") || 0;
    power = total_firewood_kw();

    // 不知名配方(混錯)：火候一旦上來就失控燒焦(docs L79-80)。
    if( reactor->query("unknown_mix") && heat >= min_h ) {
        reactor->set("overheated", 1);
        set("lit", 0);
        remove_call_out("burn");
        if( environment(this_object()) )
            tell_room(environment(this_object()),
                HIR "丹鼎中藥料配伍駁雜﹐火候一上來便失了控﹐爐裡冒起一股焦黑濃煙﹗\n" NOR);
        return;
    }

    // 過熱：火候衝破上限太多 -> 燒焦。
    if( heat > max_h + OVERHEAT_SLACK ) {
        reactor->set("overheated", 1);
        reactor->set("heat_ok", 0);
        set("lit", 0);
        remove_call_out("burn");
        if( environment(this_object()) )
            tell_room(environment(this_object()),
                HIR "爐火過旺﹐丹鼎火候燒過了頭﹐鼎中藥料登時焦糊﹐廢了﹗\n" NOR);
        return;
    }

    // 達標：火候落窗、功率落窗 -> 火候煉成﹐熄火待結丹。
    //   功率窗只在「正在燒火(query lit)」時檢查(正規流程：松柴根數須對)﹔
    //   wiz/debug 直接 set 火候時並未生火(power 可能為 0)﹐此時只認火候落窗﹐
    //   讓巫師得以快速驗證結丹(見檔頭可驗途徑)。
    if( heat >= min_h && heat <= max_h
    &&  (!query("lit") || (power >= min_p && power <= max_p)) ) {
        reactor->set("heat_ok", 1);
        reactor->set("overheated", 0);
        set("lit", 0);
        remove_call_out("burn");
        if( environment(this_object()) )
            tell_room(environment(this_object()),
                HIY "丹鼎中藥香漸濃﹐火候恰到好處﹐已然煉足﹗可解封結丹了。\n" NOR);
        return;
    }

    // 火候已在窗中但功率不在窗(柴太多/太少)：提示但續燒﹐讓玩家有機會調柴。
    // (功率窗在點火前由松柴根數決定﹐此處僅作續燒﹐不另強制。)
}

// stop_fire -- 統一熄火收尾(清心跳、落 lit)。
private void stop_fire()
{
    set("lit", 0);
    remove_call_out("burn");
}

// vim: set ts=4 sw=4 syntax=lpc
