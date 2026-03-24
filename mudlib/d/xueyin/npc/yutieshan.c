// yutieshan.c - 魚鐵山 Yu Tieshan, Xueyin Manor Leader

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("魚鐵山", ({"master", "yutieshan", "yu_tieshan"}));
    set_attr("str", 24);
    set_attr("con", 24);
    set_attr("dex", 20);
    set_attr("spi", 22);
    set_race("human");
    set_class("warrior");
    set_level(60);

    set_skill("sword", 95);
    set_skill("dodge", 80);
    set_skill("parry", 85);
    set_skill("unarmed", 70);

    set("age", 52);
    set("attitude", "peaceful");
    set("long",
	"雪吟莊莊主魚鐵山﹐身材高大壯碩﹐面如鐵鑄﹐濃眉大眼﹐一\n"
	"雙虎目透著精光。身穿一件黑色勁裝﹐腰間佩著一把闊劍。\n");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_object( STOCK_WEAPON("longsword") )->wield();
    carry_money("silver", 60);
    set_temp("apply/vision_of_ghost", 1);
}

void set_flag(object me)
{
    if( me && present(me, environment()) ) {
        if( me->query_class() != "commoner"
        ||  me->query("title") )
            return;
        me->set_temp("pending/yutieshan", 1);
    }
    else
        do_chat("魚鐵山哼了一聲﹐說道﹕人呢？\n");
}

int accept_apprentice(object me)
{
    if( is_chatting() ) return 0;
    if( me->query_temp("pending/yutieshan") ) return 1;
    if( me->query("title") ) {
        do_chat("魚鐵山道﹕你已有師門﹐莫來多事。\n");
        return 0;
    }
    do_chat(({
        "魚鐵山上下打量了你一番﹐說道﹕想入我雪吟莊？\n",
        "魚鐵山說道﹕我雪吟莊向來只收有骨氣的人。\n",
        "魚鐵山說道﹕你若真有膽量﹐便再來找我。\n",
        (: set_flag, me :)
    }));
    return 0;
}

int init_apprentice(object me)
{
    if( me->query_class() != "commoner" ) {
        do_chat(({
            "魚鐵山搖了搖頭﹐說道﹕你既入別門﹐就別再來了。\n",
        }));
        return 1;
    }
    if( ::init_apprentice(me) ) {
        seteuid(getuid());
        me->set_class("warrior");
        me->set("title", "雪吟莊弟子");
        do_chat(({
            "魚鐵山拍了拍你的肩膀﹐說道﹕好﹐從今日起你便是雪吟莊弟子了。\n",
            "魚鐵山說道﹕雪吟莊的劍法﹐講究剛猛直取﹐你先把基本功練好。\n",
            "魚鐵山說道﹕去吧。\n"
        }));
    }
}

void relay_say(object me, string msg)
{
    if( is_fighting() || is_chatting() ) return;

    if( strsrch(msg, "梅影風") >= 0 || strsrch(msg, "冷梅") >= 0
    ||  strsrch(msg, "藥") >= 0 ) {
        do_chat(({
            "魚鐵山臉色微微一沉。\n",
            "魚鐵山冷冷道﹕梅影風的家事﹐與我雪吟莊何干﹖\n",
            "魚鐵山說道﹕你若無事﹐便請回吧。\n",
        }));
        return;
    }

    if( strsrch(msg, "劉乙") >= 0 || strsrch(msg, "哭笑") >= 0 ) {
        do_chat("魚鐵山哼了一聲﹐說道﹕劉乙忘玄那個瘋子﹐提他做什麼。\n");
        return;
    }

    if( strsrch(msg, "陰謀") >= 0 || strsrch(msg, "勾結") >= 0 ) {
        do_chat(({
            "魚鐵山猛地站起身來﹐一股殺氣從身上散發出來。\n",
            "魚鐵山怒道﹕你在含沙射影什麼﹗\n",
            "魚鐵山深吸一口氣﹐坐了回去﹐冷冷道﹕出去。\n",
        }));
        return;
    }
}

int acquire_skill(object ob, string skill)
{
    if( is_chatting() )
        return notify_fail("你最好等莊主的話說完再插嘴。\n");
    if( !ob->is_apprentice_of(this_object()) ) return 0;

    switch(skill) {
    case "sword":
        if( !ob->query_learn(skill) ) {
            say("魚鐵山點了點頭，說道：好，為師傳你劍法。\n");
            message_vision("$N將雪吟莊的劍法傳授給$n。\n", this_object(), ob);
            ob->improve_skill(skill, random(ob->query_attr("str")) + 1);
        }
        break;
    default:
        return 0;
    }

    do_chat(({
        "魚鐵山說道：劍法之要﹐貴在剛猛﹐一劍劈出﹐氣吞山河。\n",
        "魚鐵山說道：去好好練吧。\n",
    }));

    return 1;
}
