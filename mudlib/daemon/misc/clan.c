

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
//       "territory": ({}),                 // 勢力範圍（Phase 2+）
//       "allies"   : ({}),                 // 結盟幫派（Phase 2+）
//       "wars"     : ({}),                 // 交戰幫派（Phase 2+）
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
        name = names[i];
        c = clans[name];
        leader = stringp(c["leader"]) ? capitalize(c["leader"]) : "（不詳）";
        member_count = mapp(c["members"]) ? sizeof(c["members"]) : 0;
        result += sprintf("%-20s 幫主: %-12s 成員: %-3d 創立: %s\n",
            name, leader, member_count,
            c["created"] ? ctime(c["created"]) : "（不詳）");
    }
    return result;
}

// vim: set ts=4 sw=4 syntax=lpc
