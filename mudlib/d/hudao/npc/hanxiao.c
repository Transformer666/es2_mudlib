// hanxiao.c - 韓笑 Han Xiao, Tiger Blade School Leader

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("韓笑", ({"hanxiao", "han_xiao"}));
    set_attr("str", 25);
    set_attr("con", 22);
    set_attr("dex", 22);
    set_attr("cor", 20);
    set_race("human");
    set_class("warrior");
    set_level(60);

    set_skill("blade", 100);
    set_skill("tiger blade", 95);
    set_skill("dodge", 85);
    set_skill("parry", 80);
    set_skill("unarmed", 60);

    set("age", 42);
    set("attitude", "peaceful");
    set("long",
	"虎刀門掌門人韓笑﹐身材魁梧﹐面帶微笑﹐但笑容中透著一股\n"
	"凜然不可犯的殺氣。腰間佩著一把虎紋大刀﹐刀柄上纏著虎皮。\n");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_money("silver", 50);
    set_temp("apply/vision_of_ghost", 1);
}

void set_flag(object me)
{
    if( me && present(me, environment()) ) {
        if( me->query_class() != "commoner"
        ||  me->query("title") )
            return;
        me->set_temp("pending/hanxiao", 1);
    }
    else
        do_chat("韓笑哈哈一笑﹐說道﹕人都跑了。\n");
}

int accept_apprentice(object me)
{
    if( is_chatting() ) return 0;
    if( me->query_temp("pending/hanxiao") ) return 1;
    if( me->query("title") ) {
        do_chat("韓笑道﹕你已有師門﹐莫來攪局。\n");
        return 0;
    }
    do_chat(({
        "韓笑哈哈大笑﹐說道﹕想學我虎刀門的刀法？\n",
        "韓笑收了笑容﹐說道﹕虎刀門的刀﹐可不是隨便什麼人都拿得動的。\n",
        "韓笑說道﹕你若真有心﹐便再來找我。\n",
        (: set_flag, me :)
    }));
    return 0;
}

int init_apprentice(object me)
{
    if( me->query_class() != "commoner" ) {
        do_chat(({
            "韓笑搖頭道﹕你既入別派﹐就別想腳踏兩條船。\n",
        }));
        return 1;
    }
    if( ::init_apprentice(me) ) {
        seteuid(getuid());
        me->set_class("warrior");
        me->set("title", "虎刀門弟子");
        do_chat(({
            "韓笑拍了拍你的肩膀﹐說道﹕好小子﹐從今天起你就是虎刀門的人了。\n",
            "韓笑說道﹕虎刀門以刀法聞名﹐你先去練好基本功。\n",
            "韓笑說道﹕去吧﹐別給虎刀門丟臉。\n"
        }));
    }
}

void relay_say(object me, string msg)
{
    if( is_fighting() || is_chatting() ) return;

    if( strsrch(msg, "梅影風") >= 0 || strsrch(msg, "冷梅") >= 0 ) {
        if( me->query("quest/meiyingfeng_medicine_step1") )
            do_chat(({
                "韓笑收斂了笑容﹐說道﹕梅莊主的夫人病了﹖這事我倒是有所耳聞。\n",
                "韓笑說道﹕黑風嶺我去過幾回﹐那裡確實有些珍稀藥草。\n",
                "韓笑壓低聲音﹐說道﹕不過你要小心劉乙忘玄和魚鐵山﹐他們最近很不對勁。\n",
            }));
        else
            do_chat("韓笑哈哈一笑﹐說道﹕梅影風﹖她劍法倒是不錯﹐可惜太冷了些。\n");
        return;
    }

    if( strsrch(msg, "劉乙") >= 0 || strsrch(msg, "魚鐵山") >= 0 ) {
        do_chat(({
            "韓笑的笑容淡了幾分﹐說道﹕那兩個人 ... 最近跟他們走得太近可不是好事。\n",
            "韓笑說道﹕我虎刀門向來光明磊落﹐不屑與人暗中勾結。\n",
        }));
        return;
    }

    if( strsrch(msg, "黑風") >= 0 ) {
        do_chat("韓笑說道﹕黑風嶺山高路險﹐多的是毒蟲猛獸﹐沒點本事別去。\n");
        return;
    }
}

int acquire_skill(object ob, string skill)
{
    if( is_chatting() )
        return notify_fail("你最好等他的話說完再插嘴。\n");
    if( !ob->is_apprentice_of(this_object()) ) return 0;

    switch(skill) {
    case "tiger blade":
        if( !ob->query_learn(skill) ) {
            say("韓笑點了點頭，說道：好，為師傳你虎刀門刀法。\n");
            message_vision("$N將虎刀門的虎嘯刀法傳授給$n。\n", this_object(), ob);
            ob->improve_skill(skill, random(ob->query_attr("str")) + 1);
        }
        break;
    default:
        return 0;
    }

    do_chat(({
        "韓笑說道：刀法之要﹐在於氣勢﹐一刀揮出﹐猛若下山之虎。\n",
        "韓笑說道：好好練吧。\n",
    }));

    return 1;
}
