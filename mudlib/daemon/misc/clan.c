

// 幫會（clan）中央管理 daemon。
//
// 原先所有幫派狀態都散落在玩家物件的 clan/* 屬性上，沒有任何中央紀錄，
// 因此離線成員、幫派金庫、勢力範圍等資料都無法保存或查詢。
// 本 daemon 提供一份持久化的中央幫派名冊，作為離線可查詢的權威來源；
// 玩家身上的 clan/* 屬性仍保留作為「上線中」的快取（fast-path）。
//
// 資料結構：
//   clans = ([ "<幫名>": ([
//       "founder"  : uid,                  // 創幫者 uid（小寫，等同 query("id")）
//       "created"  : time,                 // 創立時間
//       "leader"   : uid,                  // 現任幫主 uid
//       "members"  : ([ uid : clan_level ]),// 成員 uid -> 職等(1幫眾/2長老/3幫主)
//       "treasury" : 0,                    // 幫派金庫（Phase 2 啟用）
//       "hall"     : "<roompath>",         // 幫派總壇房間路徑
//       "ranks"    : ([ 3:"幫主",2:"長老",1:"幫眾" ]),
//       "territory": ({}),                 // 勢力範圍（領地，Phase 3：area 字串/房間路徑陣列）
//       "allies"   : ({}),                 // 結盟幫派（Phase 3：盟友幫名陣列，雙向）
//       "wars"     : ({}),                 // 交戰幫派（Phase 3：交戰幫名陣列，雙向）
//       "war_score": ([ "<敵幫>":int ]),   // 幫戰戰功（Phase 3：對各敵幫的擊殺累計，lazy 建立）
//       "log"      : ({}),                 // 幫派事件紀錄
//   ]) ])

inherit F_CLEAN_UP;
inherit F_SAVE;

#pragma save_binary

mapping clans = ([ ]);

private void
create()
{
    seteuid(getuid());
    restore();
}

string query_save_file() { return DATA_DIR + "daemon/clan"; }

void remove()
{
    save();
}

// 為每個幫派附加一條時間戳記的事件紀錄。
private void
log_event(string name, string msg)
{
    if( !name || !stringp(msg) || undefinedp(clans[name]) ) return;
    if( !arrayp(clans[name]["log"]) ) clans[name]["log"] = ({ });
    clans[name]["log"] += ({ sprintf("[%s] %s", ctime(time()), msg) });
}

// register_clan - 建立一個新幫派的中央紀錄。回傳 1 表成功，0 表已存在或參數錯誤。
int
register_clan(string name, string founder_uid)
{
    if( !stringp(name) || !stringp(founder_uid) ) return 0;
    if( !undefinedp(clans[name]) ) return 0;

    clans[name] = ([
        "founder"  : founder_uid,
        "created"  : time(),
        "leader"   : founder_uid,
        "members"  : ([ ]),
        "treasury" : 0,
        "hall"     : 0,
        "ranks"    : ([ 3:"幫主", 2:"長老", 1:"幫眾" ]),
        "territory": ({ }),
        "allies"   : ({ }),
        "wars"     : ({ }),
        "log"      : ({ }),
    ]);
    log_event(name, founder_uid + " 創立本幫。");
    save();
    return 1;
}

// disband_clan - 解散整個幫派並刪除中央紀錄。
int
disband_clan(string name)
{
    if( !stringp(name) || undefinedp(clans[name]) ) return 0;
    map_delete(clans, name);
    save();
    return 1;
}

// add_member - 將某 uid 以指定職等加入幫派（已存在則更新職等）。
int
add_member(string name, string uid, int level)
{
    if( !stringp(name) || !stringp(uid) || undefinedp(clans[name]) ) return 0;
    if( !mapp(clans[name]["members"]) ) clans[name]["members"] = ([ ]);
    if( level < 1 ) level = 1;
    if( level > 3 ) level = 3;
    clans[name]["members"][uid] = level;
    if( level == 3 ) clans[name]["leader"] = uid;
    log_event(name, uid + " 加入本幫（職等 " + level + "）。");
    save();
    return 1;
}

// remove_member - 將某 uid 移出幫派。
int
remove_member(string name, string uid)
{
    if( !stringp(name) || !stringp(uid) || undefinedp(clans[name]) ) return 0;
    if( !mapp(clans[name]["members"]) ) return 0;
    if( undefinedp(clans[name]["members"][uid]) ) return 0;
    map_delete(clans[name]["members"], uid);
    log_event(name, uid + " 離開本幫。");
    save();
    return 1;
}

