// vim: syntax=lpc

#define BASE_WEIGHT 38000

#include <ansi.h>
#include <statistic.h>
#include <race.h>

inherit HUMANOID;

private void
create()
{
    ::create();
    seteuid(getuid());
    set("karma", 3);
    set("civilized", 0);
    set("commoner_score_base", 60);
    DAEMON_D->register_race_daemon("blackteeth");
}

void setup(object ob)
{
    ::setup(ob);
    ob->set_default_object(__FILE__);
    if( !ob->query_weight() )
        ob->set_weight(BASE_WEIGHT + ((int)ob->query_attr("str", 1) - 10 ) * 5000);
    ob->add_temp("apply/armor", 3);
    ob->add_temp("apply/damage_reduction", 5);
}

void initialize(object ob)
{
    ::initialize(ob);
    ob->init_attribute(([
        "str": 10 + random(4),
        "int": 8 + random(4),
        "wis": 8 + random(4),
        "dex": 10 + random(4),
        "con": 10 + random(4),
        "spi": 6 + random(4),
        "cor": 8 + random(4),
        "cps": 8 + random(4)
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
