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

    set("karma", 10);       // karma cost to select dingling when reincarnate
    set("civilized", 1);

    set("commoner_score_base", 100);    // score base for gaining level

    DAEMON_D->register_race_daemon("dingling");

    // 字典缺「釘靈」這個詞 → 自行補上（add_translate 為幂等 set），否則建角清單會顯示英文 dingling。
    CHINESE_D->add_translate("dingling", "釘靈");
}


void setup(object ob)
{
    ::setup(ob);

    ob->set_default_object(__FILE__);

    if( !ob->query_weight() )
        ob->set_weight(BASE_WEIGHT + ((int)ob->query_attr("str", 1) - 13 ) * 5000);

    // 被動加成：移+50 傷+10
    ob->add_temp("apply/move", 50);
    ob->add_temp("apply/damage", 10);

    // TODO: active ability 踐踏
    // TODO: equipment 釘靈腿護
}

void initialize(object ob)
{
    ::initialize(ob);

    // 屬性上限 str/cor/int/spi/cps/dex/con/wis = 20/15/15/10/20/25/20/15
    ob->init_attribute(([
        "str": 15 + random(6),
        "cor": 10 + random(6),
        "int": 10 + random(6),
        "spi": 5  + random(6),
        "cps": 15 + random(6),
        "dex": 20 + random(6),
        "con": 15 + random(6),
        "wis": 10 + random(6)
    ]));

    ob->init_statistic(([
        "gin": 70,
        "kee": 40,
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