// set_member_level - 變更某成員的職等（升/降）。職等 3 同時更新幫主。
int
set_member_level(string name, string uid, int level)
{
    if( !stringp(name) || !stringp(uid) || undefinedp(clans[name]) ) return 0;
    if( !mapp(clans[name]["members"]) ) return 0;
    if( undefinedp(clans[name]["members"][uid]) ) return 0;
    if( level < 1 ) level = 1;
    if( level > 3 ) level = 3;
    clans[name]["members"][uid] = level;
    if( level == 3 ) clans[name]["leader"] = uid;
    log_event(name, uid + " 的職等變更為 " + level + "。");
    save();
    return 1;
}

// query_clan - 回傳指定幫派的完整資料 mapping（不存在回傳 0）。
mapping
query_clan(string name)
{
    if( !stringp(name) || undefinedp(clans[name]) ) return 0;
    return copy(clans[name]);
}

// query_members - 回傳指定幫派的成員 mapping ([ uid:level ])（不存在回傳 0）。
mapping
query_members(string name)
{
    if( !stringp(name) || undefinedp(clans[name]) ) return 0;
    if( !mapp(clans[name]["members"]) ) return ([ ]);
    return copy(clans[name]["members"]);
}

// query_member_level - 回傳某 uid 在某幫的職等（不存在回傳 0）。
int
query_member_level(string name, string uid)
{
    if( !stringp(name) || !stringp(uid) || undefinedp(clans[name]) ) return 0;
    if( !mapp(clans[name]["members"]) ) return 0;
    if( undefinedp(clans[name]["members"][uid]) ) return 0;
    return clans[name]["members"][uid];
}

// query_all_clans - 回傳所有幫派的原始 mapping。
mapping query_all_clans() { return copy(clans); }

// query_clan_names - 回傳所有幫派名稱的陣列。
string *query_clan_names() { return keys(clans); }

// query_leader - 回傳某幫現任幫主 uid（不存在回傳 0）。
string
query_leader(string name)
{
    if( !stringp(name) || undefinedp(clans[name]) ) return 0;
    return clans[name]["leader"];
}

// query_treasury - 回傳某幫金庫餘額。
int
query_treasury(string name)
{
    if( !stringp(name) || undefinedp(clans[name]) ) return 0;
    return clans[name]["treasury"];
}

// set_hall - 設定幫派總壇房間路徑。
int
set_hall(string name, string path)
{
    if( !stringp(name) || undefinedp(clans[name]) ) return 0;
    clans[name]["hall"] = path;
    save();
    return 1;
}

// query_hall - 回傳幫派總壇房間路徑。
string
query_hall(string name)
{
    if( !stringp(name) || undefinedp(clans[name]) ) return 0;
    return clans[name]["hall"];
}

// query_ranks - 回傳某幫的階級稱號 mapping ([ level:title ])（不存在回傳 0）。
mapping
query_ranks(string name)
{
    if( !stringp(name) || undefinedp(clans[name]) ) return 0;
    if( !mapp(clans[name]["ranks"]) )
        clans[name]["ranks"] = ([ 3:"幫主", 2:"長老", 1:"幫眾" ]);
    return copy(clans[name]["ranks"]);
}

// query_rank_title - 回傳某幫某職等的階級稱號（不存在或未設定回傳 0）。
string
query_rank_title(string name, int level)
{
    if( !stringp(name) || undefinedp(clans[name]) ) return 0;
    if( !mapp(clans[name]["ranks"]) ) return 0;
    if( undefinedp(clans[name]["ranks"][level]) ) return 0;
    return clans[name]["ranks"][level];
}

// set_rank_title - 重新命名某幫某職等(1..3)的階級稱號。回傳 1 成功，0 失敗。
int
set_rank_title(string name, int level, string title)
{
    if( !stringp(name) || undefinedp(clans[name]) ) return 0;
    if( level < 1 || level > 3 ) return 0;
    if( !stringp(title) || title == "" ) return 0;
    if( !mapp(clans[name]["ranks"]) )
        clans[name]["ranks"] = ([ 3:"幫主", 2:"長老", 1:"幫眾" ]);
    clans[name]["ranks"][level] = title;
    log_event(name, "職等 " + level + " 的稱號變更為「" + title + "」。");
    save();
    return 1;
}

