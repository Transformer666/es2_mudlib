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

    set("karma", 30);       // karma cost to select malik when reincarnate
    set("civilized", 1);

    set("commoner_score_base", 100);    // score base for gaining level

    DAEMON_D->register_race_daemon("malik");
}


void setup(object ob)
{
    ::setup(ob);

    ob->set_default_object(__FILE__);

    if( !ob->query_weight() )
        ob->set_weight(BASE_WEIGHT + ((int)ob->query_attr("str", 1) - 13 ) * 5000);

    // 被動加成：防能+50 防禦力+10 通天眼
    ob->add_temp("apply/defense", 50);
    ob->add_temp("apply/armor", 10);

    // 通天眼：能察覺隱藏 / 潛行的人物。
    //   visible() (std/char.c:448)：pending/hidden > query_ability("awarness") 才隱形。
    //   query_ability("awarness") (combat.c:128-131) 會加上 query_temp("apply/awarness")。
    //   給 +60 足以洞穿一般 vanish/sneak（藏匿值約 10-30）。
    ob->add_temp("apply/awarness", 60);

    // TODO: active ability 採靈氣回神
    // TODO: equipment 巫首項鍊 spi+2
}

void initialize(object ob)
{
    ::initialize(ob);

    // 屬性上限 str/cor/int/spi/cps/dex/con/wis = 11/11/30/30/28/25/15/25
    ob->init_attribute(([
        "str": 6  + random(6),
        "cor": 6  + random(6),
        "int": 25 + random(6),
        "spi": 25 + random(6),
        "cps": 23 + random(6),
        "dex": 20 + random(6),
        "con": 10 + random(6),
        "wis": 20 + random(6)
    ]));

    ob->init_statistic(([
        "gin": 70,
        "kee": 40,
        "sen": 100,
    ]));

    if( !ob->query("age") )
        if( (string)ob->query("gender")=="female" )
            ob->set("age", 13);
        else
            ob->set("age", 14);

    ob->set_default_object(__FILE__);
}

// vim: set ts=4 sw=4 syntax=lpc
