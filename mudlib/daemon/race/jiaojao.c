// vim: syntax=lpc

#define BASE_WEIGHT 15000

#include <ansi.h>
#include <statistic.h>
#include <race.h>

inherit HUMANOID;

private void
create()
{
    ::create();
    seteuid(getuid());
    set("karma", 10);
    set("civilized", 0);
    set("commoner_score_base", 80);
    DAEMON_D->register_race_daemon("jiaojao");
}

void setup(object ob)
{
    ::setup(ob);
    ob->set_default_object(__FILE__);
    if( !ob->query_weight() )
        ob->set_weight(BASE_WEIGHT + ((int)ob->query_attr("str", 1) - 8 ) * 5000);
    ob->add_temp("apply/armor", 2);
    ob->add_temp("apply/defense", 15);
}

void initialize(object ob)
{
    ::initialize(ob);
    ob->init_attribute(([
        "str": 8 + random(4),
        "int": 10 + random(4),
        "wis": 10 + random(4),
        "dex": 18 + random(6),
        "con": 8 + random(4),
        "spi": 8 + random(4),
        "cor": 8 + random(4),
        "cps": 10 + random(4)
    ]));
    ob->init_statistic(([
        "gin": 40,
        "kee": 25,
        "sen": 25,
    ]));
    if( !ob->query("age") )
        if( (string)ob->query("gender")=="female" )
            ob->set("age", 10);
        else
            ob->set("age", 11);
    ob->set_default_object(__FILE__);
}
