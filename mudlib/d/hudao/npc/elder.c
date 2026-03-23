// vim: syntax=lpc
// Quest: 古井藏刀 (elder_well_blade)
// Flow: talk to elder about old master/blade/secret -> elder tells story
//       -> search well in garden -> find old blade
//       -> give to elder -> elder rewards player

#include <npc.h>

inherit F_FIGHTER;

void give_reward(object player);

void create()
{
    set_name("長老", ({"elder", "zhang_lao"}));
    set_race("human");
    set_class("warrior");
    set_level(35);
    set_attr("str", 18);
    set_attr("con", 17);
    set_attr("dex", 16);
    set_skill("blade", 70);
    set_skill("dodge", 55);
    set_skill("parry", 50);
    set_skill("unarmed", 40);
    set("age", 55);
    set("gender", "male");
    set("long",
	"一位飽經風霜的長老坐在老榕樹下﹐悠然地品著茶。他的雙手厚\n"
	"實粗糙﹐掌心佈滿了數十年練刀磨出的老繭。雖然看似閒適﹐但眼\n"
	"神中卻透著一股銳利的警覺。\n");
    set("chat_chance", 1);
    set("chat_msg", ({
	"長老端起茶杯輕啜一口﹐緩緩說道﹕刀法之道﹐重在一個「勢」字。\n",
	"長老望著遠處﹐感慨道﹕想當年我跟老掌門學刀﹐一把木刀劈了三千下才算入門。\n",
	"長老放下茶杯﹐說道﹕如今的年輕人﹐少了幾分吃苦的勁頭啊。\n",
    }));
    setup();
    carry_object(STOCK_ARMOR("cloth"))->wear();
    carry_object(STOCK_WEAPON("blade"))->wield();
    carry_money("coin", 100);
}

void init()
{
    ::init();
    if( is_fighting() || is_chatting() ) return;
    if( !userp(this_player()) ) return;

    if( this_player()->query("quest/elder_well_blade_done") )
        return;

    if( this_player()->query_temp("pending/elder_well_blade") == 2 )
        do_chat("長老看了你一眼﹕找到了嗎﹖去井裡找找看吧。\n");
}

int accept_object(object who, object ob)
{
    if( !ob->id("old_blade") && !ob->id("old blade") ) return 0;

    if( who->query("quest/elder_well_blade_done") ) {
        do_chat("長老搖搖頭﹕這把刀你留著吧﹐老夫不需要了。\n");
        return 0;
    }
    if( !who->query_temp("pending/elder_well_blade") ) return 0;

    do_chat(({
        "長老接過斷刀﹐雙手微微顫抖。\n",
        "長老用衣袖擦去刀身上的鏽跡﹐露出虎頭浮雕﹐眼眶泛紅。\n",
        "長老嘆道﹕果然是老掌門的「虎嘯」……跟了他大半輩子。\n",
        "長老說道﹕老掌門臨終前把這把刀藏起來﹐說有緣人自會找到。\n",
        "長老深吸一口氣﹐把斷刀放回你手中﹐說道﹕你既然找到了﹐就是有緣。\n",
        "長老說道﹕這把刀雖然殘了﹐但刀意猶存﹐練刀時握著它﹐自有體悟。\n",
        (: give_reward, who :),
    }));
    return 1;
}

void give_reward(object player)
{
    if( !player || !present(player, environment()) ) return;
    if( player->query("quest/elder_well_blade_done") ) return;

    player->set("quest/elder_well_blade_done", 1);
    player->delete_temp("pending/elder_well_blade");
    player->gain_score("quest", 80);
    player->carry_money("silver", 2);
    tell_object(player, "( 長老塞了些碎銀給你﹐算是一點心意 )\n");
}

void relay_say(object ob, string msg)
{
    if( !userp(ob) ) return;
    if( is_fighting() || is_chatting() ) return;

    if( strsrch(msg, "老掌門") >= 0 || strsrch(msg, "秘密") >= 0
    ||  strsrch(msg, "練功") >= 0 || strsrch(msg, "古井") >= 0
    ||  strsrch(msg, "藏刀") >= 0 || strsrch(msg, "hidden") >= 0
    ||  strsrch(msg, "虎嘯") >= 0 ) {
        if( ob->query("quest/elder_well_blade_done") ) {
            do_chat("長老微微一笑﹕那把虎嘯斷刀﹐好好珍惜吧。\n");
            return;
        }
        if( ob->query_temp("pending/elder_well_blade") ) {
            do_chat("長老指了指院中的古井﹕去搜搜那口井吧﹐老掌門愛在那邊練功。\n");
            return;
        }
        do_chat(({
            "長老放下茶杯﹐沉默了片刻﹐緩緩說道﹕你問老掌門的事？\n",
            "長老嘆道﹕老掌門當年威震江湖﹐一把「虎嘯」大刀斬遍天下無敵手。\n",
            "長老說道﹕後來他年紀大了﹐知道自己時日無多﹐把那把刀藏了起來。\n",
            "長老望著院中的古井﹕老掌門喜歡在那口井邊練功……也許 ...\n",
            "長老欲言又止﹐搖搖頭﹕也許只是老夫的猜測罷了。你若好奇﹐去看看也無妨。\n",
        }));
        ob->set_temp("pending/elder_well_blade", 2);
        return;
    }

    if( strsrch(msg, "刀法") >= 0 || strsrch(msg, "虎刀") >= 0 ) {
        do_chat(({
            "長老說道﹕虎刀門的刀法﹐講究勢大力沉﹐一刀揮出﹐有如猛虎下山。\n",
            "長老說道﹕想當年老掌門的虎嘯刀法﹐那才叫厲害﹐一人一刀可戰十人。\n",
        }));
        return;
    }
}
