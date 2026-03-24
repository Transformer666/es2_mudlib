// liuyi.c - 劉乙忘玄 Liu Yi, Kuxiao School Leader

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("劉乙忘玄", ({"liuyi", "liu_yi"}));
    set_attr("str", 22);
    set_attr("con", 20);
    set_attr("dex", 22);
    set_attr("int", 20);
    set_attr("cps", 22);
    set_race("human");
    set_class("warrior");
    set_level(60);

    set_skill("sword", 95);
    set_skill("dodge", 85);
    set_skill("parry", 90);
    set_skill("unarmed", 65);

    set("age", 48);
    set("attitude", "peaceful");
    set("long",
	"哭笑門掌門劉乙忘玄﹐面容半喜半悲﹐令人捉摸不透。身穿一\n"
	"件素白長袍﹐手中提著一柄無鞘的長劍﹐劍身寒光閃閃。\n");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_object( STOCK_WEAPON("longsword") )->wield();
    carry_money("silver", 40);
    set_temp("apply/vision_of_ghost", 1);
}

void set_flag(object me)
{
    if( me && present(me, environment()) ) {
        if( me->query_class() != "commoner"
        ||  me->query("title") )
            return;
        me->set_temp("pending/liuyi", 1);
    }
    else
        do_chat("劉乙忘玄半哭半笑的說道﹕人都走了﹐哈哈 ... 嗚嗚 ...。\n");
}

int accept_apprentice(object me)
{
    if( is_chatting() ) return 0;
    if( me->query_temp("pending/liuyi") ) return 1;
    if( me->query("title") ) {
        do_chat("劉乙忘玄道﹕你已有師門﹐別來煩我。\n");
        return 0;
    }
    do_chat(({
        "劉乙忘玄忽哭忽笑﹐說道﹕拜我為師？哈哈 ... 嗚嗚 ...\n",
        "劉乙忘玄說道﹕哭笑門的功夫﹐可不是人人學得來的。\n",
        "劉乙忘玄說道﹕你若不怕﹐便再來找我。\n",
        (: set_flag, me :)
    }));
    return 0;
}

int init_apprentice(object me)
{
    if( me->query_class() != "commoner" ) {
        do_chat(({
            "劉乙忘玄搖了搖頭﹐半哭半笑道﹕你已有師門了﹐可惜可惜。\n",
        }));
        return 1;
    }
    if( ::init_apprentice(me) ) {
        seteuid(getuid());
        me->set_class("warrior");
        me->set("title", "哭笑門弟子");
        do_chat(({
            "劉乙忘玄大笑道﹕好﹐從今日起你就是哭笑門弟子了！\n",
            "劉乙忘玄忽然又哭了起來﹐說道﹕可憐啊﹐又多了一個受苦的 ...\n",
            "劉乙忘玄說道﹕去吧去吧﹐哈哈 ... 嗚嗚 ...\n"
        }));
    }
}

void relay_say(object me, string msg)
{
    if( is_fighting() || is_chatting() ) return;

    if( strsrch(msg, "梅影風") >= 0 || strsrch(msg, "冷梅") >= 0
    ||  strsrch(msg, "藥") >= 0 ) {
        do_chat(({
            "劉乙忘玄臉上的笑容忽然僵住﹐隨即又恢復如常。\n",
            "劉乙忘玄半哭半笑道﹕梅影風的事﹖哈哈 ... 嗚嗚 ... 我怎麼會知道。\n",
            "劉乙忘玄說道﹕你去問別人吧﹐別來煩我。\n",
        }));
        return;
    }

    if( strsrch(msg, "魚鐵山") >= 0 || strsrch(msg, "雪吟") >= 0 ) {
        do_chat("劉乙忘玄眼神一閃﹐忽哭忽笑道﹕魚鐵山﹖不熟不熟﹐哈哈 ... 嗚嗚 ...\n");
        return;
    }

    if( strsrch(msg, "陰謀") >= 0 || strsrch(msg, "勾結") >= 0 ) {
        do_chat(({
            "劉乙忘玄的笑容驟然收斂﹐目光冰冷地看了你一眼。\n",
            "劉乙忘玄說道﹕什麼陰謀﹖你在說什麼﹖\n",
            "劉乙忘玄忽然又笑了起來﹐說道﹕哈哈 ... 嗚嗚 ... 年輕人﹐話別亂說。\n",
        }));
        return;
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
            say("劉乙忘玄點了點頭，忽哭忽笑道：好，為師傳你劍法。\n");
            message_vision("$N將哭笑門的劍法傳授給$n。\n", this_object(), ob);
            ob->improve_skill(skill, random(ob->query_attr("dex")) + 1);
        }
        break;
    default:
        return 0;
    }

    do_chat(({
        "劉乙忘玄說道：劍法之妙﹐亦哭亦笑﹐捉摸不定。\n",
        "劉乙忘玄說道：去吧﹐好好練。\n",
    }));

    return 1;
}
