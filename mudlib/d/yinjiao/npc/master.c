#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("隱教教主", ({"master", "yinjiao_master"}));
    set_attr("str", 22);
    set_attr("con", 20);
    set_attr("dex", 26);
    set_attr("wis", 20);
    set_attr("spi", 24);
    set_race("human");
    set_class("thief");
    set_level(60);

    set_skill("dagger", 95);
    set_skill("dodge", 90);
    set_skill("parry", 80);
    set_skill("unarmed", 70);

    set("age", 50);
    set("attitude", "peaceful");
    set("long",
        "隱教教主﹐身穿一件黑色的大氅﹐面容隱藏在兜帽的陰影中﹐\n"
        "只露出一雙精光閃閃的眼睛。渾身散發著一股陰冷的威壓。\n");
    setup();
    carry_object(__DIR__"obj/eagle_glove")->wear();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_money("silver", 80);
    set_temp("apply/vision_of_ghost", 1);
}

void set_flag(object me)
{
    if( me && present(me, environment()) ) {
        if( me->query_class() != "commoner"
        ||  me->query("title") )
            return;
        me->set_temp("pending/yinjiao_master", 1);
    }
    else
        do_chat("隱教教主冷冷道﹕哼﹐走了。\n");
}

int accept_apprentice(object me)
{
    if( is_chatting() ) return 0;
    if( me->query_temp("pending/yinjiao_master") ) return 1;
    if( me->query("title") ) {
        do_chat("隱教教主冷冷道﹕你已有師門﹐別來多事。\n");
        return 0;
    }
    do_chat(({
        "隱教教主審視著你﹐說道﹕想加入隱教？\n",
        "隱教教主說道﹕隱教之人﹐必須絕對忠誠﹐不容背叛。\n",
        "隱教教主說道﹕你若真有決心﹐便再來找我。\n",
        (: set_flag, me :)
    }));
    return 0;
}

int init_apprentice(object me)
{
    if( me->query_class() != "commoner" ) {
        do_chat(({
            "隱教教主搖了搖頭﹐說道﹕你既入別門﹐隱教不收。\n",
        }));
        return 1;
    }
    if( ::init_apprentice(me) ) {
        seteuid(getuid());
        me->set_class("thief");
        me->set("title", "隱教弟子");
        do_chat(({
            "隱教教主點了點頭﹐說道﹕好﹐從今日起你便是隱教的人了。\n",
            "隱教教主說道﹕記住﹐隱教之事﹐不得外洩。\n",
            "隱教教主揮了揮手﹐說道﹕去吧。\n"
        }));
    }
}

int acquire_skill(object ob, string skill)
{
    if( is_chatting() )
        return notify_fail("你最好等教主的話說完再插嘴。\n");
    if( !ob->is_apprentice_of(this_object()) ) return 0;

    switch(skill) {
    case "dagger":
        if( !ob->query_learn(skill) ) {
            say("隱教教主點了點頭，冷冷道：好，為師傳你暗器之術。\n");
            message_vision("$N將隱教的暗器之術傳授給$n。\n", this_object(), ob);
            ob->improve_skill(skill, random(ob->query_attr("dex")) + 1);
        }
        break;
    default:
        return 0;
    }

    do_chat(({
        "隱教教主說道：暗器之術﹐在於出其不意﹐一擊必中。\n",
        "隱教教主說道：好好練。\n",
    }));

    return 1;
}
