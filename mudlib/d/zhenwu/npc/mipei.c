// mipei.c - 米沛 Mi Pei, Zhenwu Military Camp Commander

#include <npc.h>

inherit F_SOLDIER;

void create()
{
    set_name("米沛", ({"mipei", "mi_pei"}));
    set_attr("str", 22);
    set_attr("con", 22);
    set_attr("dex", 18);
    set_attr("wis", 20);
    set_attr("cor", 22);
    set_race("human");
    set_class("soldier");
    set_level(50);

    set_skill("pike", 90);
    set_skill("tactic", 85);
    set_skill("dodge", 70);
    set_skill("parry", 75);
    set_skill("unarmed", 50);

    set("age", 45);
    set("gender", "male");
    set("attitude", "peaceful");
    set("long",
	"振武軍營統領米沛﹐身披鐵甲﹐腰懸令旗﹐面容剛毅﹐目光如\n"
	"鷹隼般銳利。一手持著長槍﹐氣宇軒昂﹐頗具將帥之風。\n");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_money("silver", 80);
    set_temp("apply/vision_of_ghost", 1);
}

void set_flag(object me)
{
    if( me && present(me, environment()) ) {
        if( me->query_class() != "commoner"
        ||  me->query("title") )
            return;
        me->set_temp("pending/mipei", 1);
    }
    else
        do_chat("米沛皺了皺眉﹐說道﹕人呢？\n");
}

int accept_apprentice(object me)
{
    if( is_chatting() ) return 0;
    if( me->query_temp("pending/mipei") ) return 1;
    if( me->query("title") ) {
        do_chat("米沛道﹕你已有門派﹐軍中不收外人。\n");
        return 0;
    }
    do_chat(({
        "米沛上下打量了你一番﹐說道﹕想從軍？\n",
        "米沛說道﹕振武軍不是兒戲﹐入了軍營就要聽令行事。\n",
        "米沛說道﹕你若真有決心﹐便再來報到。\n",
        (: set_flag, me :)
    }));
    return 0;
}

int init_apprentice(object me)
{
    if( me->query_class() != "commoner" ) {
        do_chat(({
            "米沛搖了搖頭﹐說道﹕你已有師門﹐軍中規矩﹐恕難收留。\n",
        }));
        return 1;
    }
    if( ::init_apprentice(me) ) {
        seteuid(getuid());
        me->set_class("soldier");
        me->set("title", "振武軍弟子");
        do_chat(({
            "米沛點了點頭﹐說道﹕好﹐從今日起你就是振武軍的一員了。\n",
            "米沛說道﹕軍中講究紀律﹐你先去熟悉營中規矩。\n",
            "米沛揮了揮手﹐說道﹕下去吧。\n"
        }));
    }
}

int acquire_skill(object ob, string skill)
{
    if( is_chatting() )
        return notify_fail("你最好等統領的話說完再插嘴。\n");
    if( !ob->is_apprentice_of(this_object()) ) return 0;

    switch(skill) {
    case "tactic":
        if( !ob->query_learn(skill) ) {
            say("米沛點了點頭，說道：好，為師傳你兵法韜略。\n");
            message_vision("$N將振武軍的戰陣之術傳授給$n。\n", this_object(), ob);
            ob->improve_skill(skill, random(ob->query_attr("wis")) + 1);
        }
        break;
    case "pike":
        if( !ob->query_learn(skill) ) {
            say("米沛點了點頭，說道：好，為師傳你槍法。\n");
            message_vision("$N將振武軍的槍法傳授給$n。\n", this_object(), ob);
            ob->improve_skill(skill, random(ob->query_attr("str")) + 1);
        }
        break;
    default:
        return 0;
    }

    do_chat(({
        "米沛說道：兵者﹐詭道也。用兵之妙﹐存乎一心。\n",
        "米沛說道：好好揣摩﹐日後自有用處。\n",
    }));

    return 1;
}
