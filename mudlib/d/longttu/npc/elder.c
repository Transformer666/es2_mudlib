#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("龍圖長老", ({"elder", "longttu_elder"}));
    set_attr("str", 16);
    set_attr("con", 18);
    set_attr("dex", 18);
    set_attr("int", 22);
    set_attr("wis", 24);
    set_attr("spi", 20);
    set_race("human");
    set_class("alchemist");
    set_level(50);

    set_skill("needle", 80);
    set_skill("alchemy-medication", 100);
    set_skill("dodge", 60);

    set("age", 60);
    set("attitude", "peaceful");
    set("long",
        "龍圖長老﹐面容和善﹐鬚髮皆白﹐身穿一件灰色的布袍﹐腰\n"
        "間掛著一個藥箱﹐渾身散發著淡淡的藥香。\n");
    setup();
    carry_object(__DIR__"obj/silver_needle")->wield();
    carry_object(__DIR__"obj/alchemy_robe")->wear();
    carry_money("coin", 200);
    set_temp("apply/vision_of_ghost", 1);
}

void set_flag(object me)
{
    if( me && present(me, environment()) ) {
        if( me->query_class() != "commoner"
        ||  me->query("title") )
            return;
        me->set_temp("pending/longttu_elder", 1);
    }
    else
        do_chat("龍圖長老搖了搖頭﹐說道﹕嗯﹖人走了﹖\n");
}

int accept_apprentice(object me)
{
    if( is_chatting() ) return 0;
    if( me->query_temp("pending/longttu_elder") ) return 1;
    if( me->query("title") ) {
        do_chat("龍圖長老說道﹕你已有師門﹐老夫不便收你為徒了。\n");
        return 0;
    }
    do_chat(({
        "龍圖長老上下打量了你一番﹐說道﹕你想學丹術﹖\n",
        "龍圖長老說道﹕丹道一途﹐首重心性﹐次重悟性﹐非有耐心者不能有成。\n",
        "龍圖長老撫了撫長鬚﹐說道﹕你若真心想學﹐再來找老夫吧。\n",
        (: set_flag, me :)
    }));
    return 0;
}

int init_apprentice(object me)
{
    if( me->query_class() != "commoner" ) {
        do_chat(({
            "龍圖長老說道﹕你既已入別派﹐老夫便不好再收你了。\n",
            "龍圖長老揮了揮手﹐說道﹕去吧。\n"
        }));
        return 1;
    }
    if( ::init_apprentice(me) ) {
        seteuid(getuid());
        me->set_class("alchemist");
        me->set("title", "龍圖丹派弟子");
        do_chat(({
            "龍圖長老點了點頭﹐說道﹕好﹐老夫便收你入門。\n",
            "龍圖長老說道﹕入門之後﹐先從辨藥識方做起﹐不可好高騖遠。\n",
            "龍圖長老說道﹕去吧﹐好好用功。\n"
        }));
    }
}

int acquire_skill(object ob, string skill)
{
    if( is_chatting() )
        return notify_fail("你最好等長老的話說完再插嘴。\n");
    if( !ob->is_apprentice_of(this_object()) ) return 0;

    switch(skill) {
    case "needle":
        if( !ob->query_learn(skill) ) {
            say("龍圖長老點了點頭，說道：好，老夫傳你銀針之術。\n");
            message_vision("$N將龍圖丹派的銀針之術傳授給$n。\n", this_object(), ob);
            ob->improve_skill(skill, random(ob->query_attr("wis")) + 1);
        }
        break;
    case "longttu neigong":
        if( !ob->query_learn(skill)
        &&  ob->query_skill("needle") >= 30 ) {
            say("龍圖長老點了點頭，說道：你針法已有小成，老夫傳你龍圖內功心法。\n");
            message_vision("$N將龍圖丹派的內功心法傳授給$n。\n", this_object(), ob);
            ob->improve_skill(skill, random(ob->query_attr("spi")) + 1);
        }
        break;
    default:
        return 0;
    }

    do_chat(({
        "龍圖長老說道：銀針之術﹐在於識穴認經﹐下針精準。\n",
        "龍圖長老說道：好好修煉。\n",
    }));

    return 1;
}
