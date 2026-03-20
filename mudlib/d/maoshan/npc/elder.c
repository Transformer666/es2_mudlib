// elder.c - Maoshan Elder

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("茅山長老", ({"elder", "maoshan_elder"}));
    set_attr("str", 18);
    set_attr("con", 18);
    set_attr("dex", 20);
    set_attr("int", 24);
    set_attr("wis", 25);
    set_attr("spi", 26);
    set_race("human");
    set_class("taoist");
    set_level(60);

    set_skill("sword", 85);
    set_skill("maoshan sword", 90);
    set_skill("maoshan neigong", 80);
    set_skill("dodge", 75);
    set_skill("parry", 70);

    set("age", 70);
    set("attitude", "peaceful");
    set("long",
	"茅山派長老﹐身穿一件玄色道袍﹐頭戴混元巾﹐手持一柄拂塵﹐\n"
	"仙風道骨﹐飄飄然有出塵之姿。\n");
    set("chat_chance", 1);
    set("chat_msg", ({
	"長老撫鬚說道﹕道法自然﹐萬物歸一。\n",
    }));
    setup();
    carry_object( STOCK_WEAPON("longsword") )->wield();
    carry_money("coin", 200);
    set_temp("apply/vision_of_ghost", 1);
}

void set_flag(object me)
{
    if( me && present(me, environment()) ) {
        if( me->query_class() != "commoner"
        ||  me->query("title") )
            return;
        me->set_temp("pending/maoshan_elder", 1);
    }
    else
        do_chat("長老撫了撫鬚﹐自言自語道﹕咦﹐人呢？\n");
}

int accept_apprentice(object me)
{
    if( is_chatting() ) return 0;
    if( me->query_temp("pending/maoshan_elder") ) return 1;
    if( me->query("title") ) {
        do_chat("長老搖了搖頭﹐說道﹕你已入他門﹐不宜再拜貧道。\n");
        return 0;
    }
    do_chat(({
        "長老撫鬚說道﹕想入茅山門下？\n",
        "長老說道﹕茅山道術﹐講究心誠則靈﹐非有道緣者不傳。\n",
        "長老微微一笑﹐說道﹕你若真有道緣﹐便再來找貧道。\n",
        (: set_flag, me :)
    }));
    return 0;
}

int init_apprentice(object me)
{
    if( me->query_class() != "commoner" ) {
        do_chat(({
            "長老搖了搖頭﹐說道﹕你既已入別派﹐就不宜再習道術了。\n",
        }));
        return 1;
    }
    if( ::init_apprentice(me) ) {
        seteuid(getuid());
        me->set_class("taoist");
        me->set("title", "茅山派弟子");
        do_chat(({
            "長老點了點頭﹐說道﹕好﹐從今日起你便是茅山弟子了。\n",
            "長老說道﹕茅山道術博大精深﹐你先修煉靜心之功。\n",
            "長老揮了揮拂塵﹐說道﹕去吧﹐好生修行。\n"
        }));
    }
}

int acquire_skill(object ob, string skill)
{
    if( is_chatting() )
        return notify_fail("你最好等長老的話說完再插嘴。\n");
    if( !ob->is_apprentice_of(this_object()) ) return 0;

    switch(skill) {
    case "maoshan sword":
        if( !ob->query_learn(skill) ) {
            say("長老點了點頭，說道：好，貧道這就傳你茅山劍法。\n");
            message_vision("$N將茅山劍法的入門心要傳授給$n。\n", this_object(), ob);
            ob->improve_skill(skill, random(ob->query_attr("spi")) + 1);
        }
        break;
    default:
        return 0;
    }

    do_chat(({
        "長老說道：劍法之妙﹐在於以道御劍﹐心中有道﹐劍自通靈。\n",
        "長老說道：你好自修行吧。\n",
    }));

    return 1;
}
