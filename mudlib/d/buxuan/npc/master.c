#include <npc.h>

inherit F_SCHOLAR;

void create()
{
    set_name("駱易", ({"luoyi", "luo_yi"}));
    set_attr("str", 18);
    set_attr("con", 18);
    set_attr("dex", 22);
    set_attr("int", 26);
    set_attr("wis", 24);
    set_attr("spi", 20);
    set_race("human");
    set_class("scholar");
    set_level(60);

    set_skill("sword", 85);
    set_skill("three rotations", 90);
    set_skill("dodge", 80);
    set_skill("parry", 75);

    set("age", 45);
    set("attitude", "peaceful");
    set("long",
        "駱易﹐沐華居主人﹐面容儒雅﹐目光深邃﹐身穿一件月白色的\n"
        "長衫﹐腰間佩著一柄文士劍。舉手投足間盡顯書生風度﹐但眼神\n"
        "中透著一股不凡的銳氣。\n");
    setup();
    carry_object(__DIR__"obj/wind_blade")->wield();
    carry_object(__DIR__"obj/buxuan_cloth")->wear();
    carry_money("silver", 60);
    set_temp("apply/vision_of_ghost", 1);
}

void set_flag(object me)
{
    if( me && present(me, environment()) ) {
        if( me->query_class() != "commoner"
        ||  me->query("title") )
            return;
        me->set_temp("pending/luoyi", 1);
    }
    else
        do_chat("駱易搖了搖頭﹐說道﹕人走了。\n");
}

int accept_apprentice(object me)
{
    if( is_chatting() ) return 0;
    if( me->query_temp("pending/luoyi") ) return 1;
    if( me->query("title") ) {
        do_chat("駱易微微搖頭道﹕你已有師門﹐不便再收。\n");
        return 0;
    }
    do_chat(({
        "駱易放下手中書卷﹐說道﹕想拜入步玄門下？\n",
        "駱易說道﹕步玄一派﹐以文入武﹐文武兼修﹐非好學之人不收。\n",
        "駱易微微一笑﹐說道﹕你若真有向學之心﹐便再來找我。\n",
        (: set_flag, me :)
    }));
    return 0;
}

int init_apprentice(object me)
{
    if( me->query_class() != "commoner" ) {
        do_chat(({
            "駱易搖了搖頭﹐說道﹕你既有師門﹐不宜再入步玄。\n",
        }));
        return 1;
    }
    if( ::init_apprentice(me) ) {
        seteuid(getuid());
        me->set_class("scholar");
        me->set("title", "步玄派弟子");
        do_chat(({
            "駱易點了點頭﹐說道﹕好﹐從今日起你便是步玄派門生了。\n",
            "駱易說道﹕步玄之道﹐以文養武﹐以武證文﹐你需文武兼修。\n",
            "駱易說道﹕去吧﹐先去讀幾本書。\n"
        }));
    }
}

int acquire_skill(object ob, string skill)
{
    if( is_chatting() )
        return notify_fail("你最好等駱先生的話說完再插嘴。\n");
    if( !ob->is_apprentice_of(this_object()) ) return 0;

    switch(skill) {
    case "three rotations":
        if( !ob->query_learn(skill) ) {
            say("駱易點了點頭，說道：好，為師傳你三轉劍法。\n");
            message_vision("$N將步玄派的三轉劍法傳授給$n。\n", this_object(), ob);
            ob->improve_skill(skill, random(ob->query_attr("int")) + 1);
        }
        break;
    default:
        return 0;
    }

    do_chat(({
        "駱易說道：三轉劍法﹐一轉攻﹐二轉守﹐三轉攻守合一。\n",
        "駱易說道：好好修煉。\n",
    }));

    return 1;
}
