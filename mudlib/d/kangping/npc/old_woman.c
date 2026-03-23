// vim: syntax=lpc
// NPC: /d/kangping/npc/old_woman.c
// Quest: 古井玉佩 (well_jade) - 幫洗衣婦找回掉入井中的玉佩

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("洗衣婦", ({"old woman", "woman"}));
    set_attr("str", 8);
    set_attr("dex", 10);
    set_attr("con", 10);
    set_attr("int", 10);
    set_attr("spi", 12);
    set_attr("wis", 12);
    set_race("human");
    set_class("commoner");
    set_level(3);
    set("age", 50);
    set("gender", "female");
    set("long", "一個在井邊洗衣的婦人，一邊搓洗著衣物一邊和人閒聊。\n");
    set("chat_chance", 5);
    set("chat_msg", ({
        "洗衣婦低聲說道：你聽說了嗎？隔壁老王家的兒子考上武舉了！\n",
        "洗衣婦嘆了口氣：這天越來越冷了，衣服都不容易乾。\n",
        "洗衣婦抬頭張望了一下，又繼續搓洗衣物。\n",
    }));
    setup();
    carry_object("/obj/area/obj/cloth")->wear();
}

private void give_reward(object player)
{
    object money;

    if( !player || environment(player) != environment() ) return;

    money = new("/obj/money/silver");
    money->set_amount(1);
    if( !money->move(player) )
        money->move(environment());

    player->set("quest/well_jade_done", 1);
    player->gain_score("quest", 60);
}

void init()
{
    ::init();
    if( is_fighting() || is_chatting() ) return;
    if( !userp(this_player()) ) return;

    if( this_player()->query("quest/well_jade_done") )
        return;

    if( this_player()->query_temp("pending/well_jade") == 2 ) {
        do_chat("洗衣婦抬頭看了看你﹐眼睛一亮﹐說道：你是不是找到什麼了﹖\n");
        return;
    }
}

int accept_object(object ob, object item)
{
    if( !userp(ob) ) return 0;
    if( is_chatting() ) return 0;
    if( ob->query("quest/well_jade_done") ) return 0;

    if( ob->query_temp("pending/well_jade") == 2
    &&  item->query("id") == "jade pendant" ) {
        do_chat(({
            "洗衣婦接過玉佩﹐仔細端詳了一番﹐喜極而泣。\n",
            "洗衣婦說道：就是這塊玉佩﹗這是我過世的丈夫留給我的 ...\n",
            "洗衣婦擦了擦眼淚﹐說道：真是太感謝你了﹐好心人。\n",
            "洗衣婦說道：這點銀兩不成敬意﹐請你務必收下。\n",
            (: give_reward, ob :),
        }));
        destruct(item);
        return 1;
    }
    return 0;
}

void relay_say(object ob, string msg)
{
    if( !userp(ob) ) return;
    if( is_fighting() || is_chatting() ) return;

    if( ob->query("quest/well_jade_done") ) {
        if( strsrch(msg, "玉佩") >= 0 || strsrch(msg, "佩") >= 0 ) {
            do_chat("洗衣婦感激地說道：多虧了你幫我找回玉佩﹐我會一直記得你的恩情。\n");
        }
        return;
    }

    int stage = ob->query_temp("pending/well_jade");

    if( !stage || stage == 0 ) {
        if( strsrch(msg, "幫") >= 0 || strsrch(msg, "忙") >= 0
        ||  strsrch(msg, "玉") >= 0 || strsrch(msg, "佩") >= 0
        ||  strsrch(msg, "掉") >= 0 || strsrch(msg, "井") >= 0 ) {
            do_chat(({
                "洗衣婦嘆了口氣﹐說道：唉﹐說來慚愧 ...\n",
                "洗衣婦說道：前幾天我在井邊洗衣服的時候﹐不小心把玉佩掉到井裡去了。\n",
                "洗衣婦說道：那是我過世的丈夫留下的唯一念想 ...\n",
                "洗衣婦眼眶泛紅﹐說道：你要是能幫我從井裡撈上來﹐我感激不盡。\n",
                "洗衣婦說道：你試試搜尋一下那口井吧﹐也許能找到。\n",
            }));
            ob->set_temp("pending/well_jade", 1);
            return;
        }
    }

    if( stage == 1 ) {
        if( strsrch(msg, "井") >= 0 || strsrch(msg, "找") >= 0
        ||  strsrch(msg, "哪") >= 0 || strsrch(msg, "怎") >= 0 ) {
            do_chat("洗衣婦指了指旁邊的古井﹐說道：就是這口井﹐你仔細找找看。\n");
            return;
        }
    }

    if( stage == 2 ) {
        if( strsrch(msg, "玉") >= 0 || strsrch(msg, "找") >= 0
        ||  strsrch(msg, "到") >= 0 ) {
            do_chat("洗衣婦急切地說道：你找到了﹖快給我看看﹗\n");
            return;
        }
    }
}
