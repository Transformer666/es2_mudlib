// reputation.c -- 顯示玩家的多軸聲望與業力 (唯讀)。
//
// 資料來源 (皆已驗證於 mudlib 現有程式):
//   * 聲望 / 各評價軸: feature/char/score.c 的 query_score(course)，
//     底層為 query("score/" + course)；整份 mapping 為 query("score")。
//     各 NPC/任務以 gain_score("survive"/"martial fame"/"emprise"...) 累積，
//     adm/daemons/chard.c 在殺人時調整 reputation/martial fame/negative fame。
//   * 業力 (karma): 存在 link (登入連線) 物件上，由 logind.c set/add，
//     讀法見 cmds/usr/score.c： me->link()->query("karma")。
//   * 中文名稱: to_chinese("score of " + course)，字典 data/chinese.o 內已
//     收錄 score of martial fame=武林聲望、personal fame=個人聲望、
//     negative fame=黑道聲望、explorer fame=旅行見聞、emprise=俠義之舉、
//     kills=殺業、mortal sin=重大惡行、survive=江湖歷練 等。
//     字典查無的 key 會原樣回傳 (見 adm/daemons/chinesed.c 的 chinese())。
//
// 本指令完全唯讀，不更動任何狀態。中文別名見 cmds/usr/聲望.c。

#include <ansi.h>

#define REP_COLUMN 2

inherit F_CLEAN_UP;

// 要強調顯示的「聲望」類軸 (有值才印)。其餘 score 軸 (戰技、學養等) 歸到
// 「其他江湖評價」一欄，避免和 score 指令完全重複又能讓玩家一覽聲望面。
string *fame_axes = ({
    "reputation",       // 聲望
    "martial fame",     // 武林聲望
    "common fame",      // (字典亦為武林聲望)
    "personal fame",    // 個人聲望
    "negative fame",    // 黑道聲望
    "explorer fame",    // 旅行見聞
    "emprise",          // 俠義之舉
    "literary fame",    // 文學造詣
    "survive",          // 江湖歷練 (全職業，登入/戰鬥/採買皆會累積)
});

// 業力相關 / 惡行軸，獨立成一區顯示。
string *karma_axes = ({
    "mortal sin",       // 重大惡行
    "kills",            // 殺業
});

private void create() {
    seteuid(getuid());
}

private string fame_color(string course, int xp) {
    // 正派聲望給暖色，黑道/惡行給紅色，殺業給暗紅。
    if( course == "negative fame" || course == "mortal sin" )
        return (xp > 0) ? HIR : NOR;
    if( course == "kills" )
        return (xp > 0) ? RED : NOR;
    return (xp > 0) ? HIY : NOR;
}

// 計算一組軸中有非零值的數目。
private int count_axes(mapping score, string *axes) {
    string course;
    int n;

    n = 0;
    foreach( course in axes )
        if( !undefinedp(score[course]) && score[course] != 0 )
            n++;
    return n;
}

// 印出一組軸 (有值或負值才印)，依序排成兩欄，回傳格式化字串。
private string format_axes(mapping score, string *axes) {
    string course, line;
    int xp, n;

    line = "";
    n = 0;
    foreach( course in axes ) {
        if( undefinedp(score[course]) ) continue;
        xp = score[course];
        if( xp == 0 ) continue;                 // 跳過零值軸
        line += sprintf("   %-12s %s%8d" NOR,
            to_chinese("score of " + course),
            fame_color(course, xp),
            xp);
        if( (n % REP_COLUMN) == REP_COLUMN - 1 )
            line += "\n";
        n++;
    }
    if( n % REP_COLUMN )
        line += "\n";
    return line;
}

int main(object me, string arg) {
    object ob;
    mapping score;
    string line, who;
    int karma, shown;

    if( !arg || arg == "" )
        ob = me;
    else {
        if( !wizardp(me) )
            return notify_fail("只有巫師能察看別人的聲望。\n");
        ob = present(arg, environment(me));
        if( !ob ) ob = find_player(arg);
        if( !ob ) ob = find_living(arg);
        if( !ob )
            return notify_fail("你要察看誰的聲望﹖\n");
    }

    who = (ob == me) ? "你" : ob->name();

    // 業力存在 link 物件 (登入連線) 上；無連線者 (如 NPC/離線) 視為 0。
    karma = ob->link() ? ob->link()->query("karma") : 0;

    line = sprintf(HIW "【 %s 】" NOR "%s 的江湖聲望\n\n", ob->rank(), ob->short(1));
    line += sprintf(" 業力﹕" HIM "%d" NOR " 點\n\n", karma);

    score = ob->query("score");
    if( !mapp(score) ) score = ([]);

    shown = count_axes(score, fame_axes) + count_axes(score, karma_axes);

    line += HIW " ◆ 聲望﹕\n" NOR;
    line += format_axes(score, fame_axes);

    line += HIW "\n ◆ 業力相關﹕\n" NOR;
    line += format_axes(score, karma_axes);

    if( shown == 0 )
        line += sprintf("   %s尚未在江湖上累積任何聲望。\n", who);

    line += "\n" CYN " (詳細評價請用 score；技能請用 skills。)\n" NOR;

    write(line);
    return 1;
}

int help(object me) {
    write(@HELP
指令格式 : reputation
           reputation <對象名稱>              (巫師專用)

這個指令顯示你(妳)在江湖上累積的多軸聲望與業力，包括武林聲望、個人聲望、
黑道聲望、旅行見聞、俠義之舉等，以及殺業與重大惡行。數值為零的項目不會顯示。

剛踏入江湖的新手通常只會看到少許業力與江湖歷練；隨著行俠、探索、完成任務，
各項聲望才會逐漸累積。中文別名為「聲望」。

其他相關指令﹕score、skills
HELP
    );
    return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
