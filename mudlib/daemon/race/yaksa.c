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

    // 陰陽眼：能看見鬼魂 (life_form=="ghost") 的人物。
    //   std/char.c::visible() 第 452-453 行：鬼魂對沒有 apply/vision_of_ghost
    //   的觀看者不可見；夜叉天生具備此能力。chinese.o 字典 vision_of_ghost=陰陽眼。
    ob->add_temp("apply/vision_of_ghost", 1);

    // 通天眼：能察覺隱藏 / 潛行的人物。
    //   visible() 第 448 行：pending/hidden > 觀看者 query_ability("awarness") 才隱形。
    //   query_ability("awarness") (combat.c:128-131) 會加上 query_temp("apply/awarness")。
    //   vanish/sneak 的藏匿值約 10-30；給 +60 足以洞穿一般潛行，但低於焦僥/吞鬼飽和的 +100。
    ob->add_temp("apply/awarness", 60);

    // TODO: active ability 吞鬼 devour（見 /cmds/std/devour.c，已實作）
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
