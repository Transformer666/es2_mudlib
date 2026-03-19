// vim: syntax=lpc

#define BASE_WEIGHT 55000

#include <ansi.h>
#include <statistic.h>
#include <race.h>

inherit HUMANOID;

private void
create()
{
    ::create();
    seteuid(getuid());
    set("karma", 25);
    set("civilized", 0);
    set("commoner_score_base", 150);
    DAEMON_D->register_race_daemon("xingtian");
}

void setup(object ob)
{
    ::setup(ob);
    ob->set_default_object(__FILE__);
    if( !ob->query_weight() )
        ob->set_weight(BASE_WEIGHT + ((int)ob->query_attr("str", 1) - 15 ) * 5000);
    ob->add_temp("apply/armor", 5);
    ob->add_temp("apply/attack", 50);
}

void initialize(object ob)
{
    ::initialize(ob);
    ob->init_attribute(([
        "str": 15 + random(8),
        "int": 8 + random(4),
        "wis": 8 + random(4),
        "dex": 12 + random(4),
        "con": 18 + random(8),
        "spi": 6 + random(4),
        "cor": 16 + random(6),
        "cps": 10 + random(4),
    ]));
    ob->init_statistic(([
        "gin": 80,
        "kee": 100,
        "sen": 30,
    ]));
    if( !ob->query("age") )
        if( (string)ob->query("gender")=="female" )
            ob->set("age", 50);
        else
            ob->set("age", 60);
    ob->set_default_object(__FILE__);
}
