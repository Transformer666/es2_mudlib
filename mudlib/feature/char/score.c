#include <ansi.h>
#include <dbase.h>
#include <login.h>

string query_class() { return query("class"); }
string query_race() { return query("race"); }
int query_level() {    return query("level"); }

void set_class(string new_class)
{
    int lvl;

    set("class", new_class);
    if( query_level() && query_race() ) {
	delete("target_score");
	RACE_D(query_race())->initialize(this_object());
	CLASS_D(new_class)->initialize(this_object());
    }
}

void set_race(string new_race)
{
    int lvl;

    set("race", new_race);
    if( query_level() && query_class() ) {
	delete("target_score");
	RACE_D(new_race)->initialize(this_object());
	CLASS_D(query_class())->initialize(this_object());;
    }
}

void set_level(int lvl)
{
    string s;

    if( lvl < 1 ) error("character level must be at least 1.\n");
    if( lvl > 999 ) error("character level must less than 999.\n");
    set("level", lvl);
    if( query_race() && query_class() ) {
	delete("target_score");
	RACE_D(query_race())->initialize(this_object());
	CLASS_D(query_class())->initialize(this_object());
    }
}

int query_score(string course)
{
    return query("score/" + course);
}

static mapping score_gain = ([]);
mapping query_score_gain() { return score_gain; }
void reset_score_gain() { score_gain = ([]); }

#define LEVEL_SCORE_BASE 100    // 升級門檻基數（沿用 humanoid commoner_score_base）

// query_max_level()
//
// 各職業/種族的等級上限（依 docs/02-03-升級與天賦.md）。預設 60，較高者列出。
// 初版數值，完整 per-(race,class) 表日後可下放各 class daemon 再細調。
int query_max_level()
{
    string r = query_race();
    string c = query_class();

    if( r == "avatar" ) return 70;          // 人類族（萬一隱藏種族）全職 70

    switch(c) {
    case "soldier":                          // 軍人：刑天/阿修羅 70
	if( r=="headless" || r=="ashura" ) return 70;
	return 65;
    case "fighter":                          // 武者：阿修羅 70、刑天/夜叉 65
	if( r=="ashura" ) return 70;
	if( r=="headless" || r=="yaksa" ) return 65;
	return 60;
    case "thief":                            // 小偷：夜叉 70
	if( r=="yaksa" ) return 70;
	return 65;
    case "scholar":                          // 書生：人類 70
	if( r=="human" ) return 70;
	return 65;
    case "bonze":     return 65;             // 和尚
    case "taoist":    return 65;             // 道士
    case "alchemist": return 60;             // 方士
    default:          return 60;             // commoner 等
    }
}

// set_level_target()
//
// 依目前等級設定下一級所需的「江湖歷練(survive)」門檻；survive 為累積值，
// 門檻 = base × level²（隨級遞增）。已達等級上限則清除 target_score（不再升級）。
void set_level_target()
{
    int lvl = query_level();

    if( lvl < 1 ) lvl = 1;
    if( lvl >= query_max_level() ) {
	delete("target_score");
	return;
    }
    set("target_score/survive", LEVEL_SCORE_BASE * lvl * lvl);
}

varargs void
gain_score(string course, int xp)
{
    mapping sc, targ_sc;
    string s, save_file;
    int v;

    add("score/" + course, xp);
    if( undefinedp(score_gain[course]) ) score_gain[course] = xp;
    else score_gain[course] += xp;

    // 升級門檻 lazy-init（依 docs/02-03 重建升級系統）：原碼從未呼叫 set_target_score，
    // target_score 恆空 → 升級永不觸發。此處為未達上限的角色補上「江湖歷練」門檻。
    if( query_level() < query_max_level() && !query("target_score/survive") )
	set_level_target();

    // Check if we can raise a level.
    sc = query("score");
    targ_sc = query("target_score");
    if( !mapp(sc) || !mapp(targ_sc) ) return;

    foreach(s, v in targ_sc)
	if( sc[s] < v ) return;

    // 已達門檻：若已到等級上限則清門檻、不再升級。
    if( query_level() >= query_max_level() ) {
	delete("target_score");
	return;
    }

    receive( HIY "你的等級提昇了﹗\n" NOR );
    RACE_D(query_race())->advance_level(this_object());
    CLASS_D(query_class())->advance_level(this_object());
    delete("praise_done");
    add("level", 1);
    set_level_target();             // 設定下一級門檻（達上限則清除）

    seteuid(getuid());
// 系統強制在玩家升級時做save及backup -Dragoon
#ifdef SAVE_USER
    this_object()->save();
    save_file = this_object()->query_save_file();
    cp(save_file, save_file+".backup");
#endif
    receive("檔案儲存及備份完畢。\n");
}

int query_target_score(string course)
{
    return query("target_score/" + course);
}

void set_target_score(string course, int xp)
{
    if( !query("score/" + course) ) set("score/" + course, 0);
    if( xp < (int)query("target_score/" + course) ) return;
    set("target_score/" + course, xp);
}


