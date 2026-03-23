// vim: syntax=lpc
// Quest: 乞丐的往事 (quest/sanyen_beggar_jade_done)
// 乞丐原是沈家的老僕﹐沈家被抄後﹐他將主人的玉佩藏入枯井中。
// 玩家幫他從枯井中取回玉佩﹐乞丐感激贈予皮護腕。

#include <npc.h>

inherit F_VILLAGER;

void give_reward(object player);

void create()
{
    set_name("乞丐", ({"beggar"}));
    set_attr("str", 8);
    set_attr("dex", 10);
    set_attr("con", 8);
    set_attr("int", 10);
    set_attr("spi", 10);
    set_attr("wis", 10);
    set_race("human");
    set_class("commoner");
    set_level(3);
    set("age", 55);
    set("gender", "male");
    set("long",
        "一個衣衫襤褸的乞丐﹐蜷縮在暗巷的角落裡。他的眼神中帶著\n"
        "一絲不易察覺的愧疚﹐似乎心中藏著什麼往事。\n");
    set("chat_chance", 5);
    set("chat_msg", ({
        "乞丐伸出手：行行好，賞口飯吃吧。\n",
        "乞丐咳嗽了幾聲，縮了縮身子。\n",
        "乞丐低聲嘟囔著：沈家 ... 老爺 ... 對不起 ...\n",
    }));
    setup();
}

void init()
{
    ::init();
    if( is_fighting() || is_chatting() ) return;
    if( !userp(this_player()) ) return;

    if( this_player()->query("quest/sanyen_beggar_jade_done") ) {
        do_chat("乞丐看到你﹐感激地點點頭。\n");
        return;
    }

    if( this_player()->query_temp("pending/sanyen_beggar_jade") == 2 ) {
        do_chat("乞丐期盼地望著你﹕你 ... 找到那塊玉佩了嗎﹖\n");
        return;
    }
}

int accept_object(object player, object ob)
{
    if( !userp(player) ) return 0;
    if( player->query("quest/sanyen_beggar_jade_done") ) {
        do_chat("乞丐擺擺手﹕你已經幫過我了﹐我這輩子都不會忘記。\n");
        return 0;
    }

    if( player->query_temp("pending/sanyen_beggar_jade") != 2 ) return 0;

    if( ob->id("jade pendant") || ob->id("jade") || ob->id("pendant") ) {
        do_chat(({
            "乞丐接過玉佩﹐雙手顫抖著﹐老淚縱橫。\n",
            "乞丐哽咽道﹕這 ... 這就是沈老爺的玉佩 ... 我終於可以對得起他了 ...\n",
            "乞丐擦了擦眼淚﹐從懷裡掏出一樣東西。\n",
            "乞丐說道﹕這只護腕是沈老爺當年賞給我的﹐現在送給你﹐算是我的一點謝意。\n",
            (: give_reward, player :),
        }));
        return 1;
    }

    do_chat("乞丐搖搖頭﹕這 ... 這不是我要找的東西。\n");
    return 0;
}

void give_reward(object player)
{
    object wristguard;

    if( !player || environment(player) != environment() ) return;

    wristguard = new(__DIR__"obj/leather_wristguard");
    if( !wristguard->move(player) )
        wristguard->move(environment());

    player->set("quest/sanyen_beggar_jade_done", 1);
    player->gain_score("quest", 80);
}

void relay_say(object ob, string msg)
{
    if( !userp(ob) ) return;
    if( is_fighting() || is_chatting() ) return;
    if( ob->query("quest/sanyen_beggar_jade_done") ) return;

    if( !ob->query_temp("pending/sanyen_beggar_jade") ) {
        if( strsrch(msg, "沈家") >= 0 || strsrch(msg, "往事") >= 0
        ||  strsrch(msg, "怎麼了") >= 0 || strsrch(msg, "什麼事") >= 0
        ||  strsrch(msg, "幫") >= 0 ) {
            do_chat(({
                "乞丐渾身一震﹐抬起頭來望著你。\n",
                "乞丐低聲說道﹕你 ... 你問沈家﹖唉 ...\n",
                "乞丐嘆了口氣﹕我原是沈家的老僕﹐三十年前沈家被抄﹐老爺臨走前把一塊傳家玉佩交給我保管。\n",
                "乞丐說道﹕我怕被搜出來﹐就把玉佩藏到了村東邊的枯井裡 ...\n",
                "乞丐哀求道﹕好心人﹐我老了﹐腿腳不好﹐能不能幫我去枯井裡把玉佩找回來﹖\n",
            }));
            ob->set_temp("pending/sanyen_beggar_jade", 2);
            return;
        }
    }

    if( ob->query_temp("pending/sanyen_beggar_jade") == 2 ) {
        if( strsrch(msg, "枯井") >= 0 || strsrch(msg, "玉佩") >= 0
        ||  strsrch(msg, "井") >= 0 ) {
            do_chat("乞丐說道﹕枯井就在村東邊﹐你往東走就能看到了。玉佩應該還在井底。\n");
            return;
        }
    }
}
