#include <ansi.h>
#include <origin.h>
#include <user.h>
#include <action.h>

inherit CHARACTER;
inherit F_AUTOLOAD;
inherit F_EDIT;
inherit F_SAVE;
inherit F_MORE;
inherit F_FLAG;

// private prototypes

private void user_dump(int type);
private void accrue_karma();

// variables

static object my_link;
private int last_age_set;

// implementations

private void create() {
  object ob;

  // Let LOGIN_D export proper uid to us.
  seteuid(0);

  if (clonep(this_object()))
    set_name("無名氏", "noname");
}

private int move_or_destruct (object dest) {
  if (dest)
    move(dest);
  else {
    message ("system", "一陣時空的扭曲將你傳送到另一個地方....\n", this_object());
    set_temp ("last_location", base_name(environment()));
    move (VOID_OB);
  }
}

private void reset() {
  // To prevent the master copy of user object error out by security
  // violation.
  if (!userp (this_object()))
    return;

  gain_score("survive", (int)query("age") / 2 + 1 );
}

int set_link(object link) {
    if (origin()==ORIGIN_CALL_OTHER 
    && (geteuid(previous_object()) != ROOT_UID)
    && (geteuid(previous_object()) != geteuid(this_object())))
        return 0;
    my_link = link;
    return 1;
}

object link() {
    return my_link;
}

private void set_terminal_type(string term_type) {
    set_temp("terminal_type", term_type);
    message("system", "終端機型態設定為 " + term_type + "。\n", this_object());
}

// This is used by F_SAVE to determine the filename to save our data.
string query_save_file() {
    return user_data (getuid());
}

int save() {
    int res;

    if (objectp(my_link))
        my_link->save();
    save_autoload();
    res = ::save();
    clean_up_autoload();        // To save memory
    return res;
}

// 在生業力累積 (decision E)。業力是「投胎(轉種族)」的中性成本貨幣，原本只能
// 靠「真死轉世」在 logind.c::reincarnate() 賺取，導致高業力種族 (夜叉/巫首/
// 阿修羅，25~35 點) 幾乎無法達成。這裡讓「活著上線」也能慢慢累積業力，使長期
// 上線的玩家能逐步達標 ── 完全比照 docs/02-遊戲系統與機制/04-業力與聲望.md：
//
//   業力 = 人物等級；上限不超過「上線時數總天數 × 2」。
//
// 設計（中性，不涉善惡/殺業/紅人，亦不更動任何投胎門檻）：
//   * 業力存在 link (連線) 物件上，比照 logind.c / reincarnate.c 以
//     link->query("karma") 讀、link->add("karma", n) 寫。body 與 link 的 euid
//     同為玩家 uid，故通過 login.c::add() 的 USER_PROTECT (比照 tune.c 以
//     me->link()->set(...) 寫 link 的慣例)。
//   * 「上線總天數」直接取 link 的累積 time_aged ── 那是角色自創角起的「真實
//     上線秒數」累計值 (login.c::update_age() 只 ::add 不歸零)，正是
//     logind.c::reincarnate() 計 max_karma_gain 用的同一來源。
//       online_days = link_time_aged / 86400
//   * 上限 cap = min( query_level(), online_days * 2 )，與 docs 完全一致：
//     上線天數夠多時業力可達「等於等級」，但永不超過「天數×2」。
//   * 每次只補「差額」並夾住上限 (絕不超過 cap)，故反覆呼叫亦安全、不會 overshoot。
//
// KARMA_PER_DAY：每「上線一天」朝 cap 推進的點數 (純速率參數，可由設計者調整；
//   夾在 cap 內，故調大只是更快達標，永不破上限)。
#define KARMA_PER_DAY   1

private void accrue_karma() {
    int cap, cur, online_days, gain;

    if (!objectp(my_link))
        return;

    // 上線總天數取自 link 的累積 time_aged (真實上線秒數，永不歸零)。
    online_days = (int)my_link->query("time_aged") / 86400;

    // 上限完全比照 docs：min(等級, 上線天數 × 2)。
    cap = query_level();
    if (online_days * 2 < cap)
        cap = online_days * 2;

    cur = (int)my_link->query("karma");
    if (cur >= cap)
        return;                     // 已達(或超過)上限，不再累積，亦不回收。

    // 每天朝 cap 推進 KARMA_PER_DAY 點，但夾住上限、只補差額，絕不 overshoot。
    gain = KARMA_PER_DAY;
    if (cur + gain > cap)
        gain = cap - cur;
    if (gain <= 0)
        return;

    my_link->add("karma", gain);
}

// This function updates player's age, called by heart_beat()
private void heart_beat() {
    ::heart_beat();
    if (!this_object())
        return;

    // Make us older. Note this should not rely on fixed period between
    // each call to heart_beat bcz heart_beat could be stoped for various
    // reason.                                           - Annihilator

    if (!last_age_set)
        last_age_set = time();
    add ("time_aged", time() - last_age_set);
    last_age_set = time();
    if ((int)query("time_aged") >= 86400) {
        add("age", 1);
        delete("time_aged");
        // 在生業力：每「上線滿一天」朝 docs 上限推進一次 (先刷新 link 的
        // 累積上線秒數，再依 min(等級, 天數×2) 夾住補差額)。
        if (objectp(my_link))
            my_link->update_age();
        accrue_karma();
    }

    if (objectp(my_link))
        my_link->update_age();

    if (interactive(this_object()) && query_idle(this_object()) >= IDLE_TIMEOUT)
        user_dump(DUMP_IDLE);
}

