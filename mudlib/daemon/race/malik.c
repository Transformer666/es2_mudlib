// vim: syntax=lpc

#define BASE_WEIGHT 42000

#include <ansi.h>
#include <statistic.h>
#include <race.h>

inherit HUMANOID;

private void
create()
{
    ::create();
    seteuid(getuid());
    set("karma", 30);
    set("civilized", 0);
    set("commoner_score_base", 150);
    DAEMON_D->register_race_daemon("malik");
}

void setup(object ob)
{
    ::setup(ob);
    ob->set_default_object(__FILE__);
    if( !ob->query_weight() )
        ob->set_weight(BASE_WEIGHT + ((int)ob->query_attr("str", 1) - 12 ) * 5000);
    ob->add_temp("apply/armor", 3);
    ob->add_temp("apply/defense", 50);
}

void initialize(object ob)
{
    ::initialize(ob);
    ob->init_attribute(([
        "str": 12 + random(4),
        "int": 14 + random(6),
        "wis": 16 + random(6),
        "dex": 12 + random(4),
        "con": 10 + random(4),
        "spi": 18 + random(6),
        "cor": 10 + random(4),
        "cps": 14 + random(4),
    ]));
    ob->init_statistic(([
        "gin": 70,
        "kee": 40,
        "sen": 100,
    ]));
    if( !ob->query("age") )
        if( (string)ob->query("gender")=="female" )
            ob->set("age", 20);
        else
            ob->set("age", 25);
    ob->set_default_object(__FILE__);
}
