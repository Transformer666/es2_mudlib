// vim: syntax=lpc

#define BASE_WEIGHT 35000

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
    set("commoner_score_base", 120);
    DAEMON_D->register_race_daemon("rainnar");
}

void setup(object ob)
{
    ::setup(ob);
    ob->set_default_object(__FILE__);
    if( !ob->query_weight() )
        ob->set_weight(BASE_WEIGHT + ((int)ob->query_attr("str", 1) - 10 ) * 5000);
    ob->add_temp("apply/armor", 3);
    ob->add_temp("apply/defense", 20);
    ob->add_temp("apply/resist_fire", 10);
    ob->add_temp("apply/resist_ice", 10);
    ob->add_temp("apply/resist_lightning", 10);
    ob->add_temp("apply/resist_wind", 10);
}

void initialize(object ob)
{
    ::initialize(ob);
    ob->init_attribute(([
        "str": 10 + random(4),
        "int": 14 + random(6),
        "wis": 14 + random(6),
        "dex": 12 + random(4),
        "con": 10 + random(4),
        "spi": 16 + random(6),
        "cor": 10 + random(4),
        "cps": 14 + random(4)
    ]));
    ob->init_statistic(([
        "gin": 40,
        "kee": 30,
        "sen": 70,
    ]));
    if( !ob->query("age") )
        if( (string)ob->query("gender")=="female" )
            ob->set("age", 14);
        else
            ob->set("age", 15);
    ob->set_default_object(__FILE__);
}
