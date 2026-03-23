// vim: syntax=lpc
// Quest hint: 提示玩家注意老乞婆的身世

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("村長", ({"village elder", "village_elder", "elder"}));
    set_attr("str", 12);
    set_attr("dex", 10);
    set_attr("con", 14);
    set_attr("int", 18);
    set_attr("spi", 16);
    set_race("human");
    set_class("commoner");
    set_level(15);

    set("age", 60);
    set("gender", "male");
    set("long",
        "村長是個六十多歲的老人，面容和善，在村中頗有威望。他坐在村口\n"
        "的大樹下，搖著蒲扇，看著來來往往的人們。\n");
    set("chat_chance", 3);
    set("chat_msg", ({
        "村長搖著蒲扇，慢悠悠地說道：年輕人，來坐坐吧。\n",
        "村長說道：這小村子雖然不大，但勝在安寧。\n",
    }));
    setup();
    carry_object(STOCK_ARMOR("cloth"))->wear();
}

void relay_say(object ob, string msg)
{
    if( !userp(ob) ) return;
    if( is_fighting() || is_chatting() ) return;

    if( strsrch(msg, "乞婆") >= 0 || strsrch(msg, "乞丐") >= 0
    ||  strsrch(msg, "老婆婆") >= 0 || strsrch(msg, "beggar") >= 0 ) {
        do_chat(({
            "村長搖了搖頭﹐說道﹕你說南邊農田那個老婆子啊 ...\n",
            "村長說道﹕她大概一個月前才到村子的﹐不知道從哪裡來。\n",
            "村長壓低聲音說道﹕不過我瞧她的氣度﹐不像是尋常的乞丐。\n",
            "村長說道﹕你若有心﹐給她弄些吃的﹐也許她會跟你說說自己的事。\n",
        }));
        return;
    }

    if( strsrch(msg, "村子") >= 0 || strsrch(msg, "天寒") >= 0 ) {
        do_chat(({
            "村長說道﹕天寒村是個小地方﹐前些年鬧過匪患﹐幸好後來太平了。\n",
            "村長說道﹕如今村子裡就剩這些老人小孩﹐年輕人都往城裡跑了。\n",
        }));
        return;
    }
}
