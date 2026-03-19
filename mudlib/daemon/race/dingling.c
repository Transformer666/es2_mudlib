// vim: syntax=lpc

#define BASE_WEIGHT 20000

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
    set("commoner_score_base", 150);
    DAEMON_D->register_race_daemon("dingling");
}

void setup(object ob)
{
    ::setup(ob);
    ob->set_default_object(__FILE__);
    if( !ob->query_weight() )
        ob->set_weight(BASE_WEIGHT + ((int)ob->query_attr("str", 1) - 12 ) * 5000);
    ob->add_temp("apply/armor", 2);
    ob->add_temp("apply/move", 50);
    ob->add_temp("apply/damage", 10);
}

void initialize(object ob)
{
    ::initialize(ob);
    ob->init_attribute(([
        "str": 12 + random(4),
        "int": 10 + random(4),
        "wis": 8 + random(4),
        "dex": 16 + random(6),
        "con": 10 + random(4),
        "spi": 6 + random(4),
        "cor": 10 + random(4),
        "cps": 8 + random(4),
    ]));
    ob->init_statistic(([
        "gin": 70,
        "kee": 40,
        "sen": 20,
    ]));
    if( !ob->query("age") )
        if( (string)ob->query("gender")=="female" )
            ob->set("age", 5);
        else
            ob->set("age", 6);
    ob->set_default_object(__FILE__);
}