void setup() {
    if (! query("id"))
        set ("id", getuid());
    ::setup();

    /* 以下是讓 F_STATISTIC 檢查這個使用者是否在上次 quit 之前已經死亡，但
     * 還沒有被 heart_beat 抓到( 俗稱 quit 大法 )
     */
    damage_stat("gin", 0);
    damage_stat("kee", 0);
    damage_stat("sen", 0);
    damage_stat("HP", 0);

    restore_autoload();
    restore_condition();
}

private void user_dump(int type) {
  switch(type)
    {
    case DUMP_NET_DEAD:
      // change cmd: quit to quit ! -Dragoon
      cmd_quit("!");
      break;
    case DUMP_IDLE:
    default:
      // wiz don't get kicked out (Elon 10-17-95)
      if (wizardp(this_object()))
        return;
      tell_object(this_object(), CYN "你聽到一個細小的聲音說道：節能愛地球，請勿長時間掛機發呆～～\n" NOR);
      tell_object(this_object(), HIW "\n一個小小的，長著白色翅膀的生物忽然出現，抓著你的手在鍵盤上敲了 quit 命令。\n\n" NOR);
      tell_room(environment(), "一陣風吹來﹐將發呆中的" + query("name") + "化為一堆飛灰﹐消失了。\n", ({this_object()}));
      // change cmd: quit to quit ! -Dragoon
      cmd_quit("!");
      break;
    }
}

/*  net_dead()
 *
 *  當使用者斷線時，driver 會呼叫這個函數。
 */
private void net_dead() {
    set_heart_beat(0);

    if (objectp(my_link)) {
        my_link->save();
        destruct(my_link);
    }

    // Stop fighting, we'll be back soon.
    remove_all_enemy();
    if (environment())
        set_temp("last_location", base_name(environment()) );

    if( is_busy() ) interrupt(this_object(), INTR_LINKDEAD);

    if( userp(this_object()) ) {
        call_out("user_dump", NET_DEAD_TIMEOUT, DUMP_NET_DEAD);
        // tell room what happen to this player -dragoon
        tell_room(environment(), "時空一陣波動, " + query("name") +
            "瞬間由這個世界消失...\n");
        LOGIN_D->net_dead(this_object());
    } else 
        command("quit");
}

// reconnect: called by the LOGIN_D when a netdead player reconnects.
void reconnect() {
    string last_loc;

    if (geteuid(previous_object()) != ROOT_UID)
        error ("Permission denied.\n");

    set_heart_beat(1);
    remove_call_out("user_dump");
    tell_object(this_object(), "重新連線完畢。\n");
    if( stringp(last_loc = query_temp("last_location")) )
        move(last_loc);
}

static string last_cmd;
static int last_cmd_time;
static int last_cmd_count;

string process_input (string str) {
#ifdef MAX_COMMAND_PER_SECOND
    if (last_cmd_time == time()) {
        last_cmd_count++;
        if (last_cmd_count > MAX_COMMAND_PER_SECOND)
            return "";
        if (last_cmd_count == MAX_COMMAND_PER_SECOND) {
            write ("\r你下指令的速度太快了，你所控制的人物無法執行這麼多命令。\n");
            return "";
        }
    } else {
        last_cmd_time = time();
        last_cmd_count = 1;
    }
#endif	/* MAX_COMMAND_PER_SECOND */

    if (str[0..1]=="!!")
        return last_cmd + str[2..];

    if (objectp(my_link))
        return last_cmd = my_link->process_alias(str);

    return 0;
}

void lose_fight(object opponent) {
    ::lose_fight (opponent);
    tell_object (this_object(), "這一招你無法招架，輸掉了這場比試。\n");
}

void win_fight(object opponent) {
    tell_object(this_object(), opponent->name() + "招架不住，你贏了這場比試。\n");
    // add to test -Dragoon
    remove_all_enemy();
}

/***********************************************************************
                            USER DATA PROTECTIONS
 ***********************************************************************/
 
nomask mixed set (string prop, mixed data) {
    USER_PROTECT();
    return ::set(prop, data);
}

nomask mixed add (string prop, mixed data) {
    USER_PROTECT();
    return ::add(prop, data);
}

nomask void delete(string prop) {
    USER_PROTECT();
    ::delete(prop);
}

nomask varargs mixed query(string prop, int raw) {
    mixed v = ::query(prop, raw);
    if (mapp(v) || arrayp(v))
        USER_PROTECT();
    return v;
}

nomask void set_skill (string skill, int amount) {
    USER_PROTECT();
    ::set_skill (skill, amount);
}

nomask void advance_skill(string skill, int amount) {
    USER_PROTECT();
    ::advance_skill(skill, amount);
}

nomask void set_learn(string skill, int lrn) {
    USER_PROTECT();    
    ::set_learn(skill, lrn);
}

nomask void improve_skill(string skill, int amount) {
    USER_PROTECT();
    ::improve_skill(skill, amount);
}

nomask int set_attr(string what, int value) {
    USER_PROTECT();
    return ::set_attr(what, value);
}

nomask int set_stat_maximum(string what, int val) {
    USER_PROTECT();
    return ::set_stat_maximum(what, val);
}

// vim: set ts=4 sw=4 syntax=lpc
