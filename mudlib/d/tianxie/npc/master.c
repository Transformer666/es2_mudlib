#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("天邪掌門", ({"master", "tianxie_master"}));
    set_attr("str", 24);
    set_attr("con", 22);
    set_attr("dex", 26);
    set_attr("wis", 20);
    set_attr("spi", 18);
    set_race("human");
    set_class("warrior");
    set_level(65);

    set_skill("sword", 100);
    set_skill("phantom sword", 95);
    set_skill("dodge", 95);
    set_skill("parry", 85);
    set_skill("unarmed", 70);

    set("age", 45);
    set("attitude", "peaceful");
    set("long",
        "天邪派掌門﹐一身黑衣﹐面容冷峻﹐目光如鷹般銳利。腰間斜\n"
        "挎著一柄暗黑色的長刀﹐渾身散發著一股陰冷的殺氣。\n");
    setup();
    carry_object(__DIR__"obj/dark_blade")->wield();
    carry_object(__DIR__"obj/shadow_cloak")->wear();
    carry_money("silver", 100);
    set_temp("apply/vision_of_ghost", 1);
}

void set_flag(object me)
{
    if( me && present(me, environment()) ) {
        if( me->query_class() != "commoner"
        ||  me->query("title") )
            return;
        me->set_temp("pending/tianxie_master", 1);
    }
    else
        do_chat("天邪掌門冷笑一聲﹐說道﹕哼﹐跑了。\n");
}

int accept_apprentice(object me)
{
    if( is_chatting() ) return 0;
    if( me->query_temp("pending/tianxie_master") ) return 1;
    if( me->query("title") ) {
        do_chat("天邪掌門冷冷道﹕你已有師門﹐莫來自尋死路。\n");
        return 0;
    }
    do_chat(({
        "天邪掌門上下打量了你一番﹐冷笑道﹕想入我天邪派？\n",
        "天邪掌門說道﹕天邪派的弟子﹐必須心狠手辣﹐不留餘地。\n",
        "天邪掌門說道﹕你若不怕死﹐便再來找我。\n",
        (: set_flag, me :)
    }));
    return 0;
}

int init_apprentice(object me)
{
    if( me->query_class() != "commoner" ) {
        do_chat(({
            "天邪掌門冷笑道﹕你既入他門﹐就別想投靠天邪。\n",
        }));
        return 1;
    }
    if( ::init_apprentice(me) ) {
        seteuid(getuid());
        me->set_class("warrior");
        me->set("title", "天邪派弟子");
        do_chat(({
            "天邪掌門點了點頭﹐說道﹕好﹐從今日起你便是天邪派的人了。\n",
            "天邪掌門說道﹕記住﹐天邪派只有強者才能生存。\n",
            "天邪掌門揮了揮手﹐說道﹕去吧﹐別讓我失望。\n"
        }));
    }
}

int acquire_skill(object ob, string skill)
{
    if( is_chatting() )
        return notify_fail("你最好等掌門的話說完再插嘴。\n");
    if( !ob->is_apprentice_of(this_object()) ) return 0;

    switch(skill) {
    case "phantom sword":
        if( !ob->query_learn(skill) ) {
            say("天邪掌門點了點頭，冷冷道：好，為師傳你幻影劍法。\n");
            message_vision("$N將天邪派的幻影劍法傳授給$n。\n", this_object(), ob);
            ob->improve_skill(skill, random(ob->query_attr("dex")) + 1);
        }
        break;
    default:
        return 0;
    }

    do_chat(({
        "天邪掌門說道：幻影劍法﹐講究出劍如幻影﹐令敵人防不勝防。\n",
        "天邪掌門說道：好好練﹐莫要丟了天邪派的臉。\n",
    }));

    return 1;
}
