// abbot.c - Baixiang Temple Abbot

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("白象寺方丈", ({"abbot", "fangzhang"}));
    set_attr("str", 20);
    set_attr("con", 22);
    set_attr("wis", 25);
    set_attr("spi", 24);
    set_attr("cps", 22);
    set_race("human");
    set_class("monk");
    set_level(60);

    set_skill("staff", 90);
    set_skill("diamond hammer", 85);
    set_skill("dodge", 75);
    set_skill("parry", 80);
    set_skill("unarmed", 70);

    set("age", 65);
    set("attitude", "peaceful");
    set("long",
	"白象寺方丈﹐身穿一件洗得發白的灰色僧袍﹐面容慈祥﹐雙手\n"
	"合十﹐身形雖然消瘦﹐但自有一股不怒而威的氣勢。\n");
    set("chat_chance", 1);
    set("chat_msg", ({
	"方丈微微一笑﹐說道﹕施主﹐萬法皆空﹐放下即是自在。\n",
    }));
    setup();
    carry_money("coin", 100);
    set_temp("apply/vision_of_ghost", 1);
}

void set_flag(object me)
{
    if( me && present(me, environment()) ) {
        if( me->query_class() != "commoner"
        ||  me->query("title") )
            return;
        me->set_temp("pending/abbot", 1);
    }
    else
        do_chat("方丈雙手合十﹐說道﹕阿彌陀佛﹐施主已去。\n");
}

int accept_apprentice(object me)
{
    if( is_chatting() ) return 0;
    if( me->query_temp("pending/abbot") ) return 1;
    if( me->query("title") ) {
        do_chat("方丈說道﹕施主已有師門﹐老衲不便再收。\n");
        return 0;
    }
    do_chat(({
        "方丈微微一笑﹐說道﹕施主想皈依佛門？\n",
        "方丈說道﹕白象寺雖是小廟﹐但佛法無邊﹐非有佛緣者不收。\n",
        "方丈說道﹕施主若真有佛緣﹐便再來找老衲吧。\n",
        (: set_flag, me :)
    }));
    return 0;
}

int init_apprentice(object me)
{
    if( me->query_class() != "commoner" ) {
        do_chat(({
            "方丈搖了搖頭﹐說道﹕施主既已入別派﹐就不宜再入佛門了。\n",
        }));
        return 1;
    }
    if( ::init_apprentice(me) ) {
        seteuid(getuid());
        me->set_class("monk");
        me->set("title", "白象寺弟子");
        do_chat(({
            "方丈點了點頭﹐說道﹕善哉﹐從今日起你便是白象寺弟子了。\n",
            "方丈說道﹕佛門弟子﹐當以慈悲為懷﹐廣度眾生。\n",
            "方丈說道﹕去吧﹐好生修行。\n"
        }));
    }
}

