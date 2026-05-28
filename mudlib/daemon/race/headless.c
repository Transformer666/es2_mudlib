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

    set("karma", 25);       // karma cost to select headless when reincarnate
    set("civilized", 1);

    set("commoner_score_base", 100);    // score base for gaining level

    DAEMON_D->register_race_daemon("headless");
}


void setup(object ob)
{
    ::setup(ob);

    ob->set_default_object(__FILE__);

    if( !ob->query_weight() )
        ob->set_weight(BASE_WEIGHT + ((int)ob->query_attr("str", 1) - 13 ) * 5000);

    // 被動加成：攻+50 防+100 防禦力+100 移+50
    ob->add_temp("apply/attack", 50);
    ob->add_temp("apply/defense", 100);
    ob->add_temp("apply/armor", 100);
    ob->add_temp("apply/move", 50);

    // TODO: active ability 祭舞
}

void initialize(object ob)
{
    ::initialize(ob);

    // 屬性上限 str/cor/int/spi/cps/dex/con/wis = 30/20/15/10/16/24/28/18
    ob->init_attribute(([
        "str": 25 + random(6),
        "cor": 15 + random(6),
        "int": 10 + random(6),
        "spi": 5  + random(6),
        "cps": 11 + random(6),
        "dex": 19 + random(6),
        "con": 23 + random(6),
        "wis": 13 + random(6)
    ]));

    ob->init_statistic(([
        "gin": 80,
        "kee": 100,
        "sen": 30,
    ]));

    if( !ob->query("age") )
        if( (string)ob->query("gender")=="female" )
            ob->set("age", 13);
        else
            ob->set("age", 14);

    ob->set_default_object(__FILE__);
}

// vim: set ts=4 sw=4 syntax=lpc
