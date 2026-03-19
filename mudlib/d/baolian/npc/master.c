#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("寶蓮方丈", ({"master", "baolian_abbot", "fangzhang"}));
    set_attr("str", 20);
    set_attr("con", 24);
    set_attr("dex", 18);
    set_attr("wis", 26);
    set_attr("spi", 24);
    set_race("human");
    set_class("monk");
    set_level(55);

    set_skill("staff", 90);
    set_skill("dodge", 75);
    set_skill("parry", 80);
    set_skill("unarmed", 70);

    set("age", 68);
    set("attitude", "peaceful");
    set("long",
        "寶蓮寺方丈﹐面容慈祥﹐身穿金色袈裟﹐手持一根禪杖﹐雙\n"
        "目半閉﹐似在入定﹐渾身散發著一股慈悲祥和的氣息。\n");
    setup();
    carry_object(__DIR__"obj/zen_staff")->wield();
    carry_object(__DIR__"obj/monk_robe")->wear();
    carry_money("coin", 100);
}

void set_flag(object me)
{
    if( me && present(me, environment()) ) {
        if( me->query_class() != "commoner"
        ||  me->query("title") )
            return;
        me->set_temp("pending/baolian_abbot", 1);
    }
    else
        do_chat("方丈雙手合十﹐說道﹕阿彌陀佛﹐施主已去。\n");
}

int accept_apprentice(object me)
{
    if( is_chatting() ) return 0;
    if( me->query_temp("pending/baolian_abbot") ) return 1;
    if( me->query("title") ) {
        do_chat("方丈說道﹕施主已有師門﹐緣分不在此處。\n");
        return 0;
    }
    do_chat(({
        "方丈微微睜開雙眼﹐說道﹕施主想皈依佛門？\n",
        "方丈說道﹕寶蓮寺以慈悲為懷﹐濟世救人為本。\n",
        "方丈說道﹕施主若真有佛緣﹐便再來找老衲。\n",
        (: set_flag, me :)
    }));
    return 0;
}

int init_apprentice(object me)
{
    if( me->query_class() != "commoner" ) {
        do_chat(({
            "方丈搖了搖頭﹐說道﹕施主既入別門﹐不宜再入佛門。\n",
        }));
        return 1;
    }
    if( ::init_apprentice(me) ) {
        seteuid(getuid());
        me->set_class("monk");
        me->set("title", "寶蓮寺弟子");
        do_chat(({
            "方丈點了點頭﹐說道﹕善哉善哉﹐從今日起你便是寶蓮寺弟子了。\n",
            "方丈說道﹕佛門弟子﹐當以慈悲為懷﹐救苦救難。\n",
            "方丈說道﹕去吧﹐好生修行﹐阿彌陀佛。\n"
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
            say("方丈點了點頭，說道：好，老衲傳你棍法。\n");
            message_vision("$N將寶蓮寺的棍法傳授給$n。\n", this_object(), ob);
            ob->improve_skill(skill, random(ob->query_attr("con")) + 1);
        }
        break;
    default:
        return 0;
    }

    do_chat(({
        "方丈說道：棍法之道﹐以守護為本﹐以慈悲為根。\n",
        "方丈說道：你好生修煉﹐阿彌陀佛。\n",
    }));

    return 1;
}
