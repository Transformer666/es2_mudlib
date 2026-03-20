// boy.c - 阿虎 (河灣練拳的少年)
// Supports quest: 郭布要收的徒弟在哪裡？

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("阿虎", ({"boy", "ahu", "tiger boy"}));
    set_attr("str", 14);
    set_attr("dex", 16);
    set_attr("con", 15);
    set_race("human");
    set_class("commoner");
    set_level(5);

    set_skill("unarmed", 20);

    set("age", 15);
    set("gender", "male");
    set("long",
	"一個十五、六歲的少年﹐身材結實﹐皮膚被太陽曬得黝黑。他正\n"
	"在河灣的空地上笨拙地揮拳踢腿﹐雖然招式生疏﹐卻十分認真。\n");
    set("chat_chance", 3);
    set("chat_msg", ({
	"阿虎擦了擦汗﹐繼續認真地練拳。\n",
	"阿虎喘著粗氣﹐自言自語道﹕總有一天﹐我也要成為大俠﹗\n",
	"阿虎朝著河面用力揮了一拳﹐濺起一片水花。\n",
    }));
    setup();
}

void relay_say(object ob, string msg)
{
    if( !userp(ob) ) return;
    if( is_fighting() || is_chatting() ) return;

    if( strsrch(msg, "郭布") >= 0 || strsrch(msg, "師父") >= 0
    ||  strsrch(msg, "拜師") >= 0 || strsrch(msg, "學武") >= 0 ) {
	if( ob->query("quest/guobu_apprentice_done") ) {
	    do_chat("阿虎高興地說道﹕郭師父已經收我為徒了﹐我一定會好好練武的﹗\n");
	    return;
	}
	if( ob->query_temp("pending/guobu_apprentice") >= 1 ) {
	    do_chat(({
		"阿虎停下手中的動作﹐驚訝地瞪大了眼睛。\n",
		"阿虎說道﹕真的嗎﹖有人願意教我武功﹖\n",
		"阿虎激動地說道﹕我 ... 我當然願意﹗我做夢都想拜師學藝﹗\n",
		"阿虎連忙抱拳道﹕大哥﹐麻煩你替我跟那位前輩說一聲﹐阿虎願意拜師﹗\n",
	    }));
	    ob->set_temp("pending/guobu_apprentice", 2);
	    return;
	}
	do_chat(({
	    "阿虎撓了撓頭﹐說道﹕學武﹖我倒是很想﹐可是沒人肯教我。\n",
	    "阿虎嘆了口氣道﹕我爹娘走得早﹐也沒錢拜師。只能自己在這兒瞎比劃。\n",
	}));
	return;
    }
}
