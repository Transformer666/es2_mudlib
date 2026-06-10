// reincarnate.c -- 「投胎」轉世指令：以業力為成本，轉換種族但保留等級與技能。
//
// 設定來源：docs/02-遊戲系統與機制/04-業力與聲望.md + memory/specs/races.md。
//   業力(karma) 是「玩另一個種族」的轉換成本，但「又不至於完全重練」──
//   故投胎只『換種族』，等級(level) 與技能(skills/learned) 全數保留。
//
// 已驗證的機制（動工前實讀 mudlib 原碼）：
//   * set_race(race)：feature/char/score.c。改種族名後呼叫 RACE_D->initialize
//     重 roll 體質──但 init_attribute/init_statistic (feature/attribute.c、
//     feature/statistic.c) 都「只填 undefinedp 的鍵」(保護每次登入 setup_char
//     的 no-arg 重呼叫)，對既有角色是 no-op。故本指令投胎前必須先
//     clear_attribute() + delete_stat(gin/kee/sen) 把種族決定的欄位清成未定義，
//     再讓 set_race 依新種族重 roll (見 confirm_reincarnate 內註解)。
//     set_race 完全不動 skills[]/learned[]/level──等級與技能自然保留。
//   * 業力存在「連線(link)物件」上 (obj/login.c，inherit F_DBASE)：
//       讀：me->link()->query("karma")            (login.c::query 無保護，隨處可讀)
//       扣：me->link()->add("karma", -成本)        (login.c::set/add 受 USER_PROTECT)
//     USER_PROTECT (include/user.h) 在 call_other 時要求 caller euid 為
//     ROOT/DOMAIN/MUDLIB 或與 link 同 euid。/cmds/ 物件 UID==ROOT_UID
//     (adm/obj/master.c::creator_file)，且 create() seteuid(getuid())→euid=ROOT，
//     故本指令可合法 add 業力 (同理 cmds/usr/chfn.c、tune.c 亦直接 link->set)。
//   * 各種族業力門檻：daemon/race/<race>.c::create() 的 set("karma", N)，
//     讀法 RACE_D(race)->query("karma")。完全比照 logind.c::get_race 的驗證：
//       member_array(race, user_race) → kar=RACE_D(race)->query("karma")
//       → 業力不足則拒 → ob->add("karma", -kar)。本指令鏡像之。
//   * 可投胎的 11 種族清單 = logind.c 的 user_race (隱藏種族 avatar 不在內，拒絕)。
//
// 安全設計：投胎是重大不可逆操作 (重 roll 體質、扣業力)，採「互動式二次確認」
//   (input_to 'y/n'，比照 cmds/std/cestablish.c)──單一打錯字不會投胎。
//   另擋住「戰鬥中 / busy 中」投胎。中文別名見 cmds/std/投胎.c。
//
// 注意（待實機驗證的風險）：投胎到 human 時，human.c::initialize 有 0.01% 機率
//   set_race("avatar")──與「創角」時完全相同的隱藏彩蛋，屬預期行為，不另處理。

#include <ansi.h>
#include <login.h>
#include <statistic.h>      // TYPE_HEALTH：重掛精氣神/HP 的回復器用

inherit F_CLEAN_UP;

// 可投胎的 11 個玩家種族。**必須與 adm/daemons/logind.c 的 user_race 一致**
// (該變數為 private global、無對外 getter，故此處鏡像一份；隱藏種族 avatar
//  不在內)。各種族的業力門檻仍即時讀自 daemon/race/<race>.c (見 race_cost)，
//  故門檻數值的唯一真實來源仍是各 race daemon，這裡只列「哪些種族可投」。
private string *playable_race = ({
    "human", "headless", "malik", "yaksa", "ashura", "dingling",
    "woochan", "jiaojao", "blackteeth", "yenhold", "rainnar"
});

private void create() { seteuid(getuid()); }

// 取得玩家的業力 (存在 link 物件上；無連線者視為 0，比照 reputation.c)。
private int query_karma(object me)
{
    object link;

    if( !(link = me->link()) ) return 0;
    return (int)link->query("karma");
}

// 取得某種族的投胎業力門檻 (daemon/race/<race>.c 的 set("karma",N))。
private int race_cost(string race)
{
    return (int)RACE_D(race)->query("karma");
}

// 驗證 race 是否為「可投胎的真實種族」：
//   * 必須在 logind.c 的 user_race 清單內 (排除 avatar 等隱藏/非玩家種族)。
//   * 不能投胎成自己目前的種族。
// 回傳 0 = 合法；否則回傳給玩家看的錯誤字串 (notify_fail 用)。
private string validate_race(object me, string race)
{
    if( !race || race == "" )
        return "你要投胎成哪一個種族﹖（用 reincarnate 不加參數可列出可投胎的種族。）\n";

    if( member_array(race, playable_race) == -1 )
        return "世間並無「" + race + "」這個可投胎的種族。\n";

    if( race == me->query_race() )
        return "你本來就是" + to_chinese(me->query_race()) + "，何須再投胎成" +
            to_chinese(race) + "﹖\n";

    return 0;
}

