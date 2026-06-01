// vim: syntax=lpc

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

    set("karma", 25);       // karma cost to select rainnar when reincarnate
    set("civilized", 1);

    set("commoner_score_base", 100);    // score base for gaining level

    DAEMON_D->register_race_daemon("rainnar");
}


void setup(object ob)
{
    ::setup(ob);

    ob->set_default_object(__FILE__);

    if( !ob->query_weight() )
        ob->set_weight(BASE_WEIGHT + ((int)ob->query_attr("str", 1) - 13 ) * 5000);

    // 被動加成：防+20 四元素+10
    ob->add_temp("apply/defense", 20);

    // 四元素防禦 +10：四元素中只有「火」有確認會被引擎讀取的 apply key。
    //   apply/armor_vs_fire 已由 chinese.o 字典 (=火焰傷害防禦力)、yenhold.c:38、
    //   devour.c:170 證實為真實鍵，故此處先實作火元素那一面。
    ob->add_temp("apply/armor_vs_fire", 10);

    // TODO: passive ability 其餘三元素 (冰/風/雷) 防禦 +10。
    //   armor_vs_ice / armor_vs_wind / armor_vs_thunder 等鍵未在字典或任何
    //   feature/std 程式碼中出現，無法確認引擎會讀取，故不臆造；待元素傷害系統
    //   一般化後補上對應 apply key。
    // active ability 餵 5 條小蛇：見 /cmds/std/feedsnake.c（中文別名 餵蛇/馴蛇），
    //   每條小蛇 new /obj/race/rainnar_snake 移入玩家並 add_temp apply/armor+defense，
    //   上限 5 條（指令自我把關，race daemon 不替玩家 add_action，見 content-race-active.md）。
    // TODO: equipment 雨師妾袍
}

void initialize(object ob)
{
    ::initialize(ob);

    // 屬性上限 str/cor/int/spi/cps/dex/con/wis = 9/9/22/24/20/13/13/28
    ob->init_attribute(([
        "str": 4  + random(6),
        "cor": 4  + random(6),
        "int": 17 + random(6),
        "spi": 19 + random(6),
        "cps": 15 + random(6),
        "dex": 8  + random(6),
        "con": 8  + random(6),
        "wis": 23 + random(6)
    ]));

    ob->init_statistic(([
        "gin": 40,
        "kee": 30,
        "sen": 70,
    ]));

    if( !ob->query("age") )
        if( (string)ob->query("gender")=="female" )
            ob->set("age", 13);
        else
            ob->set("age", 14);

    ob->set_default_object(__FILE__);
}

// vim: set ts=4 sw=4 syntax=lpc
