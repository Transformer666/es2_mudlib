#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("天師掌教", ({"master", "tianshi_master"}));
    set_attr("str", 18);
    set_attr("con", 20);
    set_attr("dex", 20);
    set_attr("int", 24);
    set_attr("wis", 22);
    set_attr("spi", 26);
    set_race("human");
    set_class("taoist");
    set_level(60);

    set_skill("sword", 85);
    set_skill("taiyi sword", 90);
    set_skill("ziwei neigong", 85);
    set_skill("dodge", 80);
    set_skill("parry", 75);

    set("age", 65);
    set("attitude", "peaceful");
    set("long",
        "天師掌教﹐身穿紫色道袍﹐頭戴金冠﹐面容清矍﹐雙目有神\n"
        "。手持一柄古劍﹐仙風道骨﹐頗具高人氣派。\n");
    setup();
    carry_object(__DIR__"obj/taiyi_sword")->wield();
    carry_object(__DIR__"obj/taoist_robe")->wear();
    carry_money("silver", 60);
    set_temp("apply/vision_of_ghost", 1);
}

void set_flag(object me)
{
    if( me && present(me, environment()) ) {
        if( me->query_class() != "commoner"
        ||  me->query("title") )
            return;
        me->set_temp("pending/tianshi_master", 1);
    }
    else
        do_chat("天師掌教撫鬚道﹕咦﹐人呢？\n");
}

int accept_apprentice(object me)
{
    if( is_chatting() ) return 0;
    if( me->query_temp("pending/tianshi_master") ) return 1;
    if( me->query("title") ) {
        do_chat("天師掌教搖頭道﹕你已有師門﹐不宜再入道門。\n");
        return 0;
    }
    do_chat(({
        "天師掌教撫鬚說道﹕想入我天師派修道？\n",
        "天師掌教說道﹕天師派以符咒道法聞名﹐非有道緣者不傳。\n",
        "天師掌教微微一笑﹐說道﹕你若真有道心﹐便再來找貧道。\n",
        (: set_flag, me :)
    }));
    return 0;
}

int init_apprentice(object me)
{
    if( me->query_class() != "commoner" ) {
        do_chat(({
            "天師掌教搖了搖頭﹐說道﹕你既入他門﹐不宜再習道法。\n",
        }));
        return 1;
    }
    if( ::init_apprentice(me) ) {
        seteuid(getuid());
        me->set_class("taoist");
        me->set("title", "天師派弟子");
        do_chat(({
            "天師掌教點了點頭﹐說道﹕好﹐從今日起你便是天師派弟子了。\n",
            "天師掌教說道﹕天師道法﹐以劍御符﹐以符馭靈﹐你先修煉劍術。\n",
            "天師掌教揮了揮手﹐說道﹕去吧﹐好生修行。\n"
        }));
    }
}

int acquire_skill(object ob, string skill)
{
    if( is_chatting() )
        return notify_fail("你最好等掌教的話說完再插嘴。\n");
    if( !ob->is_apprentice_of(this_object()) ) return 0;

    switch(skill) {
    case "taiyi sword":
        if( !ob->query_learn(skill) ) {
            say("天師掌教點了點頭，說道：好，貧道傳你太乙劍法。\n");
            message_vision("$N將天師派的太乙劍法傳授給$n。\n", this_object(), ob);
            ob->improve_skill(skill, random(ob->query_attr("spi")) + 1);
        }
        break;
    case "ziwei neigong":
        if( !ob->query_learn(skill) ) {
            say("天師掌教點了點頭，說道：好，貧道傳你紫微內功。\n");
            message_vision("$N將天師派的紫微內功心法傳授給$n。\n", this_object(), ob);
            ob->improve_skill(skill, random(ob->query_attr("spi")) + 1);
        }
        break;
    default:
        return 0;
    }

    do_chat(({
        "天師掌教說道：太乙劍法﹐以道御劍﹐劍隨心轉。\n",
        "天師掌教說道：你好自修行吧。\n",
    }));

    return 1;
}