// 列出玩家「目前業力投得起、且非現種族」的種族 (比照 logind.c::list_user_race)。
private void list_choices(object me)
{
    string race, msg;
    int karma, cost;

    karma = query_karma(me);

    msg = HIW "【 業力投胎 】" NOR "你現有業力 " HIM + karma + NOR " 點。\n";
    msg += "投胎可轉換種族（保留等級與技能），所需業力如下：\n\n";

    foreach( race in playable_race ) {
        if( race == me->query_race() ) continue;     // 跳過自己現在的種族
        cost = race_cost(race);
        msg += sprintf("   %-22s %s%3d 點%s%s\n",
            to_chinese(race) + "(" + race + ")",
            (karma >= cost) ? HIG : RED,
            cost,
            (karma >= cost) ? "" : "（業力不足）",
            NOR);
    }

    msg += "\n指令格式﹕reincarnate <種族英文代號>  （例：reincarnate yaksa）\n";
    msg += CYN "（投胎是重大轉變，下指令後會再問一次是否確定。）\n" NOR;
    write(msg);
}

int main(object me, string arg)
{
    string err, race;
    int karma, cost;

    // 注意：此處刻意「不」用 SECURED_COMMAND。中文別名 投胎.c 會以
    // call_other 轉呼叫本 main()，屆時 previous_object() 是別名指令物件而非
    // 玩家，SECURED_COMMAND 會誤判而擋掉中文指令。本 mudlib 凡有中文別名的
    // 指令 (digest/devour/spitfire/gnaw/reputation…) 皆同此慣例不加該巨集；
    // 安全性改由「對 me 操作 + input_to 二次確認」保證。

    // 無參數：列出可投胎的種族與業力需求。
    if( !arg || arg == "" ) {
        list_choices(me);
        return 1;
    }

    race = lower_case(arg);

    // 戰鬥中 / 忙碌中不可投胎 (避免脫戰逃生 / 狀態錯亂)。
    if( sizeof(me->query_enemy()) )
        return notify_fail("你正在激戰之中，沒辦法靜下心來參透輪迴。\n");
    if( me->is_busy() )
        return notify_fail("你正忙著，沒辦法靜下心來參透輪迴。\n");

    // 鬼魂不可用本指令投胎 (鬼魂另有死亡轉世流程 LOGIN_D->reincarnate)。
    // 本指令會重 roll 精氣神，會破壞鬼魂特有的設定 (kee 已刪、gin/sen 走
    // TYPE_WASTING，見 adm/daemons/chard.c::setup_char)。
    if( me->query("life_form") == "ghost" )
        return notify_fail("你如今魂魄無依，得先還陽或轉世，方能再論投胎換族之事。\n");

    // 種族合法性 (真實可投胎種族、且非現種族)。
    if( err = validate_race(me, race) )
        return notify_fail(err);

    // 業力門檻：必須 ≥ 該種族成本，否則拒絕 (此處只檢查，尚未扣)。
    karma = query_karma(me);
    cost = race_cost(race);
    if( karma < cost )
        return notify_fail(sprintf(
            "投胎成%s需要 %d 點業力，你只有 %d 點，業力不足，投不了這個種族。\n",
            to_chinese(race), cost, karma));

    // 互動式二次確認 (比照 cmds/std/cestablish.c 的 input_to 'y/n' 模式)：
    // 投胎重大不可逆，避免單一打錯字就投胎。
    write(sprintf(HIY
        "你打算投胎轉世成「%s」(%s)。\n" NOR
        "這將" HIR "重塑你的根骨體質" NOR "並耗去 " HIM "%d" NOR " 點業力"
        "（你目前的等級與所有武學技能" HIG "都會保留" NOR "）。\n"
        HIR "注意：八維屬性與精氣神將重置為新種族的出生之資，"
        "前世修練所積的素質增益不會隨魂而來。\n" NOR
        "你確定要投胎嗎(y/n)﹖", to_chinese(race), race, cost));
    input_to("confirm_reincarnate", me, race);
    return 1;
}

