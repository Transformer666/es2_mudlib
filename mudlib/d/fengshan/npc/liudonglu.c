// liudonglu.c - 柳東蘆 Liu Donglu, Fengshan Sword School Leader

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("柳東蘆", ({"liudonglu", "liu_donglu"}));
    set_attr("str", 20);
    set_attr("con", 20);
    set_attr("dex", 24);
    set_attr("wis", 22);
    set_attr("spi", 20);
    set_race("human");
    set_class("warrior");
    set_level(60);

    set_skill("sword", 100);
    set_skill("fengshan sword", 95);
    set_skill("dodge", 90);
    set_skill("parry", 85);
    set_skill("unarmed", 50);

    set("age", 50);
    set("attitude", "peaceful");
    set("long",
	"封山派掌門人柳東蘆﹐身穿一襲灰袍﹐鬢髮斑白﹐面容清瘦﹐\n"
	"但一雙眼睛精光閃閃。腰間懸著一柄古劍﹐劍鞘上刻著封山二字。\n");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_object( STOCK_WEAPON("longsword") )->wield();
    carry_money("silver", 50);
}

void set_flag(object me)
{
    if( me && present(me, environment()) ) {
        if( me->query_class() != "commoner"
        ||  me->query("title") )
            return;
        me->set_temp("pending/liudonglu", 1);
    }
    else
        do_chat("柳東蘆嘆了口氣﹐說道﹕人都走了 ...。\n");
}

int accept_apprentice(object me)
{
    if( is_chatting() ) return 0;
    if( me->query_temp("pending/liudonglu") ) return 1;
    if( me->query("title") ) {
        do_chat("柳東蘆道﹕你已入他門﹐莫要三心二意。\n");
        return 0;
    }
    do_chat(({
        "柳東蘆看了你一眼﹐說道﹕封山劍法﹐非有緣者不傳。\n",
        "柳東蘆踱了幾步﹐說道﹕我封山派立派百年﹐向來只收心誠之人。\n",
        "柳東蘆微微頷首﹐說道﹕你若當真有心﹐便再來求我一次。\n",
        (: set_flag, me :)
    }));
    return 0;
}

int init_apprentice(object me)
{
    if( me->query_class() != "commoner" ) {
        do_chat(({
            "柳東蘆搖了搖頭﹐說道﹕你既有師門﹐何必再拜我門下？\n",
            "柳東蘆揮了揮手﹐說道﹕去吧。\n"
        }));
        return 1;
    }
    if( ::init_apprentice(me) ) {
        seteuid(getuid());
        me->set_class("warrior");
        me->set("title", "封山派弟子");
        do_chat(({
            "柳東蘆點了點頭﹐說道﹕好﹐從今日起你便是封山派弟子了。\n",
            "柳東蘆說道﹕封山劍法講究以靜制動﹐你先好生修煉基本功。\n",
            "柳東蘆說道﹕去吧﹐有空多練劍﹐莫要荒廢了。\n"
        }));
    }
}

int acquire_skill(object ob, string skill)
{
    if( is_chatting() )
        return notify_fail("你最好等他老人家的話說完再插嘴。\n");
    if( !ob->is_apprentice_of(this_object()) ) return 0;

    switch(skill) {
    case "fengshan sword":
        if( !ob->query_learn(skill) ) {
            say("柳東蘆點了點頭，說道：好，為師這就傳你封山劍法。\n");
            message_vision("$N將封山劍法的入門招式傳授給$n。\n", this_object(), ob);
            ob->improve_skill(skill, random(ob->query_attr("dex")) + 1);
        }
        break;
    default:
        return 0;
    }

    do_chat(({
        "柳東蘆說道：劍法之道﹐重在練心不在練招。\n",
        "柳東蘆說道：你好生修煉﹐日後自有進境。\n",
    }));

    return 1;
}
