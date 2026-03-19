#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("劍甲門主", ({"master", "jianjia_master"}));
    set_attr("str", 22);
    set_attr("con", 22);
    set_attr("dex", 20);
    set_attr("int", 22);
    set_attr("wis", 20);
    set_attr("spi", 18);
    set_race("human");
    set_class("alchemist");
    set_level(50);

    set_skill("sword", 85);
    set_skill("needle", 80);
    set_skill("dodge", 65);
    set_skill("parry", 70);

    set("age", 48);
    set("attitude", "peaceful");
    set("long",
        "劍甲門主﹐身材魁梧﹐面色黝黑﹐雙手佈滿了鍛造留下的老\n"
        "繭和燙傷。身穿一件厚實的皮圍裙﹐腰間佩著一把鋒利的長劍。\n");
    setup();
    carry_object(__DIR__"obj/jianjia_sword")->wield();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_money("silver", 50);
}

void set_flag(object me)
{
    if( me && present(me, environment()) ) {
        if( me->query_class() != "commoner"
        ||  me->query("title") )
            return;
        me->set_temp("pending/jianjia_master", 1);
    }
    else
        do_chat("劍甲門主哼了一聲﹐說道﹕走了。\n");
}

int accept_apprentice(object me)
{
    if( is_chatting() ) return 0;
    if( me->query_temp("pending/jianjia_master") ) return 1;
    if( me->query("title") ) {
        do_chat("劍甲門主搖頭道﹕你已有師門﹐別來湊熱鬧。\n");
        return 0;
    }
    do_chat(({
        "劍甲門主看了看你的手﹐說道﹕想學鑄劍煉器？\n",
        "劍甲門主說道﹕劍甲門的人﹐要能吃苦﹐受得了爐火的煎熬。\n",
        "劍甲門主說道﹕你若真有心﹐便再來找我。\n",
        (: set_flag, me :)
    }));
    return 0;
}

int init_apprentice(object me)
{
    if( me->query_class() != "commoner" ) {
        do_chat(({
            "劍甲門主搖了搖頭﹐說道﹕你既入別門﹐恕難收留。\n",
        }));
        return 1;
    }
    if( ::init_apprentice(me) ) {
        seteuid(getuid());
        me->set_class("alchemist");
        me->set("title", "劍甲門弟子");
        do_chat(({
            "劍甲門主點了點頭﹐說道﹕好﹐從今日起你便是劍甲門弟子了。\n",
            "劍甲門主說道﹕劍甲之道﹐以劍入道﹐以爐煉心。\n",
            "劍甲門主說道﹕去吧﹐先去鍛造室練練手。\n"
        }));
    }
}

int acquire_skill(object ob, string skill)
{
    if( is_chatting() )
        return notify_fail("你最好等門主的話說完再插嘴。\n");
    if( !ob->is_apprentice_of(this_object()) ) return 0;

    switch(skill) {
    case "sword":
        if( !ob->query_learn(skill) ) {
            say("劍甲門主點了點頭，說道：好，為師傳你劍法。\n");
            message_vision("$N將劍甲門的劍法傳授給$n。\n", this_object(), ob);
            ob->improve_skill(skill, random(ob->query_attr("str")) + 1);
        }
        break;
    case "needle":
        if( !ob->query_learn(skill) ) {
            say("劍甲門主點了點頭，說道：好，為師傳你針法。\n");
            message_vision("$N將劍甲門的針法傳授給$n。\n", this_object(), ob);
            ob->improve_skill(skill, random(ob->query_attr("dex")) + 1);
        }
        break;
    default:
        return 0;
    }

    do_chat(({
        "劍甲門主說道：鑄劍如練功﹐需要千錘百煉。\n",
        "劍甲門主說道：好好練吧。\n",
    }));

    return 1;
}