// deposit - 存入金庫（Phase 2 將由幫派指令呼叫）。回傳新餘額，失敗回傳 -1。
int
deposit(string name, int amount)
{
    if( !stringp(name) || undefinedp(clans[name]) || amount <= 0 ) return -1;
    clans[name]["treasury"] += amount;
    log_event(name, "金庫存入 " + amount + "，餘額 " + clans[name]["treasury"] + "。");
    save();
    return clans[name]["treasury"];
}

// withdraw - 自金庫提出（Phase 2 將由幫派指令呼叫）。回傳新餘額，餘額不足或失敗回傳 -1。
int
withdraw(string name, int amount)
{
    if( !stringp(name) || undefinedp(clans[name]) || amount <= 0 ) return -1;
    if( clans[name]["treasury"] < amount ) return -1;
    clans[name]["treasury"] -= amount;
    log_event(name, "金庫提出 " + amount + "，餘額 " + clans[name]["treasury"] + "。");
    save();
    return clans[name]["treasury"];
}

// ==========================================================================
// Phase-3 (decision D)：幫戰(war)、領地(territory)、結盟(allies)。
//
// 三者的權威狀態都存在每個 clan 紀錄既有的 "wars" / "territory" / "allies"
// 三個陣列欄位裡（register_clan 時即建為 ({ })）。所有變動一律「就地修改 →
// save()」，與本 daemon 既有的 add_member/deposit/... 完全同一個 F_SAVE 慣例。
//
// 設計鐵則（與 chard.c 紅人 gate 的安全性互相呼應）：
//   * 幫戰與結盟都是「相互」狀態：宣戰/休戰/結盟/解盟一律「同時」改動雙方
//     兩份紀錄，故 query_war / query_ally 對 (a,b) 與 (b,a) 必對稱為真。
//     這是 chard.c 能放心用「雙方互為交戰」剝奪紅人保護的前提。
//   * 互斥保護：盟友不得對彼此宣戰；交戰中不得對彼此結盟（避免出現
//     「既是盟友又在交戰」的矛盾狀態而被 gate 誤判）。
//   * 自我保護：幫派不能對自己宣戰 / 結盟。
//   * 防呆：任何 clan 名稱不存在於 daemon 一律回 0，不建立空殼。
// ==========================================================================

// declare_war - 令 a、b 兩幫進入「相互交戰」狀態（雙向寫入兩份 wars）。
// 回傳 1 表狀態已建立（或本就在交戰），0 表參數錯誤 / 幫派不存在 /
// 兩者為自己 / 兩者為盟友（盟友須先解盟才能宣戰）。
int
declare_war(string a, string b)
{
    if( !stringp(a) || !stringp(b) || a == b ) return 0;
    if( undefinedp(clans[a]) || undefinedp(clans[b]) ) return 0;
    // 盟友不得直接宣戰，須先 unally。
    if( arrayp(clans[a]["allies"]) && member_array(b, clans[a]["allies"]) != -1 )
        return 0;
    if( !arrayp(clans[a]["wars"]) ) clans[a]["wars"] = ({ });
    if( !arrayp(clans[b]["wars"]) ) clans[b]["wars"] = ({ });
    if( member_array(b, clans[a]["wars"]) == -1 )
        clans[a]["wars"] += ({ b });
    if( member_array(a, clans[b]["wars"]) == -1 )
        clans[b]["wars"] += ({ a });
    log_event(a, "向【" + b + "】宣戰，兩幫進入交戰狀態。");
    log_event(b, "【" + a + "】向本幫宣戰，兩幫進入交戰狀態。");
    save();
    return 1;
}

// end_war - 解除 a、b 之間的交戰狀態（雙向自兩份 wars 移除）。
// 回傳 1 表已休戰（或本就無交戰），0 表參數錯誤 / 幫派不存在。
int
end_war(string a, string b)
{
    if( !stringp(a) || !stringp(b) || a == b ) return 0;
    if( undefinedp(clans[a]) || undefinedp(clans[b]) ) return 0;
    if( arrayp(clans[a]["wars"]) )
        clans[a]["wars"] -= ({ b });
    if( arrayp(clans[b]["wars"]) )
        clans[b]["wars"] -= ({ a });
    log_event(a, "與【" + b + "】休戰。");
    log_event(b, "與【" + a + "】休戰。");
    save();
    return 1;
}

// query_war - a 是否與 b 處於交戰狀態（檢查 a 的 wars 名單）。
// 因 declare_war/end_war 雙向同步，故 query_war(a,b)==query_war(b,a)。
int
query_war(string a, string b)
{
    if( !stringp(a) || !stringp(b) || undefinedp(clans[a]) ) return 0;
    if( !arrayp(clans[a]["wars"]) ) return 0;
    return member_array(b, clans[a]["wars"]) != -1;
}

