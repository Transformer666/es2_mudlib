// meiyingfeng.c - 梅影風 Mei Yingfeng, Boss NPC

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("梅影風", ({"meiyingfeng", "mei_yingfeng"}));
    set_attr("str", 22);
    set_attr("con", 20);
    set_attr("dex", 24);
    set_attr("spi", 20);
    set_race("human");
    set_class("warrior");
    set_level(60);

    set_skill("sword", 100);
    set_skill("dodge", 90);
    set_skill("parry", 85);
    set_skill("unarmed", 55);

    set("age", 38);
    set("long",
	"一個身穿白衣的女子﹐容貌清麗絕俗﹐如梅花般傲然獨立。手\n"
	"中握著一柄通體潔白的長劍﹐劍上似有寒霜凝結。\n");
    set("attitude", "peaceful");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_object( STOCK_WEAPON("longsword") )->wield();
    carry_money("silver", 45);
    set_temp("apply/vision_of_ghost", 1);
}

void set_flag(object me)
{
    if( me && present(me, environment()) ) {
        if( me->query_class() != "commoner"
        ||  me->query("title") )
            return;
        me->set_temp("pending/meiyingfeng", 1);
    }
    else
        do_chat("梅影風輕嘆一聲﹐說道﹕人已走了 ...。\n");
}

int accept_apprentice(object me)
{
    if( is_chatting() ) return 0;
    if( me->query_temp("pending/meiyingfeng") ) return 1;
    if( me->query("title") ) {
        do_chat("梅影風冷冷道﹕你已有師門﹐莫來糾纏。\n");
        return 0;
    }
    do_chat(({
        "梅影風淡淡的看了你一眼﹐說道﹕想拜入冷梅莊？\n",
        "梅影風說道﹕冷梅劍法﹐非心志堅毅者不傳。\n",
        "梅影風說道﹕你若真有心﹐便再來找我。\n",
        (: set_flag, me :)
    }));
    return 0;
}

int init_apprentice(object me)
{
    if( me->query_class() != "commoner" ) {
        do_chat(({
            "梅影風搖了搖頭﹐說道﹕你已有師門﹐我冷梅莊不收。\n",
        }));
        return 1;
    }
    if( ::init_apprentice(me) ) {
        seteuid(getuid());
        me->set_class("warrior");
        me->set("title", "冷梅莊弟子");
        do_chat(({
            "梅影風微微頷首﹐說道﹕好﹐從今日起你便是冷梅莊弟子。\n",
            "梅影風說道﹕冷梅劍法以寒梅傲雪之意入劍﹐你需勤加修煉。\n",
            "梅影風說道﹕去吧。\n"
        }));
    }
}

void relay_say(object me, string msg)
{
    if( is_fighting() || is_chatting() ) return;

    if( strsrch(msg, "妻子") >= 0 || strsrch(msg, "夫人") >= 0
    ||  strsrch(msg, "藥") >= 0 || strsrch(msg, "medicine") >= 0 ) {
        if( me->query("quest/meiyingfeng_medicine_step1") ) {
            do_chat("梅影風輕嘆一聲﹐說道﹕多謝你費心﹐方丈若有消息﹐還望轉告。\n");
            return;
        }

        if( me->query_temp("pending/meiyingfeng_medicine") ) {
            do_chat(({
                "梅影風眉頭微皺﹐說道﹕你去找過白象寺方丈了嗎﹖\n",
                "梅影風說道﹕方丈精通佛門醫理﹐或許能救內子。\n",
            }));
            return;
        }

        do_chat(({
            "梅影風神情一黯﹐沉默了片刻。\n",
            "梅影風說道﹕內子 ... 她染了一種怪病﹐已經臥床多日。\n",
            "梅影風說道﹕我遍訪名醫﹐用盡各種靈藥﹐都不見好轉。\n",
            "梅影風說道﹕聽聞白象寺方丈精通佛門古方﹐也許他會知道解法。\n",
            "梅影風深深看了你一眼﹐說道﹕若你有暇﹐能否替我去白象寺問問方丈﹖\n",
            "梅影風說道﹕冷梅莊事務纏身﹐我一時脫不開身 ...\n",
            (: $1->set_temp("pending/meiyingfeng_medicine", 1) :),
        }));
        return;
    }

    if( strsrch(msg, "二當家") >= 0 || strsrch(msg, "趙鐵虎") >= 0
    ||  strsrch(msg, "鐵虎") >= 0 ) {
        if( me->query("quest/hudao_erdangjia_step1") )
            do_chat(({
                "梅影風微微蹙眉﹐說道﹕虎刀門的趙鐵虎﹖我倒是見過幾面。\n",
                "梅影風說道﹕此人忠厚老實﹐是韓笑的左膀右臂。\n",
                "梅影風若有所思﹐說道﹕他失蹤了﹖這倒奇怪 ...\n",
                "梅影風說道﹕我之前聽韓笑提過﹐趙鐵虎一直在查劉乙忘玄和魚鐵山的事。\n",
                "梅影風說道﹕如果他真的去了黑風嶺﹐恐怕凶多吉少。那兩人絕非善類。\n",
            }));
        else
            do_chat("梅影風淡淡說道﹕虎刀門的事﹐我不太清楚。\n");
        return;
    }

    if( strsrch(msg, "冷梅") >= 0 || strsrch(msg, "劍法") >= 0 ) {
        do_chat("梅影風淡淡說道﹕冷梅劍法以寒梅傲雪之意入劍﹐非心志堅毅者不可修習。\n");
        return;
    }
}

int acquire_skill(object ob, string skill)
{
    if( is_chatting() )
        return notify_fail("你最好等莊主的話說完再插嘴。\n");
    if( !ob->is_apprentice_of(this_object()) ) return 0;

    switch(skill) {
    case "lengmei sword":
        if( !ob->query_learn(skill) ) {
            say("梅影風點了點頭，說道：好，為師傳你冷梅劍法。\n");
            message_vision("$N將冷梅劍法的入門招式傳授給$n。\n", this_object(), ob);
            ob->improve_skill(skill, random(ob->query_attr("dex")) + 1);
        }
        break;
    default:
        return 0;
    }

    do_chat(({
        "梅影風說道：劍法之妙﹐如寒梅凌雪﹐愈冷愈堅。\n",
        "梅影風說道：好生修煉。\n",
    }));

    return 1;
}
