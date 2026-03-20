// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("靜慧師太", ({"master", "tianyue_master", "jinghui"}));
    set_attr("str", 18);
    set_attr("con", 22);
    set_attr("dex", 20);
    set_attr("wis", 26);
    set_attr("spi", 24);
    set_race("human");
    set_class("monk");
    set_level(55);

    set_skill("staff", 88);
    set_skill("dodge", 75);
    set_skill("parry", 78);
    set_skill("unarmed", 68);

    set("age", 60);
    set("gender", "female");
    set("attitude", "peaceful");
    set("long",
        "天月庵住持靜慧師太﹐年約六旬﹐面容清瘦而慈祥﹐身穿素色\n"
        "僧袍﹐手持一根月牙禪杖﹐舉止端莊﹐周身散發著一股超凡脫俗\n"
        "的氣息。\n");
    setup();
    carry_object(__DIR__"obj/moon_staff")->wield();
    carry_object(__DIR__"obj/nun_robe")->wear();
    carry_money("coin", 100);
}

void set_flag(object me)
{
    if( me && present(me, environment()) ) {
        if( me->query_class() != "commoner"
        ||  me->query("title") )
            return;
        me->set_temp("pending/tianyue_master", 1);
    }
    else
        do_chat("靜慧師太雙手合十﹐說道﹕阿彌陀佛﹐施主已去。\n");
}

int accept_apprentice(object me)
{
    if( is_chatting() ) return 0;
    if( me->query_temp("pending/tianyue_master") ) return 1;
    if( me->query("title") ) {
        do_chat("靜慧師太說道﹕施主已有師門﹐緣分不在此處。\n");
        return 0;
    }
    do_chat(({
        "靜慧師太微微抬眼﹐說道﹕施主想入我天月庵修行？\n",
        "靜慧師太說道﹕天月庵以濟世度人為己任﹐修的是慈悲之心。\n",
        "靜慧師太說道﹕施主若真有佛緣﹐便再來找老身。\n",
        (: set_flag, me :)
    }));
    return 0;
}

int init_apprentice(object me)
{
    if( me->query_class() != "commoner" ) {
        do_chat(({
            "靜慧師太搖了搖頭﹐說道﹕施主既入別門﹐不宜再入佛門。\n",
        }));
        return 1;
    }
    if( ::init_apprentice(me) ) {
        seteuid(getuid());
        me->set_class("monk");
        me->set("title", "天月庵弟子");
        do_chat(({
            "靜慧師太點了點頭﹐說道﹕善哉善哉﹐從今日起你便是天月庵弟子了。\n",
            "靜慧師太說道﹕佛門弟子﹐當以慈悲為懷﹐濟世度人。\n",
            "靜慧師太說道﹕去吧﹐好生修行﹐阿彌陀佛。\n"
        }));
    }
}

int acquire_skill(object ob, string skill)
{
    if( is_chatting() )
        return notify_fail("你最好等師太的話說完再插嘴。\n");
    if( !ob->is_apprentice_of(this_object()) ) return 0;

    switch(skill) {
    case "staff":
        if( !ob->query_learn(skill) ) {
            say("靜慧師太點了點頭，說道：好，老身傳你棍法。\n");
            message_vision("$N將天月庵的棍法傳授給$n。\n", this_object(), ob);
            ob->improve_skill(skill, random(ob->query_attr("con")) + 1);
        }
        break;
    default:
        return 0;
    }

    do_chat(({
        "靜慧師太說道：棍法之道﹐以守護為本﹐以慈悲為根。\n",
        "靜慧師太說道：你好生修煉﹐阿彌陀佛。\n",
    }));

    return 1;
}
