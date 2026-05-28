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

    set("karma", 5);        // karma cost to select woochan when reincarnate
    set("civilized", 1);

    set("commoner_score_base", 100);    // score base for gaining level

    DAEMON_D->register_race_daemon("woochan");
}


void setup(object ob)
{
    ::setup(ob);

    ob->set_default_object(__FILE__);

    if( !ob->query_weight() )
        ob->set_weight(BASE_WEIGHT + ((int)ob->query_attr("str", 1) - 13 ) * 5000);

    // 被動加成：防+5 守勢+25 不需食物
    ob->add_temp("apply/defense", 5);
    ob->add_temp("apply/wittiness", 25);

    // TODO: passive ability 不需食物
    // TODO: active ability 消水氣回狀態
    // TODO: equipment 無腸寶珠
}

void initialize(object ob)
{
    ::initialize(ob);

    // 屬性上限 str/cor/int/spi/cps/dex/con/wis = 15/15/20/20/18/20/15/22
    ob->init_attribute(([
        "str": 10 + random(6),
        "cor": 10 + random(6),
        "int": 15 + random(6),
        "spi": 15 + random(6),
        "cps": 13 + random(6),
        "dex": 15 + random(6),
        "con": 10 + random(6),
        "wis": 17 + random(6)
    ]));

    ob->init_statistic(([
        "gin": 30,
        "kee": 20,
        "sen": 60,
    ]));

    if( !ob->query("age") )
        if( (string)ob->query("gender")=="female" )
            ob->set("age", 13);
        else
            ob->set("age", 14);

    ob->set_default_object(__FILE__);
}

// vim: set ts=4 sw=4 syntax=lpc