void relay_say(object me, string msg)
{
    if( is_fighting() || is_chatting() ) return;

    if( strsrch(msg, "梅影風") >= 0 || strsrch(msg, "冷梅") >= 0
    ||  strsrch(msg, "藥") >= 0 || strsrch(msg, "medicine") >= 0 ) {
        if( me->query("quest/meiyingfeng_medicine_step1") ) {
            do_chat(({
                "方丈雙手合十﹐說道﹕阿彌陀佛﹐施主已知藥方之事。\n",
                "方丈說道﹕那味「雪蓮淨心草」﹐生於黑風嶺深處﹐極為難尋。\n",
                "方丈說道﹕施主若要前往﹐務必小心。\n",
            }));
            return;
        }

        if( !me->query_temp("pending/meiyingfeng_medicine") ) {
            do_chat("方丈微微一笑﹐說道﹕阿彌陀佛﹐施主有何指教﹖\n");
            return;
        }

        do_chat(({
            "方丈神色微變﹐說道﹕阿彌陀佛﹐梅莊主的夫人染病了﹖\n",
            "方丈沉吟片刻﹐說道﹕老衲在古卷中確曾見過一帖古方 ...\n",
            "方丈說道﹕此方名為「淨心散」﹐需以「雪蓮淨心草」為主藥。\n",
            "方丈說道﹕只是此草極為罕見﹐據說只生長在黑風嶺的深處。\n",
            "方丈說道﹕而且 ...\n",
            "方丈壓低聲音﹐說道﹕老衲近日聽聞一些不尋常的傳言。\n",
            "方丈說道﹕有人說魚鐵山和劉乙忘玄最近走動頻繁﹐似乎在謀劃什麼。\n",
            "方丈說道﹕此事或許與梅莊主夫人的病有關﹐也或許無關﹐施主自行斟酌。\n",
            "方丈雙手合十﹐說道﹕阿彌陀佛﹐願施主一路平安。\n",
            (: $1->set("quest/meiyingfeng_medicine_step1", 1) :),
            (: $1->delete_temp("pending/meiyingfeng_medicine") :),
        }));
        return;
    }

    if( strsrch(msg, "二當家") >= 0 || strsrch(msg, "趙鐵虎") >= 0
    ||  strsrch(msg, "鐵虎") >= 0 ) {
        if( me->query("quest/hudao_erdangjia_step1") ) {
            do_chat(({
                "方丈雙手合十﹐說道﹕阿彌陀佛﹐施主問的是虎刀門的趙施主﹖\n",
                "方丈沉吟片刻﹐說道﹕半月前確有一位魁梧漢子來過白象寺。\n",
                "方丈說道﹕他向老衲打聽黑風嶺深處的路﹐說要去查一件要緊的事。\n",
                "方丈說道﹕老衲勸他不要獨自前往﹐但他心意已決。\n",
                "方丈說道﹕他臨走時說﹐若他三日不回﹐便請老衲轉告韓施主。\n",
                "方丈神色凝重﹐說道﹕可惜他走後再無消息﹐老衲也甚為掛念。\n",
                "方丈說道﹕老衲隱約聽聞﹐黑風嶺近來有不尋常的人出沒 ...\n",
                "方丈說道﹕施主若要去尋他﹐萬事小心。阿彌陀佛。\n",
            }));
        }
        else
            do_chat("方丈微微搖頭﹐說道﹕阿彌陀佛﹐老衲不知施主所指何人。\n");
        return;
    }

    if( strsrch(msg, "淨心") >= 0 || strsrch(msg, "雪蓮") >= 0 ) {
        if( me->query("quest/meiyingfeng_medicine_step1") ) {
            do_chat(({
                "方丈說道﹕「雪蓮淨心草」形如蓮花﹐色如白雪﹐散發淡淡清香。\n",
                "方丈說道﹕黑風嶺山高路險﹐聽說韓笑曾去過那裡﹐或許他知道些什麼。\n",
            }));
        }
        else
            do_chat("方丈微微搖頭﹐說道﹕老衲不知施主所指為何。\n");
        return;
    }
}

int acquire_skill(object ob, string skill)
{
    if( is_chatting() )
        return notify_fail("你最好等方丈的話說完再插嘴。\n");
    if( !ob->is_apprentice_of(this_object()) ) return 0;

    switch(skill) {
    case "staff":
        if( !ob->query_learn(skill) ) {
            say("方丈點了點頭，說道：好，老衲這就傳你棍法。\n");
            message_vision("$N將白象寺棍法的入門招式傳授給$n。\n", this_object(), ob);
            ob->improve_skill(skill, random(ob->query_attr("con")) + 1);
        }
        break;
    case "diamond hammer":
        if( !ob->query_learn(skill) ) {
            say("方丈點了點頭，說道：好，老衲傳你金剛鎚法。\n");
            message_vision("$N將白象寺金剛鎚法的入門心要傳授給$n。\n", this_object(), ob);
            ob->improve_skill(skill, random(ob->query_attr("str")) + 1);
        }
        break;
    default:
        return 0;
    }

    do_chat(({
        "方丈說道：棍法之道﹐以守為攻﹐以柔克剛。\n",
        "方丈說道：你好生修煉﹐阿彌陀佛。\n",
    }));

    return 1;
}
