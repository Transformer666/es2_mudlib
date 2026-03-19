// vim: syntax=lpc

#define BASE_WEIGHT 45000

#include <ansi.h>
#include <statistic.h>
#include <race.h>

inherit HUMANOID;

private void
create()
{
    ::create();
    seteuid(getuid());
    set("karma", 35);
    set("civilized", 0);
    set("commoner_score_base", 150);
    DAEMON_D->register_race_daemon("yaksha");
}

void setup(object ob)
{
    ::setup(ob);
    ob->set_default_object(__FILE__);
    if( !ob->query_weight() )
        ob->set_weight(BASE_WEIGHT + ((int)ob->query_attr("str", 1) - 14 ) * 5000);
    ob->add_temp("apply/armor", 4);
    ob->add_temp("apply/defense", 50);
    ob->add_temp("apply/attack", 25);
}

void initialize(object ob)
{
    ::initialize(ob);
    ob->init_attribute(([
        "str": 14 + random(6),
        "int": 14 + random(6),
        "wis": 12 + random(4),
        "dex": 16 + random(6),
        "con": 13 + random(4),
        "spi": 14 + random(6),
        "cor": 14 + random(6),
        "cps": 12 + random(4),
    ]));
    ob->init_statistic(([
        "gin": 140,
        "kee": 70,
        "sen": 70,
    ]));
    if( !ob->query("age") )
        if( (string)ob->query("gender")=="female" )
            ob->set("age", 18);
        else
            ob->set("age", 20);
    ob->set_default_object(__FILE__);
}
