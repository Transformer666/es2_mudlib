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

    set("karma", 35);       // karma cost to select yaksa when reincarnate
    set("civilized", 1);

    set("commoner_score_base", 100);    // score base for gaining level

    DAEMON_D->register_race_daemon("yaksa");
}


void setup(object ob)
{
    ::setup(ob);

    ob->set_default_object(__FILE__);

    if( !ob->query_weight() )
        ob->set_weight(BASE_WEIGHT + ((int)ob->query_attr("str", 1) - 13 ) * 5000);

    // 被動加成：防+50 攻+25 陰陽眼/通天眼
    ob->add_temp("apply/defense", 50);
    ob->add_temp("apply/attack", 25);

    // TODO: passive ability 陰陽眼/通天眼
    // TODO: active ability 吞鬼 devour
}

void initialize(object ob)
{
    ::initialize(ob);

    // 屬性上限 str/cor/int/spi/cps/dex/con/wis = 25/25/20/25/20/25/25/25
    ob->init_attribute(([
        "str": 20 + random(6),
        "cor": 20 + random(6),
        "int": 15 + random(6),
        "spi": 20 + random(6),
        "cps": 15 + random(6),
        "dex": 20 + random(6),
        "con": 20 + random(6),
        "wis": 20 + random(6)
    ]));

    ob->init_statistic(([
        "gin": 140,
        "kee": 70,
        "sen": 70,
    ]));

    if( !ob->query("age") )
        if( (string)ob->query("gender")=="female" )
            ob->set("age", 13);
        else
            ob->set("age", 14);

    ob->set_default_object(__FILE__);
}

// vim: set ts=4 sw=4 syntax=lpc
