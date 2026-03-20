// abbot.c - Baixiang Temple Abbot

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("白象寺方丈", ({"abbot", "fangzhang"}));
    set_attr("str", 20);
    set_attr("con", 22);
    set_attr("wis", 25);
    set_attr("spi", 24);
    set_attr("cps", 22);
    set_race("human");
    set_class("monk");
    set_level(60);

    set_skill("staff", 90);
    set_skill("diamond hammer", 85);
    set_skill("dodge", 75);
    set_skill("parry", 80);
    set_skill("unarmed", 70);

    set("age", 65);
    set("attitude", "peaceful");
    set("long",
	"白象寺方丈﹐身穿一件洗得發白的灰色僧袍﹐面容慈祥﹐雙手\n"
	"合十﹐身形雖然消瘦﹐但自有一股不怒而威的氣勢。\n");
    set("chat_chance", 1);
    set("chat_msg", ({
	"方丈微微一笑﹐說道﹕施主﹐萬法皆空﹐放下即是自在。\n",
    }));
    setup();
    carry_money("coin", 100);
    set_temp("apply/vision_of_ghost", 1);
}

void set_flag(object me)
{
    if( me && present(me, environment()) ) {
        if( me->query_class() != "commoner"
        ||  me->query("title") )
            return;
        me->set_temp("pending/abbot", 1);
    }
    else
        do_chat("方丈雙手合十﹐說道﹕阿彌陀佛﹐施主已去。\n");
}

int accept_apprentice(object me)
{
    if( is_chatting() ) return 0;
    if( me->query_temp("pending/abbot") ) return 1;
    if( me->query("title") ) {
        do_chat("方丈說道﹕施主已有師門﹐老衲不便再收。\n");
        return 0;
    }
    do_chat(({
        "方丈微微一笑﹐說道﹕施主想皈依佛門？\n",
        "方丈說道﹕白象寺雖是小廟﹐但佛法無邊﹐非有佛緣者不收。\n",
        "方丈說道﹕施主若真有佛緣﹐便再來找老衲吧。\n",
        (: set_flag, me :)
    }));
    return 0;
}

int init_apprentice(object me)
{
    if( me->query_class() != "commoner" ) {
        do_chat(({
            "方丈搖了搖頭﹐說道﹕施主既已入別派﹐就不宜再入佛門了。\n",
        }));
        return 1;
    }
    if( ::init_apprentice(me) ) {
        seteuid(getuid());
        me->set_class("monk");
        me->set("title", "白象寺弟子");
        do_chat(({
            "方丈點了點頭﹐說道﹕善哉﹐從今日起你便是白象寺弟子了。\n",
            "方丈說道﹕佛門弟子﹐當以慈悲為懷﹐廣度眾生。\n",
            "方丈說道﹕去吧﹐好生修行。\n"
        }));
    }
}

int acquire_skill(object ob, string skill)
{
    if( is_chatting() )
        return notify_fail("你最好等方丈的話說完再插嘴。\n");
    if( !ob->is_apprentice_of(this_object()) ) return 0;

    switch(skill) {
    case "staff":
        if( !ob->query_learn(skill) ) {
            say("方丈點了點頭，說道：好，老衲這就傳你棍法。\n");
            message_vision("$N將白象寺棍法的入門招式傳授給$n。\n", this_object(), ob);
            ob->improve_skill(skill, random(ob->query_attr("con")) + 1);
        }
        break;
    default:
        return 0;
    }

    do_chat(({
        "方丈說道：棍法之道﹐以守為攻﹐以柔克剛。\n",
        "方丈說道：你好生修煉﹐阿彌陀佛。\n",
    }));

    return 1;
}
