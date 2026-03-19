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
    default:
        return 0;
    }

    do_chat(({
        "龍圖長老說道：銀針之術﹐在於識穴認經﹐下針精準。\n",
        "龍圖長老說道：好好修煉。\n",
    }));

    return 1;
}