// 確認步驟：只有明確回答 y/Y 才真正投胎；其餘一律取消。
// 投胎瞬間「重新驗證」業力與種族（玩家在確認期間狀態可能改變），確保安全。
private void confirm_reincarnate(string yn, object me, string race)
{
    object link;
    string old_race;
    int karma, cost;

    if( !objectp(me) ) return;

    // 確保扣業力時 euid==ROOT (本指令 UID 為 ROOT_UID)，通過 link 的
    // USER_PROTECT。比照 cestablish.c 在 input_to callback 內重設 euid 的慣例
    // (euid 不保證跨 input_to 延續)。
    seteuid(getuid());

    if( !yn || yn == "" || (yn[0] != 'y' && yn[0] != 'Y') ) {
        tell_object(me, "你打消了投胎的念頭。\n");
        return;
    }

    // 重新檢查（確認期間玩家可能進戰鬥、業力可能變動、或已是該種族）。
    if( sizeof(me->query_enemy()) ) {
        tell_object(me, "你正在激戰之中，沒辦法靜下心來參透輪迴。\n");
        return;
    }
    if( me->query("life_form") == "ghost" ) {   // 確認期間死了：擋下，免得
        tell_object(me, "你已是一縷幽魂，此刻投不得胎。\n");   // 重 roll 毀掉鬼魂狀態
        return;
    }
    if( validate_race(me, race) ) {
        tell_object(me, "投胎之事有變，這個種族此刻投不得。\n");
        return;
    }

    karma = query_karma(me);
    cost = race_cost(race);
    if( karma < cost ) {
        tell_object(me, "你的業力不足，投不了這個種族。\n");
        return;
    }

    if( !(link = me->link()) ) {
        tell_object(me, "你的連線狀態異常，現在無法投胎。\n");
        return;
    }

    old_race = me->query_race();

    // 1) 扣業力 (link 物件；本指令 euid==ROOT，通過 USER_PROTECT)。
    link->add("karma", -cost);

    // 2) 換種族。init_attribute/init_statistic 都「只填 undefinedp 的鍵」，
    //    老角色屬性與精氣神上限早已定義，直接 set_race 會是 no-op (只改種族
    //    名字串，素質完全不換)。故先把「種族決定的欄位」清成未定義，再讓
    //    set_race -> RACE_D->initialize 依新種族重 roll；等級/職業/技能/
    //    score/任務旗標/年齡一概不碰。
    me->clear_attribute();      // 八維屬性 (obj/user.c 有 USER_PROTECT 包裝)
    me->delete_stat("gin");     // 精氣神：上限/heal/現值/回復器全清，
    me->delete_stat("kee");     //   由新種族 init_statistic 重設上限
    me->delete_stat("sen");
    me->set_race(race);

    // 3) 重建衍生值：HP 上限照建角公式 con*5 (adm/daemons/chard.c::setup_char)，
    //    heal_stat(0)/supplement_stat(0) 把 effective/current 夾回新上限內
    //    (仿 std/race/humanoid.c 的 clamp 慣例)；TYPE_HEALTH 會把剛清掉的
    //    精氣神 current/effective 補滿到新上限並重掛回復器。
    //    ※ 不可圖方便改呼叫 CHAR_D->setup_char()：它會 set_temp("apply", ...)
    //      整個重置暫時加成，穿戴中武器/防具的加成會全部消失。
    //    (food/water 上限依舊屬性，下次登入 humanoid.c::setup 會無條件重算。)
    me->set_stat_maximum("HP", (int)me->query_attr("con") * 5);
    me->heal_stat("HP", 0);
    me->supplement_stat("HP", 0);
    me->set_stat_regenerate("HP", TYPE_HEALTH);
    me->set_stat_regenerate("gin", TYPE_HEALTH);
    me->set_stat_regenerate("kee", TYPE_HEALTH);
    me->set_stat_regenerate("sen", TYPE_HEALTH);

    // 4) 投胎演出 (脫胎換骨)。
    message_vision(HIM
        "\n$N周身光華流轉，三魂七魄似被一隻無形大手攬入輪迴，"
        "再睜眼時已是脫胎換骨、面目一新。\n" NOR, me);
    tell_object(me, sprintf(HIG
        "你自「%s」投胎轉世為「%s」，根骨體質煥然一新，"
        "往日的武學修為與江湖歷練卻盡數隨魂而來。\n" NOR,
        to_chinese(old_race), to_chinese(me->query_race())));
    tell_object(me, sprintf("（耗去 %d 點業力，剩餘業力 %d 點。）\n",
        cost, query_karma(me)));

    log_file("REINCARNATE", sprintf("[%s] %s(%s) %s -> %s, cost %d karma, level %d\n",
        ctime(time()), me->name(), me->query("id"),
        old_race, me->query_race(), cost, me->query_level()));

#ifdef SAVE_USER
    me->save();
#endif
}

int help(object me)
{
    write(@HELP
指令格式﹕reincarnate                    （列出可投胎的種族與所需業力）
          reincarnate <種族英文代號>      （例：reincarnate yaksa）

「投胎」是以「業力」為成本的轉世之術。山海經眾族各有業障門檻，業力愈
高，能投胎的種族愈奇詭強大（如夜叉需 35 點、巫首與阿修羅需 30 點，而黑
齒只需 3 點）。

投胎只會「轉換你的種族」──你的新身軀會依新種族重塑根骨體質，但你過往
所修的一切武學技能、以及累積的等級與江湖歷練，都會原封不動地隨魂而來，
不必從頭重練。

但須留意：重塑根骨是脫胎換骨之變──八維屬性與精、氣、神都會重置為新種
族的「出生之資」，前世升級修練所累積的素質增益，並不會隨魂帶到新身軀。

投胎是重大且不可逆的轉變，下達指令後會再問一次是否確定(y/n)，確認後才
會真正投胎並扣除業力。戰鬥之中或身有他務時無法投胎。

中文別名為「投胎」。相關指令﹕reputation（查業力）、score、skills
HELP
    );
    return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
