#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("瑯夷堂主", ({"master", "langyi_master"}));
    set_attr("str", 20);
    set_attr("con", 18);
    set_attr("dex", 26);
    set_attr("wis", 22);
    set_attr("cps", 24);
    set_race("human");
    set_class("thief");
    set_level(55);

    set_skill("dagger", 95);
    set_skill("dodge", 90);
    set_skill("parry", 75);
    set_skill("unarmed", 60);

    set("age", 40);
    set("attitude", "peaceful");
    set("long",
        "瑯夷堂主﹐面容削瘦﹐雙目細長﹐嘴角掛著一抹陰險的笑意。\n"
        "身穿一件暗灰色的勁裝﹐腰間掛著一柄短匕﹐渾身透著一股精\n"
        "明幹練的氣質。\n");
    setup();
    carry_object(__DIR__"obj/viper_dagger")->wield();
    carry_object(__DIR__"obj/night_suit")->wear();
    carry_money("silver", 80);
}

void set_flag(object me)
{
    if( me && present(me, environment()) ) {
        if( me->query_class() != "commoner"
        ||  me->query("title") )
            return;
        me->set_temp("pending/langyi_master", 1);
    }
    else
        do_chat("瑯夷堂主陰笑道﹕嘿嘿﹐跑了。\n");
}

int accept_apprentice(object me)
{
    if( is_chatting() ) return 0;
    if( me->query_temp("pending/langyi_master") ) return 1;
    if( me->query("title") ) {
        do_chat("瑯夷堂主陰笑道﹕你已有師門﹐別來湊熱鬧。\n");
        return 0;
    }
    do_chat(({
        "瑯夷堂主上下打量了你一番﹐說道﹕想加入瑯夷？\n",
        "瑯夷堂主說道﹕瑯夷的人﹐要夠機靈﹐夠狠辣。\n",
        "瑯夷堂主說道﹕你若真想入夥﹐便再來找我。\n",
        (: set_flag, me :)
    }));
    return 0;
}

int init_apprentice(object me)
{
    if( me->query_class() != "commoner" ) {
        do_chat(({
            "瑯夷堂主搖了搖頭﹐說道﹕你既入別門﹐就別想腳踏兩條船。\n",
        }));
        return 1;
    }
    if( ::init_apprentice(me) ) {
        seteuid(getuid());
        me->set_class("thief");
        me->set("title", "瑯夷弟子");
        do_chat(({
            "瑯夷堂主點了點頭﹐說道﹕好﹐從今天起你就是瑯夷的人了。\n",
            "瑯夷堂主說道﹕記住﹐入了瑯夷﹐就要聽號令行事。\n",
            "瑯夷堂主揮了揮手﹐說道﹕去吧。\n"
        }));
    }
}

int acquire_skill(object ob, string skill)
{
    if( is_chatting() )
        return notify_fail("你最好等堂主的話說完再插嘴。\n");
    if( !ob->is_apprentice_of(this_object()) ) return 0;

    switch(skill) {
    case "dagger":
        if( !ob->query_learn(skill) ) {
            say("瑯夷堂主點了點頭，說道：好，為師傳你匕首之術。\n");
            message_vision("$N將瑯夷的匕首技法傳授給$n。\n", this_object(), ob);
            ob->improve_skill(skill, random(ob->query_attr("dex")) + 1);
        }
        break;
    default:
        return 0;
    }

    do_chat(({
        "瑯夷堂主說道：匕首之術﹐講究快、狠、準﹐一擊必殺。\n",
        "瑯夷堂主說道：好好練吧。\n",
    }));

    return 1;
}
