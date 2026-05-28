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

    set("karma", 5);        // karma cost to select yenhold when reincarnate
    set("civilized", 1);

    set("commoner_score_base", 100);    // score base for gaining level

    DAEMON_D->register_race_daemon("yenhold");
}


void setup(object ob)
{
    ::setup(ob);

    ob->set_default_object(__FILE__);

    if( !ob->query_weight() )
        ob->set_weight(BASE_WEIGHT + ((int)ob->query_attr("str", 1) - 13 ) * 5000);

    // 被動加成：防+20 火防+50
    ob->add_temp("apply/defense", 20);
    ob->add_temp("apply/armor_vs_fire", 50);

    // TODO: active ability 吐火
}

void initialize(object ob)
{
    ::initialize(ob);

    // 屬性上限 str/cor/int/spi/cps/dex/con/wis = 20/14/10/12/20/14/22/15
    ob->init_attribute(([
        "str": 15 + random(6),
        "cor": 9  + random(6),
        "int": 5  + random(6),
        "spi": 7  + random(6),
        "cps": 15 + random(6),
        "dex": 9  + random(6),
        "con": 17 + random(6),
        "wis": 10 + random(6)
    ]));

    ob->init_statistic(([
        "gin": 20,
        "kee": 30,
        "sen": 20,
    ]));

    if( !ob->query("age") )
        if( (string)ob->query("gender")=="female" )
            ob->set("age", 13);
        else
            ob->set("age", 14);

    ob->set_default_object(__FILE__);
}

// vim: set ts=4 sw=4 syntax=lpc
