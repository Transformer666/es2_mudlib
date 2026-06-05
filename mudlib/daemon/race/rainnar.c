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

    set("karma", 25);       // karma cost to select rainnar when reincarnate
    set("civilized", 1);

    set("commoner_score_base", 100);    // score base for gaining level

    DAEMON_D->register_race_daemon("rainnar");
}


void setup(object ob)
{
    ::setup(ob);

    ob->set_default_object(__FILE__);

    if( !ob->query_weight() )
        ob->set_weight(BASE_WEIGHT + ((int)ob->query_attr("str", 1) - 13 ) * 5000);

    // 被動加成：防+20 四元素+10
    ob->add_temp("apply/defense", 20);

    // 四元素「物理向」防禦 +10(火)：apply/armor_vs_fire 由 resist_damage 讀﹐已由
    //   chinese.o 字典 (=火焰傷害防禦力)、yenhold.c:38、devour.c:170 證實為真實鍵。
    ob->add_temp("apply/armor_vs_fire", 10);

    // 四元素「法術向」防禦 +10(火/冰/風/雷)：apply/<elem>_def 為 /std/magic.c 元素引擎
    //   (magic_element_resist﹐2026-06-05 已建)折算元素魔法傷害所讀的百分比抗性鍵﹐
    //   持久 query + 暫時 query_temp 加總(鏡 query_attr)。雨師妾被動四元素防禦(docs
    //   03-種族設定.md L41「四元素防禦」)經此鍵對天師火/茅山雷/玄衣風/寒冰諸元素咒
    //   一體生效﹐補齊原 TODO 的冰/風/雷三面(以引擎鍵而非未確認的 armor_vs_* 鍵)。
    foreach( string elem in ({ "fire", "freeze", "wind", "thunder" }) )
        ob->add_temp("apply/" + elem + "_def", 10);

    // active ability 餵 5 條小蛇：見 /cmds/std/feedsnake.c（中文別名 餵蛇/馴蛇），
    //   每條小蛇 new /obj/race/rainnar_snake 移入玩家並 add_temp apply/armor+defense，
    //   上限 5 條（指令自我把關，race daemon 不替玩家 add_action，見 content-race-active.md）。
    // TODO: equipment 雨師妾袍
}

void initialize(object ob)
{
    ::initialize(ob);

    // 屬性上限 str/cor/int/spi/cps/dex/con/wis = 9/9/22/24/20/13/13/28
    ob->init_attribute(([
        "str": 4  + random(6),
        "cor": 4  + random(6),
        "int": 17 + random(6),
        "spi": 19 + random(6),
        "cps": 15 + random(6),
        "dex": 8  + random(6),
        "con": 8  + random(6),
        "wis": 23 + random(6)
    ]));

    ob->init_statistic(([
        "gin": 40,
        "kee": 30,
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
