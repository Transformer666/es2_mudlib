// vim: syntax=lpc

#define BASE_WEIGHT 50000

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
    DAEMON_D->register_race_daemon("asura");
}

void setup(object ob)
{
    ::setup(ob);
    ob->set_default_object(__FILE__);
    if( !ob->query_weight() )
        ob->set_weight(BASE_WEIGHT + ((int)ob->query_attr("str", 1) - 14 ) * 5000);
    ob->add_temp("apply/armor", 4);
    ob->add_temp("apply/attack", 20);
    ob->set_temp("apply/vision_of_ghost", 1);   // 陰陽眼：可看見鬼魂
}

void initialize(object ob)
{
    ::initialize(ob);
    ob->init_attribute(([
        "str": 14 + random(6),
        "int": 14 + random(6),
        "wis": 14 + random(6),
        "dex": 14 + random(6),
        "con": 14 + random(6),
        "spi": 14 + random(6),
        "cor": 14 + random(6),
        "cps": 14 + random(6),
    ]));
    ob->init_statistic(([
        "gin": 80,
        "kee": 80,
        "sen": 80,
    ]));
    if( !ob->query("age") )
        if( (string)ob->query("gender")=="female" )
            ob->set("age", 25);
        else
            ob->set("age", 30);
    ob->set_default_object(__FILE__);
}
