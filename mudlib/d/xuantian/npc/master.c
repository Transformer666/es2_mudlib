#include <npc.h>

inherit F_SCHOLAR;

void create()
{
    set_name("玄天教主", ({"master", "xuantian_master"}));
    set_attr("str", 18);
    set_attr("con", 18);
    set_attr("dex", 20);
    set_attr("int", 24);
    set_attr("wis", 22);
    set_attr("spi", 24);
    set_race("human");
    set_class("scholar");
    set_level(55);

    set_skill("sword", 85);
    set_skill("dodge", 75);
    set_skill("parry", 70);

    set("age", 55);
    set("attitude", "peaceful");
    set("long",
        "玄天教主﹐身穿黑色道袍﹐面容莊嚴﹐頭戴玄冠﹐手持一柄\n"
        "七星劍﹐渾身散發著一股不怒而威的氣勢。\n");
    setup();
    carry_object(__DIR__"obj/xuantian_sword")->wield();
    carry_object(__DIR__"obj/xuan_cloth")->wear();
    carry_money("silver", 50);
    set_temp("apply/vision_of_ghost", 1);
}

void set_flag(object me)
{
    if( me && present(me, environment()) ) {
        if( me->query_class() != "commoner"
        ||  me->query("title") )
            return;
        me->set_temp("pending/xuantian_master", 1);
    }
    else
        do_chat("玄天教主搖了搖頭﹐說道﹕人走了。\n");
}

int accept_apprentice(object me)
{
    if( is_chatting() ) return 0;
    if( me->query_temp("pending/xuantian_master") ) return 1;
    if( me->query("title") ) {
        do_chat("玄天教主搖頭道﹕你已有師門﹐不宜再入玄天。\n");
        return 0;
    }
    do_chat(({
        "玄天教主看了你一眼﹐說道﹕想入我玄天教？\n",
        "玄天教主說道﹕玄天教奉玄天上帝﹐修文習武﹐非有志者不收。\n",
        "玄天教主說道﹕你若真有心﹐便再來找我。\n",
        (: set_flag, me :)
    }));
    return 0;
}

int init_apprentice(object me)
{
    if( me->query_class() != "commoner" ) {
        do_chat(({
            "玄天教主搖了搖頭﹐說道﹕你既入別門﹐不宜再入玄天教。\n",
        }));
        return 1;
    }
    if( ::init_apprentice(me) ) {
        seteuid(getuid());
        me->set_class("scholar");
        me->set("title", "玄天教弟子");
        do_chat(({
            "玄天教主點了點頭﹐說道﹕好﹐從今日起你便是玄天教弟子了。\n",
            "玄天教主說道﹕玄天之道﹐以文入道﹐以道御劍。\n",
            "玄天教主說道﹕去吧﹐好好修行。\n"
        }));
    }
}

int acquire_skill(object ob, string skill)
{
    if( is_chatting() )
        return notify_fail("你最好等教主的話說完再插嘴。\n");
    if( !ob->is_apprentice_of(this_object()) ) return 0;

    switch(skill) {
    case "sword":
        if( !ob->query_learn(skill) ) {
            say("玄天教主點了點頭，說道：好，為師傳你玄天劍法。\n");
            message_vision("$N將玄天教的劍法傳授給$n。\n", this_object(), ob);
            ob->improve_skill(skill, random(ob->query_attr("int")) + 1);
        }
        break;
    default:
        return 0;
    }

    do_chat(({
        "玄天教主說道：劍法之要﹐心正則劍正﹐心邪則劍邪。\n",
        "玄天教主說道：好好修煉。\n",
    }));

    return 1;
}
