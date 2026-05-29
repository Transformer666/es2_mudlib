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

    set("karma", 10);       // karma cost to select jiaojao when reincarnate
    set("civilized", 1);

    set("commoner_score_base", 100);    // score base for gaining level

    DAEMON_D->register_race_daemon("jiaojao");
}


void setup(object ob)
{
    ::setup(ob);

    ob->set_default_object(__FILE__);

    if( !ob->query_weight() )
        ob->set_weight(BASE_WEIGHT + ((int)ob->query_attr("str", 1) - 13 ) * 5000);

    // 被動加成：防能+15 警覺+100
    ob->add_temp("apply/defense", 15);
    ob->add_temp("apply/awarness", 100);

    // 主動技能 遁 (逃逸躲藏)：見 /cmds/std/vanish.c（中文別名 /cmds/std/遁.c）。
    // 指令以 query_race()=="jiaojao" 自鎖；daemon 不能替玩家 add_action
    // （setup 在 daemon context 跑），故此處只留指引，不掛 action。
    //   見 memory/patterns/content-race-active.md。
    // TODO: equipment 焦僥靴
}

void initialize(object ob)
{
    ::initialize(ob);

    // 屬性上限 str/cor/int/spi/cps/dex/con/wis = 14/13/19/19/19/24/16/18
    ob->init_attribute(([
        "str": 9  + random(6),
        "cor": 8  + random(6),
        "int": 14 + random(6),
        "spi": 14 + random(6),
        "cps": 14 + random(6),
        "dex": 19 + random(6),
        "con": 11 + random(6),
        "wis": 13 + random(6)
    ]));

    ob->init_statistic(([
        "gin": 40,
        "kee": 25,
        "sen": 25,
    ]));

    if( !ob->query("age") )
        if( (string)ob->query("gender")=="female" )
            ob->set("age", 13);
        else
            ob->set("age", 14);

    ob->set_default_object(__FILE__);
}

// vim: set ts=4 sw=4 syntax=lpc
