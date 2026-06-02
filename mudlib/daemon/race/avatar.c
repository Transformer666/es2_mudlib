// vim: syntax=lpc
//
// avatar.c -- 「人類族」種族 daemon（人類的萬分之一隱藏變體）
//
// 見 docs/01-世界觀與劇情/03-種族設定.md：
//   人類 被動「有萬分之一機率成為『人類族』」。
//   人類族（萬分之一機率）：
//     - 適合所有職業，等級上限 70
//     - 初始狀態：精/氣/神 各 30
//     - 屬性上限：全部 20
//     - 被動：防禦力 +10
//     - 主動：通過向太陽神祈禱獲得陽光的祝福，恢復大量狀態
//
// 觸發路徑（不另開創角分支，沿用既有彩蛋）：
//   創角時 logind.c 先 set_race("human")，待 set_level(1) 時 human.c 的
//   initialize() 才被呼叫；其中 random(10000)==9999 命中即 ob->set_race("avatar")，
//   此時 level/class 皆已就緒，score.c::set_race 便鏈式呼叫 RACE_D("avatar")
//   ->initialize(ob)（本檔），完成屬性與三維的初始化。RACE_D("avatar") 透過
//   daemond.c::query_daemon 於首次使用時 load_object("/daemon/race/avatar")
//   自動載入，無須 preload。
//
// 等級上限 70 由 feature/char/score.c::query_max_level() 對 race=="avatar"
// 統一回傳，本檔不重複處理。

#define BASE_WEIGHT 40000

#include <ansi.h>
#include <statistic.h>
#include <race.h>

inherit HUMANOID;

private void
create()
{
    ::create();

    seteuid(getuid());

    // 業力同人類（5）。人類族並非可投胎選擇的種族──reincarnate.c 的
    // user_race 清單不含 avatar，僅能由人類創角時的萬一機率誕生。
    set("karma", 5);
    set("civilized", 1);    // 人類族屬文明人形種族

    set("commoner_score_base", 100);    // 升級門檻基數，同人類

    DAEMON_D->register_race_daemon("avatar");
}


void setup(object ob)
{
    ::setup(ob);

    ob->set_default_object(__FILE__);

    if( !ob->query_weight() )
        ob->set_weight(BASE_WEIGHT + ((int)ob->query_attr("str", 1) - 13 ) * 5000);

    // 被動加成：防禦力 +10（同人類；setup() 每次登入皆會重設）。
    ob->add_temp("apply/armor", 10);

    // 主動技能「太陽神祈禱」：指令實作於 /cmds/std/sunpray.c（中文別名
    // 太陽神祈禱.c）。該指令位於所有玩家共用的 /cmds/std/ 搜尋路徑，並在
    // 指令內以 query_race()=="avatar" 自我限制，故無須在此 add_path。
    // （race daemon 的 setup() 在 daemon context 執行，無法替玩家 add_action，
    //  見 doc/efuns/add_action 與 surge.c/spitfire.c 的同款做法。）
}

void initialize(object ob)
{
    ::initialize(ob);

    // 屬性上限全部 20（人類族「萬能」之處：八維皆頂規 20）。
    ob->init_attribute(([
        "str": 20,
        "cor": 20,
        "int": 20,
        "spi": 20,
        "cps": 20,
        "dex": 20,
        "con": 20,
        "wis": 20
    ]));

    // 初始狀態：精(gin)/氣(kee)/神(sen) 各 30。
    ob->init_statistic(([
        "gin": 30,
        "kee": 30,
        "sen": 30,
    ]));

    if( !ob->query("age") )
        if( (string)ob->query("gender")=="female" )
            ob->set("age", 13);
        else
            ob->set("age", 14);

    ob->set_default_object(__FILE__);
}

// vim: set ts=4 sw=4 syntax=lpc
