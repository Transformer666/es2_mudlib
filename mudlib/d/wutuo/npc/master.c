#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("武陀香主", ({"master", "wutuo_master"}));
    set_attr("str", 16);
    set_attr("con", 18);
    set_attr("dex", 22);
    set_attr("int", 24);
    set_attr("wis", 26);
    set_attr("spi", 20);
    set_race("human");
    set_class("alchemist");
    set_level(50);

    set_skill("needle", 90);
    set_skill("five defeat needle", 85);
    set_skill("dodge", 65);
    set_skill("parry", 60);

    set("age", 55);
    set("attitude", "peaceful");
    set("long",
        "武陀香主﹐面容清瘦﹐眼神銳利﹐手指纖長靈活。身穿一件\n"
        "青色長袍﹐腰間掛著一個精緻的針灸箱。\n");
    setup();
    carry_object(__DIR__"obj/gold_needle")->wield();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_money("silver", 50);
}

void set_flag(object me)
{
    if( me && present(me, environment()) ) {
        if( me->query_class() != "commoner"
        ||  me->query("title") )
            return;
        me->set_temp("pending/wutuo_master", 1);
    }
    else
        do_chat("武陀香主搖了搖頭﹐說道﹕人走了。\n");
}

int accept_apprentice(object me)
{
    if( is_chatting() ) return 0;
    if( me->query_temp("pending/wutuo_master") ) return 1;
    if( me->query("title") ) {
        do_chat("武陀香主搖頭道﹕你已有師門﹐不宜再學針術。\n");
        return 0;
    }
    do_chat(({
        "武陀香主看了看你的手﹐說道﹕想學針灸之術？\n",
        "武陀香主說道﹕針灸一道﹐講究認穴精準﹐手法穩健。\n",
        "武陀香主說道﹕你若真有心﹐便再來找我。\n",
        (: set_flag, me :)
    }));
    return 0;
}

int init_apprentice(object me)
{
    if( me->query_class() != "commoner" ) {
        do_chat(({
            "武陀香主搖了搖頭﹐說道﹕你既入別門﹐恕難收留。\n",
        }));
        return 1;
    }
    if( ::init_apprentice(me) ) {
        seteuid(getuid());
        me->set_class("alchemist");
        me->set("title", "武陀弟子");
        do_chat(({
            "武陀香主點了點頭﹐說道﹕好﹐從今日起你便是武陀弟子了。\n",
            "武陀香主說道﹕針灸之術﹐先學認穴﹐再學運針。\n",
            "武陀香主說道﹕去吧﹐先把經絡穴位圖背熟。\n"
        }));
    }
}

int acquire_skill(object ob, string skill)
{
    if( is_chatting() )
        return notify_fail("你最好等香主的話說完再插嘴。\n");
    if( !ob->is_apprentice_of(this_object()) ) return 0;

    switch(skill) {
    case "five defeat needle":
        if( !ob->query_learn(skill) ) {
            say("武陀香主點了點頭，說道：好，為師傳你五敗針法。\n");
            message_vision("$N將武陀的五敗針法傳授給$n。\n", this_object(), ob);
            ob->improve_skill(skill, random(ob->query_attr("wis")) + 1);
        }
        break;
    default:
        return 0;
    }

    do_chat(({
        "武陀香主說道：五敗針法﹐一針破氣﹐二針斷脈﹐三針封穴﹐四針散功﹐五針奪命。\n",
        "武陀香主說道：你好生修煉。\n",
    }));

    return 1;
}
