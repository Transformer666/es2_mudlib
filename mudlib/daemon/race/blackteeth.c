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

    set("karma", 3);        // karma cost to select blackteeth when reincarnate
    set("civilized", 1);

    set("commoner_score_base", 100);    // score base for gaining level

    DAEMON_D->register_race_daemon("blackteeth");
}


void setup(object ob)
{
    ::setup(ob);

    ob->set_default_object(__FILE__);

    if( !ob->query_weight() )
        ob->set_weight(BASE_WEIGHT + ((int)ob->query_attr("str", 1) - 13 ) * 5000);

    // 被動加成：防+5
    ob->add_temp("apply/defense", 5);

    // TODO: active ability 吞物回狀態 (gnaw)
}

void initialize(object ob)
{
    ::initialize(ob);

    // 屬性上限 str/cor/int/spi/cps/dex/con/wis = 25/15/15/10/15/20/20/10
    ob->init_attribute(([
        "str": 20 + random(6),
        "cor": 10 + random(6),
        "int": 10 + random(6),
        "spi": 5  + random(6),
        "cps": 10 + random(6),
        "dex": 15 + random(6),
        "con": 15 + random(6),
        "wis": 5  + random(6)
    ]));

    ob->init_statistic(([
        "gin": 35,
        "kee": 25,
        "sen": 10,
    ]));

    if( !ob->query("age") )
        if( (string)ob->query("gender")=="female" )
            ob->set("age", 13);
        else
            ob->set("age", 14);

    ob->set_default_object(__FILE__);
}

// vim: set ts=4 sw=4 syntax=lpc