// query_wars - 回傳某幫所有交戰對手的幫名陣列。
string *
query_wars(string name)
{
    if( !stringp(name) || undefinedp(clans[name]) ) return ({ });
    if( !arrayp(clans[name]["wars"]) ) return ({ });
    return copy(clans[name]["wars"]);
}

// add_ally - 令 a、b 兩幫結為盟友（雙向寫入兩份 allies）。
// 回傳 1 表已結盟（或本就是盟友），0 表參數錯誤 / 幫派不存在 /
// 兩者為自己 / 兩者正在交戰（須先 peace 才能結盟）。
int
add_ally(string a, string b)
{
    if( !stringp(a) || !stringp(b) || a == b ) return 0;
    if( undefinedp(clans[a]) || undefinedp(clans[b]) ) return 0;
    // 交戰中不得結盟，須先 end_war。
    if( arrayp(clans[a]["wars"]) && member_array(b, clans[a]["wars"]) != -1 )
        return 0;
    if( !arrayp(clans[a]["allies"]) ) clans[a]["allies"] = ({ });
    if( !arrayp(clans[b]["allies"]) ) clans[b]["allies"] = ({ });
    if( member_array(b, clans[a]["allies"]) == -1 )
        clans[a]["allies"] += ({ b });
    if( member_array(a, clans[b]["allies"]) == -1 )
        clans[b]["allies"] += ({ a });
    log_event(a, "與【" + b + "】結為盟友。");
    log_event(b, "與【" + a + "】結為盟友。");
    save();
    return 1;
}

// remove_ally - 解除 a、b 之間的盟友關係（雙向自兩份 allies 移除）。
// 回傳 1 表已解盟（或本就非盟友），0 表參數錯誤 / 幫派不存在。
int
remove_ally(string a, string b)
{
    if( !stringp(a) || !stringp(b) || a == b ) return 0;
    if( undefinedp(clans[a]) || undefinedp(clans[b]) ) return 0;
    if( arrayp(clans[a]["allies"]) )
        clans[a]["allies"] -= ({ b });
    if( arrayp(clans[b]["allies"]) )
        clans[b]["allies"] -= ({ a });
    log_event(a, "與【" + b + "】解除盟約。");
    log_event(b, "與【" + a + "】解除盟約。");
    save();
    return 1;
}

// query_ally - a 與 b 是否為盟友（檢查 a 的 allies 名單）。對稱（同 query_war）。
int
query_ally(string a, string b)
{
    if( !stringp(a) || !stringp(b) || undefinedp(clans[a]) ) return 0;
    if( !arrayp(clans[a]["allies"]) ) return 0;
    return member_array(b, clans[a]["allies"]) != -1;
}

// query_allies - 回傳某幫所有盟友的幫名陣列。
string *
query_allies(string name)
{
    if( !stringp(name) || undefinedp(clans[name]) ) return ({ });
    if( !arrayp(clans[name]["allies"]) ) return ({ });
    return copy(clans[name]["allies"]);
}

// add_territory - 把一塊「領地」(area，通常是房間路徑或地域字串) 納入某幫的
// territory 名單。回傳 1 表已納入（或本就持有），0 表參數錯誤 / 幫派不存在 /
// 該領地已被「別的」幫派占據（先到先得，未釋出前他幫不能搶）。
int
add_territory(string name, string area)
{
    string *names;
    int i;

    if( !stringp(name) || !stringp(area) || area == "" ) return 0;
    if( undefinedp(clans[name]) ) return 0;
    // 先到先得：若已被他幫占據則不得搶占。
    names = keys(clans);
    for( i = 0; i < sizeof(names); i++ ) {
        if( names[i] == name ) continue;
        if( arrayp(clans[names[i]]["territory"])
        && member_array(area, clans[names[i]]["territory"]) != -1 )
            return 0;
    }
    if( !arrayp(clans[name]["territory"]) ) clans[name]["territory"] = ({ });
    if( member_array(area, clans[name]["territory"]) == -1 )
        clans[name]["territory"] += ({ area });
    log_event(name, "將「" + area + "」納入本幫勢力範圍。");
    save();
    return 1;
}

// remove_territory - 自某幫的 territory 名單釋出一塊領地。
// 回傳 1 表已釋出（或本就未持有），0 表參數錯誤 / 幫派不存在。
int
remove_territory(string name, string area)
{
    if( !stringp(name) || !stringp(area) || undefinedp(clans[name]) ) return 0;
    if( arrayp(clans[name]["territory"]) )
        clans[name]["territory"] -= ({ area });
    log_event(name, "放棄了「" + area + "」的勢力範圍。");
    save();
    return 1;
}

