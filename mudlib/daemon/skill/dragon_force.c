// 龍圖心經 dragon force -- 龍圖丹派醫師門下的入門內功
//
// 內功(force)是被動的「力道乘數」：戰鬥時 COMBAT_D->fight() 讀 query_skill("force")
// 與 skill_mapped("force")，藉氣(kee)與功力百分比(force_ratio)放大攻擊力道，故內功
// daemon 不需攻擊招式表。玩家以 `enable force with dragon force` 掛上本心法後，再用
// `exert dragon force` 盤膝打坐修煉（見 /std/force.c 與 cmds/std/exert.c）。
//
// 修煉與 valid_enable 等共用機制一律由 FORCE(/std/force.c)基底提供；本檔只負責
// 註冊心法名、並 override cultivate_msg() 提供龍圖丹派自家的打坐氣象。

#include <ansi.h>

inherit FORCE;

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("dragon force");
    setup();
}

// 龍圖丹派弟子打坐運功時所現的內功氣象。
string cultivate_msg()
{
    return WHT "$N閉目盤膝﹐緩緩運轉龍圖心經﹐周身似有一股溫醇平和之氣循經流轉﹐"
               "默運吐納﹐溫養經脈。\n" NOR;
}

// vim: set ts=4 sw=4 syntax=lpc
