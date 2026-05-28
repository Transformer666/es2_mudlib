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

    set("karma", 30);       // karma cost to select ashura when reincarnate
    set("civilized", 1);

    set("commoner_score_base", 100);    // score base for gaining level

    DAEMON_D->register_race_daemon("ashura");
}


void setup(object ob)
{
    ::setup(ob);

    ob->set_default_object(__FILE__);

    if( !ob->query_weight() )
        ob->set_weight(BASE_WEIGHT + ((int)ob->query_attr("str", 1) - 13 ) * 5000);

    // 被動加成：攻+30 攻勢+30 陰陽眼
    ob->add_temp("apply/attack", 30);
    ob->add_temp("apply/intimidate", 30);

    // TODO: passive ability 陰陽眼
    // TODO: active ability 混亂 / 吞屍
    // TODO: equipment 修羅之面
}

void initialize(object ob)
{
    ::initialize(ob);

    // 屬性上限 str/cor/int/spi/cps/dex/con/wis = 25/40/15/25/10/20/20/20
    ob->init_attribute(([
        "str": 20 + random(6),
        "cor": 35 + random(6),
        "int": 10 + random(6),
        "spi": 20 + random(6),
        "cps": 5  + random(6),
        "dex": 15 + random(6),
        "con": 15 + random(6),
        "wis": 15 + random(6)
    ]));

    ob->init_statistic(([
        "gin": 80,
        "kee": 80,
        "sen": 80,
    ]));

    if( !ob->query("age") )
        if( (string)ob->query("gender")=="female" )
            ob->set("age", 13);
        else
            ob->set("age", 14);

    ob->set_default_object(__FILE__);
}

// vim: set ts=4 sw=4 syntax=lpc