// query_territory - 回傳某幫所有領地的陣列（不存在回傳空陣列）。
string *
query_territory(string name)
{
    if( !stringp(name) || undefinedp(clans[name]) ) return ({ });
    if( !arrayp(clans[name]["territory"]) ) return ({ });
    return copy(clans[name]["territory"]);
}

// query_territory_owner - 回傳某塊領地目前的占據幫派名（無人占據回傳 0）。
// 供房間 / gate 反查「我腳下這塊地是誰的」。
string
query_territory_owner(string area)
{
    string *names;
    int i;

    if( !stringp(area) ) return 0;
    names = keys(clans);
    for( i = 0; i < sizeof(names); i++ )
        if( arrayp(clans[names[i]]["territory"])
        && member_array(area, clans[names[i]]["territory"]) != -1 )
            return names[i];
    return 0;
}

// tally_war_kill - 幫戰戰功計分。當交戰中的 killer_clan 成員殺死 victim_clan
// 成員時呼叫，於 killer_clan 累加一筆 war_score 並記入雙方幫派事件紀錄。
// 回傳 killer_clan 對 victim_clan 的累計戰功，參數錯誤 / 非交戰回傳 -1。
int
tally_war_kill(string killer_clan, string victim_clan)
{
    if( !stringp(killer_clan) || !stringp(victim_clan) ) return -1;
    if( undefinedp(clans[killer_clan]) || undefinedp(clans[victim_clan]) )
        return -1;
    // 僅在「確實交戰」時計分，避免被拿來灌水非戰時擊殺。
    if( !query_war(killer_clan, victim_clan) ) return -1;
    if( !mapp(clans[killer_clan]["war_score"]) )
        clans[killer_clan]["war_score"] = ([ ]);
    clans[killer_clan]["war_score"][victim_clan] =
        (intp(clans[killer_clan]["war_score"][victim_clan])
            ? clans[killer_clan]["war_score"][victim_clan] : 0) + 1;
    log_event(killer_clan, "幫戰中又下一城，對【" + victim_clan
        + "】的戰功累計 " + clans[killer_clan]["war_score"][victim_clan] + " 筆。");
    log_event(victim_clan, "幫戰中折損一名幫眾於【" + killer_clan + "】之手。");
    save();
    return clans[killer_clan]["war_score"][victim_clan];
}

// query_war_score - 回傳 killer_clan 對 victim_clan 的累計幫戰戰功。
int
query_war_score(string killer_clan, string victim_clan)
{
    if( !stringp(killer_clan) || !stringp(victim_clan) ) return 0;
    if( undefinedp(clans[killer_clan]) ) return 0;
    if( !mapp(clans[killer_clan]["war_score"]) ) return 0;
    if( !intp(clans[killer_clan]["war_score"][victim_clan]) ) return 0;
    return clans[killer_clan]["war_score"][victim_clan];
}

// list_clans - 回傳一段供列表顯示用的人類可讀字串（含成員數、幫主、創立時間）。
string
list_clans()
{
    string result, *names, name, leader;
    mapping c;
    int i, member_count;

    names = keys(clans);
    if( !sizeof(names) )
        return "目前尚無任何幫派成立。\n";

    result = "";
    for( i = 0; i < sizeof(names); i++ ) {
        int n_war, n_ally, n_terr;
        name = names[i];
        c = clans[name];
        leader = stringp(c["leader"]) ? capitalize(c["leader"]) : "（不詳）";
        member_count = mapp(c["members"]) ? sizeof(c["members"]) : 0;
        n_war  = arrayp(c["wars"])      ? sizeof(c["wars"])      : 0;
        n_ally = arrayp(c["allies"])    ? sizeof(c["allies"])    : 0;
        n_terr = arrayp(c["territory"]) ? sizeof(c["territory"]) : 0;
        result += sprintf("%-20s 幫主: %-12s 成員: %-3d 創立: %s",
            name, leader, member_count,
            c["created"] ? ctime(c["created"]) : "（不詳）");
        if( n_war || n_ally || n_terr )
            result += sprintf("    〔交戰 %d  結盟 %d  領地 %d〕\n",
                n_war, n_ally, n_terr);
        else
            result += "\n";
    }
    return result;
}

// vim: set ts=4 sw=4 syntax=lpc
